#include "../Enclave.h"
#include "Enclave_t.h"
#include "sgx_thread.h"

static size_t global_counter = 0;
static sgx_thread_mutex_t global_mutex = SGX_THREAD_MUTEX_INITIALIZER;
int offset = 13;

#define BUFFER_SIZE 50

typedef struct {
    int buf[BUFFER_SIZE];
    int occupied;
    int nextin;
    int nextout;
    sgx_thread_mutex_t mutex;
    sgx_thread_cond_t more;
    sgx_thread_cond_t less;
} cond_buffer_t;

static cond_buffer_t buffer = {{0, 0, 0, 0, 0, 0}, 0, 0, 0,
    SGX_THREAD_MUTEX_INITIALIZER, SGX_THREAD_COND_INITIALIZER, SGX_THREAD_COND_INITIALIZER};

/*
 * ecall_increase_counter:
 *   Utilize thread APIs inside the enclave.
 */
size_t ecall_increase_counter(void)
{
    size_t ret = 0;
    for (int i = 0; i < LOOPS_PER_THREAD; i++) {
        sgx_thread_mutex_lock(&global_mutex);
        /* mutually exclusive adding */
        size_t tmp = global_counter;
        global_counter = ++tmp;
        if (4*LOOPS_PER_THREAD == global_counter)
            ret = global_counter;
        sgx_thread_mutex_unlock(&global_mutex);
    }
    return ret;
}

void ecall_producer(void)
{
    for (int i = 0; i < 4*LOOPS_PER_THREAD; i++) {
        cond_buffer_t *b = &buffer;
        sgx_thread_mutex_lock(&b->mutex);
        while (b->occupied >= BUFFER_SIZE)
            sgx_thread_cond_wait(&b->less, &b->mutex);
        b->buf[b->nextin] = b->nextin;
        b->nextin++;
        b->nextin %= BUFFER_SIZE;
        b->occupied++;
        sgx_thread_cond_signal(&b->more);
        sgx_thread_mutex_unlock(&b->mutex);
    }
}

void ecall_consumer(void)
{
    for (int i = 0; i < LOOPS_PER_THREAD; i++) {
        cond_buffer_t *b = &buffer;
        sgx_thread_mutex_lock(&b->mutex);
        while(b->occupied <= 0)
            sgx_thread_cond_wait(&b->more, &b->mutex);
        b->buf[b->nextout++] = 0;
        b->nextout %= BUFFER_SIZE;
        b->occupied--;
        sgx_thread_cond_signal(&b->less);
        sgx_thread_mutex_unlock(&b->mutex);
    }
}

void encrypt(double* matrix, int NB) {
    for (int i = 0; i < NB; i++) {
        matrix[i] = matrix[i] + offset;
    }
}


void decrypt(double* matrix, int NB) {
    for (int i = 0; i < NB; i++) {
        matrix[i] = matrix[i] - offset;
    }
}

void ecall_dot_prod(double *a,
                    double *b,
                    double *c, 
                    long i,
                    long j,
                    long bs)
{
            decrypt(a, bs);
            decrypt(b, bs);
            c[j]=0;
            for (long ii=0; ii<bs; ii++)
                c[j]+= a[i+ii] * b[i+ii];
            encrypt(a, bs);
            encrypt(b, bs);
}

void ecall_copy_task(double *a, double *c, int bs)
{
        decrypt(a, bs);
        for (int j = 0; j < bs; j++)
                c[j] = a[j];
        encrypt(a, bs);
        encrypt(c, bs);
}

void ecall_scale_task(double *b, double *c, double scalar, int bs)
{
        decrypt(c, bs);
        int j;
        for (j = 0; j < bs; j++)
            b[j] = scalar*c[j];
        encrypt(b, bs);
        encrypt(c, bs);
        
}

void ecall_add_task(double *a, double *b, double *c, int bs)
{
        decrypt(a, bs);
        decrypt(b, bs);
        for (int j = 0; j < bs; j++)
           c[j] = a[j]+b[j];
        encrypt(a, bs);
        encrypt(b, bs);
        encrypt(c, bs);
}

void ecall_triad_task(double *a, double *b, double *c, double scalar, int bs)
{
        decrypt(b, bs);
        decrypt(c, bs);
        for (int j = 0; j < bs; j++)
            a[j] = b[j]+scalar*c[j];
        encrypt(a, bs);
        encrypt(b, bs);
        encrypt(c, bs);
}
