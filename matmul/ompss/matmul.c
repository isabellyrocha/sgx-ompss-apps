#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "omp.h"

//#define BSIZE 128

#pragma omp task in([NB][NB]A, [NB][NB]B) inout([NB][NB]C)
void matmul(double  *A, double *B, double *C, unsigned long NB)
{
  int i, j, k, I;
  double tmp;
  for (i = 0; i < NB; i++)
  {
    I=i*NB;
    for (j = 0; j < NB; j++)
    {
      tmp=C[I+j];
      for (k = 0; k < NB; k++)
      {
        tmp+=A[I+k]*B[k*NB+j];
      }
      C[I+j]=tmp;
    }
  }
}

void compute(struct timeval *start, struct timeval *stop, unsigned long NB, unsigned long DIM,
             double *A[DIM][DIM], double *B[DIM][DIM], double *C[DIM][DIM])
{
  unsigned i, j, k;

  gettimeofday(start,NULL);
  
  for (i = 0; i < DIM; i++)
    for (j = 0; j < DIM; j++)
      for (k = 0; k < DIM; k++)
        matmul ((double *)A[i][k], (double *)B[k][j], (double *)C[i][j], NB);

  #pragma omp taskwait
  gettimeofday(stop,NULL);
}

// -------------------------------------------------------------------------------------------------

double **A;
double **B;
double **C;

static void convert_to_blocks(unsigned long NB,unsigned long DIM, unsigned long N, double *Alin, double *A[DIM][DIM])
{
  unsigned i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      A[i/NB][j/NB][(i%NB)*NB+j%NB] = Alin[j*N+i];
    }
  }

}

void fill_random(double *Alin, int NN)
{
  int i;
  for (i = 0; i < NN; i++)
  {
    Alin[i]=((double)rand())/((double)RAND_MAX);
  }
}

void init (unsigned long argc, char **argv, unsigned long * N_p, unsigned long * DIM_p, unsigned long *BSIZE_p)
{
  unsigned long ISEED[4] = {0,0,0,1};
  unsigned long IONE=1;
  unsigned long DIM, BSIZE;
  char UPLO='n';
  double FZERO=0.0;

  if (argc==3)
  {
    DIM=atoi(argv[1]);
    BSIZE=atoi(argv[2]);
  }
  else
  {
    printf("usage: %s DIM BSIZE\n",argv[0]);
    exit(0);
  }

  // matrix init
  unsigned long N=BSIZE*DIM;
  unsigned long NN=N*N;
  int i;

  *N_p=N;
  *DIM_p=DIM;
  *BSIZE_p=BSIZE;

  // linear matrix
  double *Alin = (double *) malloc(NN * sizeof(double));
  double *Blin = (double *) malloc(NN * sizeof(double));
  double *Clin = (double *) malloc(NN * sizeof(double));

  // fill the matrix with random values
  srand(0);
  fill_random(Alin,NN);
  fill_random(Blin,NN);
  for (i=0; i < NN; i++)
    Clin[i]=0.0;

  A = (double **) malloc(DIM*DIM*sizeof(double *));
  B = (double **) malloc(DIM*DIM*sizeof(double *));
  C = (double **) malloc(DIM*DIM*sizeof(double *));
  
  for (i = 0; i < DIM*DIM; i++)
  {
     A[i] = (double *) malloc(BSIZE*BSIZE*sizeof(double));
     B[i] = (double *) malloc(BSIZE*BSIZE*sizeof(double));
     C[i] = (double *) malloc(BSIZE*BSIZE*sizeof(double));
  }
  convert_to_blocks(BSIZE,DIM, N, Alin, (double * (*)[DIM])A);
  convert_to_blocks(BSIZE,DIM, N, Blin, (double * (*) [DIM])B);
  convert_to_blocks(BSIZE,DIM, N, Clin, (double *(*) [DIM])C);

  free(Alin);
  free(Blin);
  free(Clin);

}


int main(int argc, char *argv[])
{
  // local vars
  unsigned long NB, N, DIM, BSIZE;
  
  struct timeval start;
  struct timeval stop;
  unsigned long elapsed;

  // application inicializations
  init(argc, argv, &N, &DIM, &BSIZE);

  // compute with CellSs
  compute(&start, &stop,(unsigned long) BSIZE, DIM, (void *)A, (void *)B, (void *)C);

  double s = (double)start.tv_sec + (double)start.tv_usec * .000001;
  double e = (double)stop.tv_sec + (double)stop.tv_usec * .000001;
  
  elapsed = 1000000 * (stop.tv_sec - start.tv_sec);
  elapsed += stop.tv_usec - start.tv_usec;
// threads
//  printf("threads: ");
//  printf ("%d;\t\n", omp_get_num_threads() );
// time in usecs
//  printf("time: ");
//  printf ("%lu;\t", elapsed);
// performance in MFLOPS
//  printf("MFLOPS: %lu\n", (unsigned long)((((double)N)*((double)N)*((double)N)*2)/elapsed));

  printf("%d,%d,%f", (int)s, (int)e, (e-s));

  return 0;
}

