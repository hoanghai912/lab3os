#include <stdio.h>
#include "pthread.h"
#include <stdint.h>
#include <stdlib.h>

void *hello(void* tid)
{
    long i = (long)tid;
    printf("Hello from thread %ld\n", i);
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid[10];
    long i;
    for (i = 0; i<10; i++)
    {
        pthread_create(&tid[i], NULL, hello, (void*)i);
        pthread_join(tid[i], NULL);
    }
    pthread_exit(NULL);

    return 0;
}