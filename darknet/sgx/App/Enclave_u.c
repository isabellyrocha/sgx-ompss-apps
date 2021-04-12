#include "Enclave_u.h"
#include <errno.h>

typedef struct ms_ecall_classify_t {
	list* ms_sections;
	list* ms_labels;
	char* ms_weights;
	float ms_thresh;
	image ms_im;
} ms_ecall_classify_t;

typedef struct ms_ocall_open_file_t {
	char* ms_filename;
	flag ms_oflag;
} ms_ocall_open_file_t;

typedef struct ms_ocall_fread_t {
	void* ms_ptr;
	size_t ms_size;
	size_t ms_nmemb;
} ms_ocall_fread_t;

typedef struct ms_ocall_fwrite_t {
	void* ms_ptr;
	size_t ms_size;
	size_t ms_nmemb;
} ms_ocall_fwrite_t;

typedef struct ms_ocall_print_string_t {
	const char* ms_str;
} ms_ocall_print_string_t;

typedef struct ms_ocall_free_sec_t {
	section* ms_sec;
} ms_ocall_free_sec_t;

typedef struct ms_ocall_free_list_t {
	list* ms_list;
} ms_ocall_free_list_t;

static sgx_status_t SGX_CDECL Enclave_ocall_open_file(void* pms)
{
	ms_ocall_open_file_t* ms = SGX_CAST(ms_ocall_open_file_t*, pms);
	ocall_open_file(ms->ms_filename, ms->ms_oflag);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_close_file(void* pms)
{
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ocall_close_file();
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fread(void* pms)
{
	ms_ocall_fread_t* ms = SGX_CAST(ms_ocall_fread_t*, pms);
	ocall_fread(ms->ms_ptr, ms->ms_size, ms->ms_nmemb);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_fwrite(void* pms)
{
	ms_ocall_fwrite_t* ms = SGX_CAST(ms_ocall_fwrite_t*, pms);
	ocall_fwrite(ms->ms_ptr, ms->ms_size, ms->ms_nmemb);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ocall_print_string(ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_free_sec(void* pms)
{
	ms_ocall_free_sec_t* ms = SGX_CAST(ms_ocall_free_sec_t*, pms);
	ocall_free_sec(ms->ms_sec);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_free_list(void* pms)
{
	ms_ocall_free_list_t* ms = SGX_CAST(ms_ocall_free_list_t*, pms);
	ocall_free_list(ms->ms_list);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_timestamp_start(void* pms)
{
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ocall_timestamp_start();
	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_timestamp_end(void* pms)
{
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ocall_timestamp_end();
	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[9];
} ocall_table_Enclave = {
	9,
	{
		(void*)Enclave_ocall_open_file,
		(void*)Enclave_ocall_close_file,
		(void*)Enclave_ocall_fread,
		(void*)Enclave_ocall_fwrite,
		(void*)Enclave_ocall_print_string,
		(void*)Enclave_ocall_free_sec,
		(void*)Enclave_ocall_free_list,
		(void*)Enclave_ocall_timestamp_start,
		(void*)Enclave_ocall_timestamp_end,
	}
};
sgx_status_t ecall_classify(sgx_enclave_id_t eid, list* sections, list* labels, char* weights, float thresh, image im)
{
	sgx_status_t status;
	ms_ecall_classify_t ms;
	ms.ms_sections = sections;
	ms.ms_labels = labels;
	ms.ms_weights = weights;
	ms.ms_thresh = thresh;
	ms.ms_im = im;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave, &ms);
	return status;
}

