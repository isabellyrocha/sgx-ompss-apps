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

//long N;
//long CHUNK_SIZE;
/* Application entry */
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

    unsigned long N, CHUNK_SIZE;
    struct timeval start;
    struct timeval stop;
    unsigned long elapsed;

    // application inicializations
//    init(argc, argv, &N, &DIM, &BSIZE);


    if (argc != 3) {
        fprintf(stderr, "Usage: %s <vector size in K> <chunk size in K> \n", argv[0]);
        return 1;
    }

    //N = atol(argv[1]) * 1024L;
    CHUNK_SIZE = atol(argv[2]) * 1024L;
    N = atol(argv[1]) * CHUNK_SIZE * 1024L;

    double *A = (double *) malloc(N*sizeof(double));
    double *B = (double *) malloc(N*sizeof(double));

    initialize(N, A);
    initialize(N, B);

    gettimeofday(&start,NULL);
    double s = (double)start.tv_sec + (double)start.tv_usec * .000001;

    long actual_size;
    int j;
    double result;

    const long N_CHUNKS = N/CHUNK_SIZE + (N % CHUNK_SIZE != 0);
    double *C = (double *) malloc(N_CHUNKS*sizeof(double));

    result=0.0;
    j=0;
    for (long i=0; i<N; i+=CHUNK_SIZE) {

        actual_size = (N - i >= CHUNK_SIZE) ? CHUNK_SIZE : N - i;

        // OMPSS: What are the 2 inputs and the in/out data for this task ?
        #pragma omp task in( A[i;actual_size], B[i; actual_size] ) inout( C[j;1] )
        {
        //    C[j]=0;
        //    for (long ii=0; ii<actual_size; ii++)
        //        C[j]+= A[i+ii] * B[i+ii];
        ecall_dot_prod(global_eid, A, B, C, i, j, actual_size);
        }

        // OMPSS: This task depends on an single element of C and will resultumulate the result on result.
        #pragma omp task label( increment ) firstprivate( j ) in( C[j;1] ) commutative( result )
        result += C[j];

        j++;
    }

    // OMPSS: We must make sure that all computations have ended before returning a value
    #pragma omp taskwait

    gettimeofday(&stop,NULL);
    double e =(double)stop.tv_sec + (double)stop.tv_usec * .000001;

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

    printf("\nResult of Dot product i= %le\n", result);
    // time in usecs
    printf("time: ");
    printf ("%lu;\t", elapsed);
    // performance in MFLOPS
    printf("MFLOPS: %lu\n", (unsigned long)((((float)N)*((float)N)*((float)N)*2)/elapsed));

    /* Destroy the enclave */
    sgx_destroy_enclave(global_eid);
    
    printf("Info: SampleEnclave successfully returned.\n");


    printf("%d,%d,%f\n", (int) s, (int) e, (e-s));
//    printf("Enter a character before exit ...\n");
//    getchar();
    return 0;
}
