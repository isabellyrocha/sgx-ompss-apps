#include "Enclave.h"
#include "sgx_trts.h"
#include "sgx_thread.h"
#include "Enclave_t.h" 
#include <stdarg.h>
#include <stdio.h>
#include "dnet_sgx_utils.h"
#include "../App/dnet-in/src/darknet.h"

void printf(const char *fmt, ...)
{
    PRINT_BLOCK();
}

void sgx_printf(const char *fmt, ...)
{
    PRINT_BLOCK();
}

void ecall_classify(list *sections, list *labels, char* weights, float thresh, image im)
{
    test_detector(sections, weights, thresh, 0.4, 0, 0, 0, NULL, 0, 1, im);
}
