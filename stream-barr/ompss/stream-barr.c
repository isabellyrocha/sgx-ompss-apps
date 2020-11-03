# include <stdio.h>
# include <math.h>
# include <float.h>
# include <stdlib.h>
# include <sys/time.h>
# include "omp.h"

# define M 20
# define NTIMES	10
# define OFFSET	0
# define HLINE "-------------------------------------------------------------\n"

# ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
# endif
# ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
# endif

#define OmpSs
#define TUNED

#pragma omp task out ([bs]a, [bs]b, [bs]c)
void init_task(double *a, double *b, double *c, int bs)
{
	int j;	
	for (j=0; j < bs; j++){
	        a[j] = 1.0;
	        b[j] = 2.0;
	        c[j] = 0.0;
		a[j] = 2.0E0 * a[j];
  	}
}

#pragma omp task in ([bs]a) out ([bs]c)
void copy_task(double *a, double *c, int bs)
{
        int j;
        for (j=0; j < bs; j++)
                c[j] = a[j];
}

#pragma omp task in ([bs]c ) out ([bs]b)
void scale_task(double *b, double *c, double scalar, int bs)
{
        int j;
        for (j=0; j < bs; j++)
            b[j] = scalar*c[j];
}

#pragma omp task in ([bs]a, [bs]b) out ([bs]c)
void add_task(double *a, double *b, double *c, int bs)
{
        int j;
        for (j=0; j < bs; j++)
           c[j] = a[j]+b[j];
}

#pragma omp task in ([bs]b, [bs]c) out ([bs]a)
void triad_task(double *a, double *b, double *c, double scalar, int bs)
{
        int j;
        for (j=0; j < bs; j++)
            a[j] = b[j]+scalar*c[j];

}

void tuned_initialization(double a[], double b[], double c[], int N, int bs)
{
	int j;
        for (j=0; j<N; j+=bs)
            //Assumes N is multiple of BSIZE 
            init_task(&a[j], &b[j], &c[j], bs); 
}

/* A gettimeofday routine to give access to the wall
   clock timer on most UNIX-like systems.  */
