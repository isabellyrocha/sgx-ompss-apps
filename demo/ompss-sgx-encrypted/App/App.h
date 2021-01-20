#ifndef _APP_H_
#define _APP_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "sgx_error.h"       /* sgx_status_t */
#include "sgx_eid.h"     /* sgx_enclave_id_t */

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
# include <unistd.h>
#include "Enclave_u.h"
#include "sgx_urts.h"
# include <pwd.h>
#include <nanos_omp.h>
#include <string>


# define MAX_PATH FILENAME_MAX

#ifndef TRUE
# define TRUE 1
#endif

#ifndef FALSE
# define FALSE 0
#endif

# define TOKEN_FILENAME   "enclave.token"
# define ENCLAVE_FILENAME "enclave.signed.so"

extern sgx_enclave_id_t global_eid;    /* global enclave id */

#if defined(__cplusplus)
extern "C" {
#endif

void edger8r_array_attributes(void);
void edger8r_type_attributes(void);
void edger8r_pointer_attributes(void);
void edger8r_function_attributes(void);

void ecall_libc_functions(void);
void ecall_libcxx_functions(void);
void ecall_thread_functions(void);
double timestemp();

#if defined(__cplusplus)
}
#endif

#endif /* !_APP_H_ */
