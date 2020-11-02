/*-----------------------------------------------------------------------*/
/* Program: Stream                                                       */
/* Adapted to StarSs by Rosa M. Badia (Barcelona Supercomputing Center)	 */
/* This version does not insert barriers after each set of operations,   */
/* to promote task chaining in StarSs					 */
/* Revision: $Id: stream.c,v 5.8 2007/02/19 23:57:39 mccalpin Exp mccalpin $ */
/* Original code developed by John D. McCalpin                           */
/* Programmers: John D. McCalpin                                         */
/*              Joe R. Zagar                                             */
/*                                                                       */
/* This program measures memory transfer rates in MB/s for simple        */
/* computational kernels coded in C.                                     */
/*-----------------------------------------------------------------------*/
/* Copyright 1991-2005: John D. McCalpin                                 */
/*-----------------------------------------------------------------------*/
/* License:                                                              */
/*  1. You are free to use this program and/or to redistribute           */
/*     this program.                                                     */
/*  2. You are free to modify this program for your own use,             */
/*     including commercial use, subject to the publication              */
/*     restrictions in item 3.                                           */
/*  3. You are free to publish results obtained from running this        */
/*     program, or from works that you derive from this program,         */
/*     with the following limitations:                                   */
/*     3a. In order to be referred to as "STREAM benchmark results",     */
/*         published results must be in conformance to the STREAM        */
/*         Run Rules, (briefly reviewed below) published at              */
/*         http://www.cs.virginia.edu/stream/ref.html                    */
/*         and incorporated herein by reference.                         */
/*         As the copyright holder, John McCalpin retains the            */
/*         right to determine conformity with the Run Rules.             */
/*     3b. Results based on modified source code or on runs not in       */
/*         accordance with the STREAM Run Rules must be clearly          */
/*         labelled whenever they are published.  Examples of            */
/*         proper labelling include:                                     */
/*         "tuned STREAM benchmark results"                              */
/*         "based on a variant of the STREAM benchmark code"             */
/*         Other comparable, clear and reasonable labelling is           */
/*         acceptable.                                                   */
/*     3c. Submission of results to the STREAM benchmark web site        */
/*         is encouraged, but not required.                              */
/*  4. Use of this program or creation of derived works based on this    */
/*     program constitutes acceptance of these licensing restrictions.   */
/*  5. Absolutely no warranty is expressed or implied.                   */
/*-----------------------------------------------------------------------*/
# include <stdio.h>
# include <math.h>
# include <float.h>
# include <stdlib.h>
//# include "limits.h"
# include <sys/time.h>
# include "omp.h"

/* INSTRUCTIONS:
 *
 *	1) Stream requires a good bit of memory to run.  Adjust the
 *          value of 'N' (below) to give a 'timing calibration' of
 *          at least 20 clock-ticks.  This will provide rate estimates
 *          that should be good to about 5% precision.
 */

//# define N	128*1024*1024
# define M 20
# define NTIMES	10
# define OFFSET	0

/*
 *	3) Compile the code with full optimization.  Many compilers
 *	   generate unreasonably bad code before the optimizer tightens
 *	   things up.  If the results are unreasonably good, on the
 *	   other hand, the optimizer might be too smart for me!
 *
 *         Try compiling with:
 *               cc -O stream_omp.c -o stream_omp
 *
 *         This is known to work on Cray, SGI, IBM, and Sun machines.
 *
 *
 *	4) Mail the results to mccalpin@cs.virginia.edu
 *	   Be sure to include:
 *		a) computer hardware model number and software revision
 *		b) the compiler flags
 *		c) all of the output from the test case.
 * Thanks!
 *
 */

# define HLINE "-------------------------------------------------------------\n"

# ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
# endif
# ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
# endif