double mysecond()
{
        struct timeval tp;
        int i;

        i = gettimeofday(&tp,NULL);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

int checktick()
{
    int         i, minDelta, Delta;
    double      t1, t2, timesfound[M];

    /* Collect a sequence of M unique time values from the system. */
    for (i = 0; i < M; i++) {
        t1 = mysecond();
        while( ((t2=mysecond()) - t1) < 1.0E-6 );
        timesfound[i] = t1 = t2;
    }

    /*
     * Determine the minimum difference between these M values.
     * This result will be our estimate (in microseconds) for the
     * clock granularity.
    */
    minDelta = 1000000;
    for (i = 1; i < M; i++) {
        Delta = (int)( 1.0E6 * (timesfound[i]-timesfound[i-1]));
        minDelta = MIN(minDelta, MAX(Delta,0));
    }

    return(minDelta);
}

int main(int argc, char *argv[])
{
    int			quantum, checktick();
    int			BytesPerWord;
    register int	j, k;
    double		scalar, t, times[4][NTIMES], total_time;
    int                 N = atoi(argv[1])*1024*1024; //128*1024*1024;
    int                 bs = N/atoi(argv[2]); //N/64; 
    struct timeval start, stop;
    unsigned long elapsed;


    /* --- SETUP --- determine precision and check timing --- */
    gettimeofday(&start,NULL);
    double s = (double)start.tv_sec + (double)start.tv_usec * .000001;

#ifdef VERBOSE
    printf(HLINE);
    printf("STREAM version $Revision: 5.8 $\n");
    printf(HLINE);
    BytesPerWord = sizeof(double);
    printf("This system uses %d bytes per DOUBLE PRECISION word.\n",
	BytesPerWord);

    printf(HLINE);
    printf("Array size = %d, Offset = %d\n" , N, OFFSET);
    printf("Total memory required = %.1f MB.\n",
	(3.0 * BytesPerWord) * ( (double) N / 1048576.0));
    printf("Each test is run %d times, but only\n", NTIMES);
    printf("the *best* time for each is used.\n");
    printf(HLINE);
#endif

#ifdef OmpSs
    k = omp_get_num_threads();
    //printf ("Number of Threads = %i\n",k);
#endif
#ifdef SMPSs
    //printf("CSS_NUM_CPUS %s \n", getenv("CSS_NUM_CPUS"));
    k = atoi (getenv ("CSS_NUM_CPUS"));
    //printf ("Number of CSS Threads = %i\n",k);
#endif
#ifdef CellSs
    //printf(HLINE);
    k = atoi (getenv ("CSS_NUM_SPUS"));
    //printf ("Number of CSS Threads = %i\n",k);
#endif
#ifdef CellSs_tracing
    //printf(HLINE);
    k = atoi (getenv ("CSS_NUM_SPUS"));
    //printf ("Number of CSS Threads = %i\n",k);
#endif

    //printf(HLINE);

    //printf ("Printing one line per active thread....\n");

    double   __attribute__((aligned(4096)))   *a = (double*) malloc(N*sizeof(double));
    double   __attribute__((aligned(4096)))   *b = (double*) malloc(N*sizeof(double));
    double   __attribute__((aligned(4096)))   *c = (double*) malloc(N*sizeof(double));

    static double   avgtime[4] = {0}, maxtime[4] = {0},
                    mintime[4] = {FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX};

    static char     *label[4] = {"Copy:      ", "Scale:     ",
                                 "Add:       ", "Triad:     "};

    double   bytes[4] = {
        2 * sizeof(double) * N,
        2 * sizeof(double) * N,
        3 * sizeof(double) * N,
        3 * sizeof(double) * N
    };

    total_time = mysecond();
    // tuned_initialization
    for (j=0; j<N; j+=bs)
        //Assumes N is multiple of BSIZE
//#pragma omp task out ([bs]a, [bs]b, [bs]c)
        init_task(&a[j], &b[j], &c[j], bs);
#pragma omp taskwait

    /*	--- MAIN LOOP --- repeat test cases NTIMES times --- */

    scalar = 3.0;
    for (k=0; k<NTIMES; k++)
	{
	times[0][k] = mysecond();
#ifdef TUNED
     //  tuned_STREAM_Copy(a, c, N, BSIZE);
    int j;
    for (j=0; j<N; j+=bs)
//#pragma omp task in ([bs]a) out ([bs]c)
    // Assumes N is multiple of 100
        copy_task(&a[j], &c[j], bs);
#else
    printf("WARNING: This version is a port to StarSs that only works for TUNED option \n");
    for (j=0; j<N; j++)
        c[j] = a[j];
#endif
#pragma omp taskwait  
    times[0][k] = mysecond() - times[0][k];
    times[1][k] = mysecond();
#ifdef TUNED
    // tuned_STREAM_Scale(a, c, scalar, N, BSIZE);
        //Assumes N is multiple of 100
    for (j=0; j<N; j+=bs)
//#pragma omp task in ([bs]c ) out ([bs]b)
         scale_task(&b[j], &c[j], scalar, bs);
#else
    for (j=0; j<N; j++)
        b[j] = scalar*c[j];
#endif
#pragma omp taskwait
    times[1][k] = mysecond() - times[1][k];	
    times[2][k] = mysecond();
#ifdef TUNED
    // tuned_STREAM_Add(a, b, c, N, BSIZE);
    // Assumes N is multiple of 100
    for (j=0; j<N; j+=bs)
//#pragma omp task in ([bs]a, [bs]b) out ([bs]c)
        add_task(&a[j], &b[j], &c[j], bs);
#else
	for (j=0; j<N; j++)
	    c[j] = a[j]+b[j];
#endif
#pragma omp taskwait 
    times[2][k] = mysecond() - times[2][k];
    times[3][k] = mysecond();
#ifdef TUNED
    //        tuned_STREAM_Triad(a, b, c, scalar, N, BSIZE);
    //Assumes N is multiple of 100
    for (j=0; j<N; j+=bs)
//#pragma omp task in ([bs]b, [bs]c) out ([bs]a)
        triad_task(&a[j], &b[j], &c[j], scalar, bs);
#else
    for (j=0; j<N; j++)
        a[j] = b[j]+scalar*c[j];
#endif
#pragma omp  taskwait
    times[3][k] = mysecond() - times[3][k];
    }
    gettimeofday(&stop,NULL);
    double e = (double)stop.tv_sec + (double)stop.tv_usec * .000001;
    total_time = mysecond() - total_time;
#pragma omp taskwait

    printf("%d,%d,%f\n", (int)s, (int)e, (e-s));
    /*	--- SUMMARY --- */

    for (k=1; k<NTIMES; k++) /* note -- skip first iteration */ {
	for (j=0; j<4; j++) {
	    avgtime[j] = avgtime[j] + times[j][k];
	    mintime[j] = MIN(mintime[j], times[j][k]);
	    maxtime[j] = MAX(maxtime[j], times[j][k]);
	}
    }

#ifdef VERBOSE
    printf("Function      Rate (MB/s)   Avg time     Min time     Max time\n");
    for (j=0; j<4; j++) {
	avgtime[j] = avgtime[j]/(double)(NTIMES-1);

	printf("%s%11.4f  %11.4f  %11.4f  %11.4f\n", label[j],
	       1.0E-06 * bytes[j]/mintime[j],
	       avgtime[j],
	       mintime[j],
	       maxtime[j]);
    }

    printf(HLINE);
    printf("TOTAL time (including initialization) =  %11.4f seconds\n", total_time);
#endif
    /* --- Check Results --- */

    // checkSTREAMresults(a, b, c, BSIZE);
    double aj,bj,cj;//,scalar;
    double asum,bsum,csum;
    double epsilon;
    
    /* reproduce initialization */
    aj = 1.0;
    bj = 2.0;
    cj = 0.0;
    /* a[] is modified during timing check */
    aj = 2.0E0 * aj;
    /* now execute timing loop */
    scalar = 3.0;
    for (k=0; k<NTIMES; k++) {
        cj = aj;
        bj = scalar*cj;
        cj = aj+bj;
        aj = bj+scalar*cj;
    }
    aj = aj * (double) (N);
    bj = bj * (double) (N);
    cj = cj * (double) (N);

    asum = 0.0;
    bsum = 0.0;
    csum = 0.0;
    for (j=0; j<N; j++) {
	asum += a[j];
	bsum += b[j];
	csum += c[j];
    }
#ifdef VERBOSE
    printf ("Results Comparison: \n");
    printf ("        Expected  : %f %f %f \n",aj,bj,cj);
    printf ("        Observed  : %f %f %f \n",asum,bsum,csum);
#endif

#ifndef abs
#define abs(a) ((a) >= 0 ? (a) : -(a))
#endif
    epsilon = 1.e-8;
#ifdef VERBOSE
    if (abs(aj-asum)/asum > epsilon) {
	printf ("Failed Validation on array a[]\n");
	printf ("        Expected  : %f \n",aj);
	printf ("        Observed  : %f \n",asum);
    } else if (abs(bj-bsum)/bsum > epsilon) {
	printf ("Failed Validation on array b[]\n");
	printf ("        Expected  : %f \n",bj);
	printf ("        Observed  : %f \n",bsum);
    } else if (abs(cj-csum)/csum > epsilon) {
	printf ("Failed Validation on array c[]\n");
	printf ("        Expected  : %f \n",cj);
	printf ("        Observed  : %f \n",csum);
    } else {
        printf ("Solution Validates\n");
    }
    printf(HLINE);
#endif

    return 0;
}
