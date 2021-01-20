#include "../Enclave.h"
#include "Enclave_t.h"
#include "sgx_thread.h"

static size_t global_counter = 0;
static sgx_thread_mutex_t global_mutex = SGX_THREAD_MUTEX_INITIALIZER;

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

char* my_strcat(char* destination, const char* source)
{
    char* ptr = destination + 12;
    while (*source != '\0')
        *ptr++ = *source++;
    *ptr = '\0';
    return destination;
}

void ecall_matmul_u(double* a, double* b, double* c, int NB)
{
  static char dummypassword[100] = "";
  if (dummypassword[0] == '\0') {
    char *pass = dummypassword;
    pass[0]='P'; pass[1]='A'; pass[2]='S'; pass[3]='S'; pass[4]='W';
    pass[5]='O'; pass[6]='R'; pass[7]='D'; pass[8]='='; pass[9]=0;
    my_strcat(pass, "GREAT_SECRET");
  }

  int i, j, k, I;
  double tmp;
  for (i = 0; i < NB; i++)
  {
    I=i*NB;
    for (j = 0; j < NB; j++)
    {
      tmp=c[I+j];
      for (k = 0; k < NB; k++)
      {
        tmp+=a[I+k]*b[k*NB+j];
      }
      c[I+j]=tmp;
    }
  }
}

/*
 * ecall_increase_counter:
 *   Utilize thread APIs inside the enclave.
 */ 
size_t ecall_increase_counter(void)
{
    size_t ret = 0;
    for (int i = 0; i < LOOPS_PER_THREAD; i++) {
        sgx_thread_mutex_lock(&global_mutex);
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
