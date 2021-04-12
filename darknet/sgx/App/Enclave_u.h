#ifndef ENCLAVE_U_H__
#define ENCLAVE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */

#include "dnet_types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OCALL_OPEN_FILE_DEFINED__
#define OCALL_OPEN_FILE_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_open_file, (char* filename, flag oflag));
#endif
#ifndef OCALL_CLOSE_FILE_DEFINED__
#define OCALL_CLOSE_FILE_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_close_file, (void));
#endif
#ifndef OCALL_FREAD_DEFINED__
#define OCALL_FREAD_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fread, (void* ptr, size_t size, size_t nmemb));
#endif
#ifndef OCALL_FWRITE_DEFINED__
#define OCALL_FWRITE_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_fwrite, (void* ptr, size_t size, size_t nmemb));
#endif
#ifndef OCALL_PRINT_STRING_DEFINED__
#define OCALL_PRINT_STRING_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_string, (const char* str));
#endif
#ifndef OCALL_FREE_SEC_DEFINED__
#define OCALL_FREE_SEC_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_free_sec, (section* sec));
#endif
#ifndef OCALL_FREE_LIST_DEFINED__
#define OCALL_FREE_LIST_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_free_list, (list* list));
#endif
#ifndef OCALL_TIMESTAMP_START_DEFINED__
#define OCALL_TIMESTAMP_START_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_timestamp_start, (void));
#endif
#ifndef OCALL_TIMESTAMP_END_DEFINED__
#define OCALL_TIMESTAMP_END_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_timestamp_end, (void));
#endif

sgx_status_t ecall_classify(sgx_enclave_id_t eid, list* sections, list* labels, char* weights, float thresh, image im);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