#define OmpSs
//#define SMPSs
//#define CellSs
//#define CellSs_tracing
#define TUNED
// Definition of BSIZE for CellSs
//#ifdef CellSs
//#define BSIZE 4000
//#endif
// Definition of BSIZE for CellSs when using tracing
//#ifdef CellSs_tracing
//#define BSIZE 3200
//#endif
//#ifdef SMPSs
// Definition of BSIZE for SMPSs
//#define BSIZE N/64
//#endif
//#ifdef OmpSs
// Definitions of BSIZE for OmpSs
//#define BSIZE N/64
//#endif



#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
# include <unistd.h>
# include <pwd.h>
# define MAX_PATH FILENAME_MAX
#include <nanos_omp.h>
#include "sgx_urts.h"
#include "App.h"
#include "Enclave_u.h"

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

typedef struct _sgx_errlist_t {
    sgx_status_t err;
    const char *msg;
    const char *sug; /* Suggestion */
} sgx_errlist_t;

/* Error code returned by sgx_create_enclave */
static sgx_errlist_t sgx_errlist[] = {
    {
        SGX_ERROR_UNEXPECTED,
        "Unexpected error occurred.",
        NULL
    },
    {
        SGX_ERROR_INVALID_PARAMETER,
        "Invalid parameter.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_MEMORY,
        "Out of memory.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_LOST,
        "Power transition occurred.",
        "Please refer to the sample \"PowerTransition\" for details."
    },
    {
        SGX_ERROR_INVALID_ENCLAVE,
        "Invalid enclave image.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ENCLAVE_ID,
        "Invalid enclave identification.",
        NULL
    },
    {
        SGX_ERROR_INVALID_SIGNATURE,
        "Invalid enclave signature.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_EPC,
        "Out of EPC memory.",
        NULL
    },
    {
        SGX_ERROR_NO_DEVICE,
        "Invalid SGX device.",
        "Please make sure SGX module is enabled in the BIOS, and install SGX driver afterwards."
    },
    {
        SGX_ERROR_MEMORY_MAP_CONFLICT,
        "Memory map conflicted.",
        NULL
    },
    {
        SGX_ERROR_INVALID_METADATA,
        "Invalid enclave metadata.",
        NULL
    },
    {
        SGX_ERROR_DEVICE_BUSY,
        "SGX device was busy.",
        NULL
    },
    {
        SGX_ERROR_INVALID_VERSION,
        "Enclave version was invalid.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ATTRIBUTE,
        "Enclave was not authorized.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_FILE_ACCESS,
        "Can't open enclave file.",
        NULL
    },
};

/* Check error conditions for loading enclave */
void print_error_message(sgx_status_t ret)
{
    size_t idx = 0;
    size_t ttl = sizeof sgx_errlist/sizeof sgx_errlist[0];

    for (idx = 0; idx < ttl; idx++) {
        if(ret == sgx_errlist[idx].err) {
            if(NULL != sgx_errlist[idx].sug)
                printf("Info: %s\n", sgx_errlist[idx].sug);
            printf("Error: %s\n", sgx_errlist[idx].msg);
            break;
        }
    }
    
    if (idx == ttl)
    	printf("Error code is 0x%X. Please refer to the \"Intel SGX SDK Developer Reference\" for more details.\n", ret);
}

static double timestemp() {
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

/* Initialize the enclave:
 *   Call sgx_create_enclave to initialize an enclave instance
 */
int initialize_enclave(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    
    /* Call sgx_create_enclave to initialize an enclave instance */
    /* Debug Support: set 2nd parameter to 1 */
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        print_error_message(ret);
        return -1;
    }

    return 0;
}

/* OCall functions */
void ocall_print_string(const char *str)
{
    /* Proxy/Bridge will check the length and null-terminate 
     * the input string to prevent buffer overflow. 
     */
    printf("%s", str);
}

