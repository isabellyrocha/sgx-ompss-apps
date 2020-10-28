/*
 * Copyright (C) 2011-2019 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
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
#include <string>
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

double **A;
double **B;
double **C;

static void print_matrix(double *A[8][8])
{
    int i, j;
    for (i=0; i < 2 ; i++ ) {
        for (j=0; j < 2 ; j++ )
            printf ("%d, %d: %f ", i, j, (*A)[i][j]);
        printf ("\n");
    }
}

static void print_matrix2(double *A)
{
    int i, j;
    for (i=0; i < 2 ; i++ ) {
        for (j=0; j < 2 ; j++ )
            printf ("   %d, %d: %f ", i, j, A[i*128+j]);
    printf ("\n");
  }
}

static double timestemp() {
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void fill_random(double *Alin, int NN)
{
    int i;
    for (i = 0; i < NN; i++) {
        Alin[i]=((double)rand())/((double)RAND_MAX);
    }
}

void init(unsigned long argc, char **argv, unsigned long * N_p, unsigned long * DIM_p, unsigned long * BSIZE_p)
{
    unsigned long ISEED[4] = {0,0,0,1};
    unsigned long IONE=1;
    unsigned long DIM, BSIZE;
    char UPLO='n';
    float FZERO=0.0;

    if (argc==3) {
        DIM=atoi(argv[1]);
        BSIZE=atoi(argv[2]);
    } else {
        printf("usage: %s DIM BSIZE\n",argv[0]);
        exit(0);
    }

    // matrix init
//    unsigned long N=BSIZE*DIM; 
    unsigned long N=DIM;
    unsigned long NN=N*N;
    int i, j;

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

    for (i = 0; i < DIM*DIM; i++) {
        A[i] = (double *) malloc(BSIZE*BSIZE*sizeof(double));
        B[i] = (double *) malloc(BSIZE*BSIZE*sizeof(double));
        C[i] = (double *) malloc(BSIZE*BSIZE*sizeof(double));
    }

    // Convert to blocks
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            ((double * (*) [DIM])A)[i/BSIZE][j/BSIZE][(i%BSIZE)*BSIZE+j%BSIZE] = Alin[j*N+i];
            ((double * (*) [DIM])B)[i/BSIZE][j/BSIZE][(i%BSIZE)*BSIZE+j%BSIZE] = Blin[j*N+i];
            ((double * (*) [DIM])C)[i/BSIZE][j/BSIZE][(i%BSIZE)*BSIZE+j%BSIZE] = Clin[j*N+i];
        }
    }

//    print_matrix((float *(*) [8])C);

    free(Alin);
    free(Blin);
    free(Clin);
}

std::string get_size(long size) {
    if (size >= 32) return "large";
    if (size >= 16) return "medium";
    return "small";
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

/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
//for (int rounds = 0; rounds < 10; rounds++) {

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

    unsigned long NB, BSIZE, N, DIM;
    struct timeval start;
    struct timeval stop;
    unsigned long elapsed;

    // application inicializations
    init(argc, argv, &N, &DIM, &BSIZE);

    
    unsigned i, j, k;

    gettimeofday(&start,NULL);
    double s = (double)start.tv_sec + (double)start.tv_usec * .000001;

    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++)
            for (k = 0; k < DIM; k++) {
                #pragma omp task in(A[i][k], B[k][j]) inout(C[i][j]) no_copy_deps
//                #pragma omp task in(A[BSIZE][BSIZE], B[BSIZE][BSIZE]) inout(C[BSIZE][BSIZE]) no_copy_deps
                {
                ecall_matmul_u(global_eid, &A[i][k], &B[k][j], &C[i][j], BSIZE);
                }
            }

    #pragma omp taskwait
    gettimeofday(&stop,NULL);
    double e =(double)stop.tv_sec + (double)stop.tv_usec * .000001;


//    print_matrix2(&C[DIM-1][DIM-1]);
    elapsed = 1000000 * (stop.tv_sec - start.tv_sec);
    elapsed += stop.tv_usec - start.tv_usec;

    // threads
    #ifdef OMP
        printf("threads: ");
        printf ("%d;\t", omp_get_num_threads() );
    #endif
   
    // time in usecs
//    printf("time: ");
//    printf ("%lu;\t", elapsed);
    // performance in MFLOPS
//    printf("MFLOPS: %lu\n", (unsigned long)((((float)N)*((float)N)*((float)N)*2)/elapsed));
    

    /* Destroy the enclave */
    sgx_destroy_enclave(global_eid);
    
//    printf("Info: SampleEnclave successfully returned.\n");
    char *size;
//    #ifdef OMP
    if (BSIZE >= 32) size = "large";
    else if (BSIZE >= 16) size = "medium";
    else size = "small";
    printf("%d,%d,%f\n", (int) s, (int) e, (e-s));
//    #endif
//    printf("Enter a character before exit ...\n");
//    getchar();
  //  }
    return 0;
}
