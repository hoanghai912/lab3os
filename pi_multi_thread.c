#include <stdio.h>
#include "pthread.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUMTHREADS 8

void* in_point(void *arg)
{
    float *count = (float*)malloc(sizeof(float));
    *count = 0;
    unsigned int t = time(NULL);
    long points = (long)arg;
    for (long i = 0; i<points; i++)
    {
        double x_cor = (double)rand_r(&t)/RAND_MAX;
        double y_cor = (double)rand_r(&t)/RAND_MAX;
        if (x_cor*x_cor + y_cor*y_cor <= 1) *count += 1;
    }

    pthread_exit((void*)count);
}

int main()
{
    pthread_t threads[NUMTHREADS];
    double nPoints;
    scanf("%lf", &nPoints);
    long limit = nPoints / NUMTHREADS;
    float total = 0;
    void *status;

    clock_t start = clock();
    for (int i = 0; i<NUMTHREADS; i++)
    {
        pthread_create(&threads[i], NULL, in_point, (void*)limit);
    }

    for (int i = 0; i<NUMTHREADS; i++)
    {
        pthread_join(threads[i], (void*)&status);
        total += *(float*)status;
    }

    clock_t finish = clock();
    double res = 4 * total / nPoints;
    double time_used = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Pi is %lf\n", res);
    printf("Time is %lf\n", time_used);
    return 0;
}