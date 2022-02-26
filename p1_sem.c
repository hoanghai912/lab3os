#include <stdio.h>
#include "pthread.h"
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>

#define THREADS 8

struct data
{
    int seed;
    long point;
};

struct data thread_item[THREADS];

static double d = 0;
static sem_t sem;


void* in(void *arg)
{
    struct data *item;
    item = (struct data *) arg;
    long lim_point = item->point;
    int seed = item->seed;

    for (long i = 0; i<lim_point; i++)
    {
        double x_point = (double)rand_r(&seed)/RAND_MAX;
        double y_point = (double)rand_r(&seed)/RAND_MAX;
        if (x_point*x_point + y_point*y_point <= 1)
        {
            sem_wait(&sem);
            ++d;
            sem_post(&sem);
        }
    }

    pthread_exit(NULL);
}

int main()
{
    sem_init(&sem, 0, 1);
    double nPoints;
    scanf("%lf", &nPoints);
    long point = nPoints / THREADS;

    pthread_t thread_id[THREADS];

    for (int i = 0; i<THREADS; i++)
    {
        time_t t_time;
        thread_item[i].seed = i + time(&t_time);
        thread_item[i].point = point;
        pthread_create(&thread_id[i], NULL, in, (void*)&thread_item[i]);
    }

    for (int i = 0; i<THREADS; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    double res = 4 * d / nPoints;
    printf("Calculate Pi is %lf\n", res);
    return 0;
}