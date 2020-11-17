# include <stdio.h>
# include <math.h>
# include <float.h>
# include <stdlib.h>
//# include "limits.h"
# include <sys/time.h>
# include "omp.h"

# define HLINE "-------------------------------------------------------------\n"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
# include <unistd.h>
# include <pwd.h>
# define MAX_PATH FILENAME_MAX
# define VERBOSE
#include <nanos_omp.h>
#include "sgx_urts.h"
#include "App.h"
#include "Enclave_u.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include "cholesky.h"

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

//void cholesky_blocked(const int ts, const int nt, double** Ah)
void cholesky_blocked(const int ts, const int nt, double** Ah)
{
   for (int k = 0; k < nt; k++) {

      // Diagonal Block factorization
#pragma omp task inout(Ah[k*nt+k])
      ecall_omp_potrf (global_eid,Ah[k*nt+k], ts, ts);
      printf("ecall_omp_potrf..\n");
      // Triangular systems
      for (int i = k + 1; i < nt; i++) {
#pragma omp task in(Ah[k*nt+k]) inout(Ah[k*nt+i])
         ecall_omp_trsm (global_eid,Ah[k*nt+k], Ah[k*nt+i], ts, ts);
      }
      printf("ecall_omp_trsm..\n");
      // Update trailing matrix
      for (int i = k + 1; i < nt; i++) {
         for (int j = k + 1; j < i; j++) {
#pragma omp task in(Ah[k*nt+i], Ah[k*nt+j]) inout(Ah[j*nt+i])
            ecall_omp_gemm (global_eid, Ah[k*nt+i], Ah[k*nt+j], Ah[j*nt+i], ts, ts);
         }
	 printf("ecall_omp_gemm..\n");
#pragma omp task in(Ah[k*nt+i]) inout(Ah[i*nt+i])
         ecall_omp_syrk (global_eid, Ah[k*nt+i], Ah[i*nt+i], ts, ts);
      }
      printf("ecall_omp_syrk..\n");

   }
#pragma omp taskwait
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

   char *result[3] = {"n/a","sucessful","UNSUCCESSFUL"};
   const double eps = BLAS_dfpinfo( blas_eps );

   if ( argc < 4) {
      printf( "cholesky matrix_size block_size check\n" );
      exit( -1 );
   }
   const int  n = atoi(argv[1]); // matrix size
   const int ts = atoi(argv[2]); // tile size
   int check    = atoi(argv[3]); // check result?

   // Allocate matrix
   double * const matrix = (double *) malloc(n * n * sizeof(double));
   assert(matrix != NULL);

   // Init matrix
   initialize_matrix(n, ts, matrix);

   // Allocate matrix
   double * const original_matrix = (double *) malloc(n * n * sizeof(double));
   assert(original_matrix != NULL);

   const int nt = n / ts;

   // Allocate blocked matrix
   double** Ah = (double **) malloc(nt*nt*sizeof(double *));

   for (int i = 0; i < nt*nt; i++) {
      //for (int j = 0; j < nt; j++) {
         Ah[i] = (double*) malloc(ts * ts * sizeof(double));
         assert(Ah[i] != NULL);
      //}
   }

   for (int i = 0; i < n * n; i++ ) {
      original_matrix[i] = matrix[i];
   }

#ifdef VERBOSE
   printf ("Executing ...\n");
#endif

//   convert_to_blocks(ts, nt, n, (double(*)[n]) matrix, Ah);
    // Convert to blocks
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ((double * (*) [nt])Ah)[i/ts][j/ts][(i%ts)*ts+j%ts] = matrix[i*n+j];
        }
    }

   printf("Convet blocks..\n");
   const float t1 = get_time();
   cholesky_blocked(ts, nt, Ah);

   printf("Convet blocks done..\n");
   const float t2 = get_time() - t1;
   //convert_to_linear(ts, nt, n, Ah, (double (*)[n]) matrix);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //((double * (*) [nt])Ah)[i/ts][j/ts][(i%ts)*ts+j%ts] = matrix[i*n+j];
            matrix[i*n+j] = ((double * (*) [nt])Ah)[i/ts][j/ts][(i%ts)*ts+j%ts]; 
       }
    }

   if ( check ) {
      const char uplo = 'L';
      if ( check_factorization( n, original_matrix, matrix, n, uplo, eps) ) check++;
   }

   free(original_matrix);

   float time = t2;
   float gflops = (((1.0 / 3.0) * n * n * n) / ((time) * 1.0e+9));

   // Print results
#ifdef VERBOSE
   printf( "============ CHOLESKY RESULTS ============\n" );
   printf( "  matrix size:          %dx%d\n", n, n);
   printf( "  block size:           %dx%d\n", ts, ts);
   printf( "  number of threads:    %d\n", omp_get_num_threads());
   printf( "  time (s):             %f\n", time);
   printf( "  performance (gflops): %f\n", gflops);
   printf( "==========================================\n" );
   printf( "test:%s-%d-%d:threads:%2d:result:%s:gflops:%f\n", argv[0], n, ts, omp_get_num_threads(), result[check], gflops );
#endif

    gettimeofday(&stop,NULL);

   // Free blocked matrix
   for (int i = 0; i < nt*nt; i++) {
      //for (int j = 0; j < nt; j++) {
         assert(Ah[i] != NULL);
         free(Ah[i]);
      //}
   }

   // Free matrix
   free(matrix);
   free(Ah);

/* ------------------------------------------------------------------------------------------------------------------------*/


    double e =(double)stop.tv_sec + (double)stop.tv_usec * .000001;
#ifdef VERBOSE
    printf("\nMarking starting point.. Timestamp: %f.", s);
    printf("\nMarking starting point.. Timestamp: %f.", e);
    printf("\nInference completed in %f seconds.", (e-s));
#endif
    elapsed = 1000000 * (stop.tv_sec - start.tv_sec);
    elapsed += stop.tv_usec - start.tv_usec;
#ifdef VERBOSE
    // threads
    #ifdef OMP
        printf("threads: ");
        printf ("%d;\t\n", omp_get_num_threads() );
    #endif

    // time in usecs
    printf("time: ");
    printf ("%lu;\t", elapsed);
    // performance in MFLOPS
    printf("MFLOPS: %lu\n", (unsigned long)((((float)n)*((float)n)*((float)n)*2)/elapsed));
#endif

    printf("%d,%d,%f\n", (int) s, (int) e, (e-s));
    }

    /* Destroy the enclave */
    sgx_destroy_enclave(global_eid);
#ifdef VERBOSE
    printf("Info: SampleEnclave successfully returned.\n");
#endif

    return 0;
}