static void initialize(long length, double data[length])
{
    for (long i = 0; i < length; i++) {
        data[i] = ((double)rand()/(double)RAND_MAX);
    }
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
    int		i, minDelta, Delta;
    double	t1, t2, timesfound[M];

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

int SGX_CDECL main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    /* Initialize the enclave */
    if(initialize_enclave() < 0){
        printf("Enter a character before exit ...\n");
        getchar();
        return -1; 
    }
 
    /* Utilize edger8r attributes */
    edger8r_array_attributes();
    edger8r_pointer_attributes();
    edger8r_type_attributes();
    edger8r_function_attributes();
    
    /* Utilize trusted libraries */
    ecall_libc_functions();
    ecall_libcxx_functions();
    ecall_thread_functions();

    struct timeval start;
    struct timeval stop;
    unsigned long elapsed;

    {
    gettimeofday(&start,NULL);
    double s = (double)start.tv_sec + (double)start.tv_usec * .000001;

/* ------------------------------------------------------------------------------------------------------------------------*/

    int			quantum, checktick();
    int			BytesPerWord;
    register int	j, k;
    double		scalar, t, times[4][NTIMES], total_time, total_bytes;
//    int                 N = atoi(argv[1])*1024*1024; //128*1024*1024;
//    int                 bs = N/atoi(argv[2]); //N/64;
    int                 bs = atoi(argv[2]); //N/64;
    int                 N = atoi(argv[1])*1024;

    /* --- SETUP --- determine precision and check timing --- */
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

#ifdef OmpSs
    printf(HLINE);
    k = omp_get_num_threads();
    printf ("Number of Threads = %i\n",k);
#endif
#ifdef SMPSs
    printf("CSS_NUM_CPUS %s \n", getenv("CSS_NUM_CPUS"));
    k = atoi (getenv ("CSS_NUM_CPUS"));
    printf ("Number of CSS Threads = %i\n",k);
#endif
#ifdef CellSs
    printf(HLINE);
    k = atoi (getenv ("CSS_NUM_SPUS"));
    printf ("Number of CSS Threads = %i\n",k);
#endif
#ifdef CellSs_tracing
    printf(HLINE);
    k = atoi (getenv ("CSS_NUM_SPUS"));
    printf ("Number of CSS Threads = %i\n",k);
#endif

    printf(HLINE);

    printf ("Printing one line per active thread....\n");
#endif

    double   __attribute__((aligned(4096)))   *a = (double*) malloc(N*sizeof(double));
    double   __attribute__((aligned(4096)))   *b = (double*) malloc(N*sizeof(double));
    double   __attribute__((aligned(4096)))   *c = (double*) malloc(N*sizeof(double));

    static double   avgtime[4] = {0}, maxtime[4] = {0},
                    mintime[4] = {FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX};

    static char     *label[4] = {"Copy:      ", "Scale:     ",
                                 "Add:       ", "Triad:     "};

    double   bytes[4] = {
        (double) 2 * sizeof(double) * N,
        (double) 2 * sizeof(double) * N,
        (double) 3 * sizeof(double) * N,
        (double) 3 * sizeof(double) * N
    };

    total_time = mysecond();
    // tuned_initialization
    for (j=0; j<N; j+=bs)
        //Assumes N is multiple of BSIZE
#pragma omp task out ([bs]a, [bs]b, [bs]c)
        ecall_init_task(global_eid, &a[j], &b[j], &c[j], bs);
//#pragma omp taskwait

    /*	--- MAIN LOOP --- repeat test cases NTIMES times --- */

    scalar = 3.0;
    for (k=0; k<NTIMES; k++) {
	times[0][k] = mysecond();
#ifdef TUNED
     //  tuned_STREAM_Copy(a, c, N, BSIZE);
    int j;
    for (j=0; j<N; j+=bs)
    // Assumes N is multiple of 100
#pragma omp task in ([bs]a) out ([bs]c)        
        ecall_copy_task(global_eid, &a[j], &c[j], bs);
#else
    printf("WARNING: This version is a port to StarSs that only works for TUNED option \n");
    for (j=0; j<N; j++)
        c[j] = a[j];
#endif
//#pragma omp taskwait
    times[0][k] = mysecond() - times[0][k];
    times[1][k] = mysecond();
#ifdef TUNED
    // tuned_STREAM_Scale(a, c, scalar, N, BSIZE);
        //Assumes N is multiple of 100
    for (j=0; j<N; j+=bs)
#pragma omp task in ([bs]c ) out ([bs]b)
         ecall_scale_task(global_eid, &b[j], &c[j], scalar, bs);
#else
    for (j=0; j<N; j++)
        b[j] = scalar*c[j];
#endif
//#pragma omp taskwait
    times[1][k] = mysecond() - times[1][k];
    times[2][k] = mysecond();
#ifdef TUNED
    // tuned_STREAM_Add(a, b, c, N, BSIZE);
    // Assumes N is multiple of 100
    for (j=0; j<N; j+=bs)
#pragma omp task in ([bs]a, [bs]b) out ([bs]c)
        ecall_add_task(global_eid, &a[j], &b[j], &c[j], bs);
#else
	for (j=0; j<N; j++)
	    c[j] = a[j]+b[j];
#endif
//#pragma omp taskwait
    times[2][k] = mysecond() - times[2][k];
    times[3][k] = mysecond();
#ifdef TUNED
    //        tuned_STREAM_Triad(a, b, c, scalar, N, BSIZE);
    //Assumes N is multiple of 100
    for (j=0; j<N; j+=bs)
#pragma omp task in ([bs]b, [bs]c) out ([bs]a)
        ecall_triad_task(global_eid, &a[j], &b[j], &c[j], scalar, bs);
#else
    for (j=0; j<N; j++)
        a[j] = b[j]+scalar*c[j];
#endif
//#pragma omp  taskwait
    times[3][k] = mysecond() - times[3][k];
    }
#pragma omp taskwait
    gettimeofday(&stop,NULL);
    double e =(double)stop.tv_sec + (double)stop.tv_usec * .000001;
    total_time = mysecond() - total_time;

     printf("%d,%d,%f\n", (int)s, (int)e, (e-s));
    /*	--- SUMMARY --- */

    for (k=1; k<NTIMES; k++) /* note -- skip first iteration */ {
	for (j=0; j<4; j++) {
	    avgtime[j] = avgtime[j] + times[j][k];
	    mintime[j] = MIN(mintime[j], times[j][k]);
	    maxtime[j] = MAX(maxtime[j], times[j][k]);
	}
    
}
    total_bytes = bytes[0] + bytes[1] + bytes [2] + bytes [3];
#ifdef VERBOSE
    printf ("Average Rate (MB/s): %11.4f \n", 1.0E-06 * total_bytes*NTIMES/total_time);
    printf ("note: in this version, the average rate per function\n");
    printf ("can not be provided, use tracing to check it\n");
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

/* ------------------------------------------------------------------------------------------------------------------------*/
    printf("\nMarking starting point.. Timestamp: %f.", s);
    printf("\nMarking starting point.. Timestamp: %f.", e);
    printf("\nInference completed in %f seconds.", (e-s));

    elapsed = 1000000 * (stop.tv_sec - start.tv_sec);
    elapsed += stop.tv_usec - start.tv_usec;

    // threads
    #ifdef OMP
        printf("threads: ");
        printf ("%d;\t\n", omp_get_num_threads() );
    #endif

    // time in usecs
    printf("time: ");
    printf ("%lu;\t", elapsed);
    // performance in MFLOPS
    printf("MFLOPS: %lu\n", (unsigned long)((((float)N)*((float)N)*((float)N)*2)/elapsed));
#endif
    }

    /* Destroy the enclave */
    sgx_destroy_enclave(global_eid);
#ifdef VERBOSE
    printf("Info: SampleEnclave successfully returned.\n");
#endif
    return 0;
}
