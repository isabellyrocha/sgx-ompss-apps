#ifndef ENCLAVE_T_H__
#define ENCLAVE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "dnet_types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void ecall_classify(list* sections, list* labels, char* weights, float thresh, image im);

sgx_status_t SGX_CDECL ocall_open_file(char* filename, flag oflag);
sgx_status_t SGX_CDECL ocall_close_file(void);
sgx_status_t SGX_CDECL ocall_fread(void* ptr, size_t size, size_t nmemb);
sgx_status_t SGX_CDECL ocall_fwrite(void* ptr, size_t size, size_t nmemb);
sgx_status_t SGX_CDECL ocall_print_string(const char* str);
sgx_status_t SGX_CDECL ocall_free_sec(section* sec);
sgx_status_t SGX_CDECL ocall_free_list(list* list);
sgx_status_t SGX_CDECL ocall_timestamp_start(void);
sgx_status_t SGX_CDECL ocall_timestamp_end(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
