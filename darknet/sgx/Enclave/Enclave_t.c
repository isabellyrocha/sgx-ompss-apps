#include "Enclave_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */
#include "sgx_lfence.h" /* for sgx_lfence */

#include <errno.h>
#include <mbusafecrt.h> /* for memcpy_s etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_ENCLAVE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_within_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define ADD_ASSIGN_OVERFLOW(a, b) (	\
	((a) += (b)) < (b)	\
)


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

static sgx_status_t SGX_CDECL sgx_ecall_classify(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_classify_t));
	//
	// fence after pointer checks
	//
	sgx_lfence();
	ms_ecall_classify_t* ms = SGX_CAST(ms_ecall_classify_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	list* _tmp_sections = ms->ms_sections;
	list* _tmp_labels = ms->ms_labels;
	char* _tmp_weights = ms->ms_weights;



	ecall_classify(_tmp_sections, _tmp_labels, _tmp_weights, ms->ms_thresh, ms->ms_im);


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv; uint8_t is_switchless;} ecall_table[1];
} g_ecall_table = {
	1,
	{
		{(void*)(uintptr_t)sgx_ecall_classify, 0, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[9][1];
} g_dyn_entry_table = {
	9,
	{
		{0, },
		{0, },
		{0, },
		{0, },
		{0, },
		{0, },
		{0, },
		{0, },
		{0, },
	}
};


sgx_status_t SGX_CDECL ocall_open_file(char* filename, flag oflag)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_open_file_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_open_file_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_open_file_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_open_file_t));
	ocalloc_size -= sizeof(ms_ocall_open_file_t);

	ms->ms_filename = filename;
	ms->ms_oflag = oflag;
	status = sgx_ocall(0, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_close_file(void)
{
	sgx_status_t status = SGX_SUCCESS;
	status = sgx_ocall(1, NULL);

	return status;
}
sgx_status_t SGX_CDECL ocall_fread(void* ptr, size_t size, size_t nmemb)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_fread_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fread_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fread_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fread_t));
	ocalloc_size -= sizeof(ms_ocall_fread_t);

	ms->ms_ptr = ptr;
	ms->ms_size = size;
	ms->ms_nmemb = nmemb;
	status = sgx_ocall(2, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_fwrite(void* ptr, size_t size, size_t nmemb)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_ptr = nmemb * size;

	ms_ocall_fwrite_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_fwrite_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(ptr, _len_ptr);

	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (ptr != NULL) ? _len_ptr : 0))
		return SGX_ERROR_INVALID_PARAMETER;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_fwrite_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_fwrite_t));
	ocalloc_size -= sizeof(ms_ocall_fwrite_t);

	if (ptr != NULL) {
		ms->ms_ptr = (void*)__tmp;
		if (memcpy_s(__tmp, ocalloc_size, ptr, _len_ptr)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_ptr);
		ocalloc_size -= _len_ptr;
	} else {
		ms->ms_ptr = NULL;
	}
	
	ms->ms_size = size;
	ms->ms_nmemb = nmemb;
	status = sgx_ocall(3, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_print_string(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_print_string_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_string_t);
	void *__tmp = NULL;


	CHECK_ENCLAVE_POINTER(str, _len_str);

	if (ADD_ASSIGN_OVERFLOW(ocalloc_size, (str != NULL) ? _len_str : 0))
		return SGX_ERROR_INVALID_PARAMETER;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_string_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_string_t));
	ocalloc_size -= sizeof(ms_ocall_print_string_t);

	if (str != NULL) {
		ms->ms_str = (const char*)__tmp;
		if (_len_str % sizeof(*str) != 0) {
			sgx_ocfree();
			return SGX_ERROR_INVALID_PARAMETER;
		}
		if (memcpy_s(__tmp, ocalloc_size, str, _len_str)) {
			sgx_ocfree();
			return SGX_ERROR_UNEXPECTED;
		}
		__tmp = (void *)((size_t)__tmp + _len_str);
		ocalloc_size -= _len_str;
	} else {
		ms->ms_str = NULL;
	}
	
	status = sgx_ocall(4, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_free_sec(section* sec)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_free_sec_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_free_sec_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_free_sec_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_free_sec_t));
	ocalloc_size -= sizeof(ms_ocall_free_sec_t);

	ms->ms_sec = sec;
	status = sgx_ocall(5, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_free_list(list* list)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_ocall_free_list_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_free_list_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_free_list_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_free_list_t));
	ocalloc_size -= sizeof(ms_ocall_free_list_t);

	ms->ms_list = list;
	status = sgx_ocall(6, ms);

	if (status == SGX_SUCCESS) {
	}
	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_timestamp_start(void)
{
	sgx_status_t status = SGX_SUCCESS;
	status = sgx_ocall(7, NULL);

	return status;
}
sgx_status_t SGX_CDECL ocall_timestamp_end(void)
{
	sgx_status_t status = SGX_SUCCESS;
	status = sgx_ocall(8, NULL);

	return status;
}
