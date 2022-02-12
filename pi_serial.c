#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    double nPoints;
    scanf("%lf", &nPoints);
    long long count = 0;
    clock_t begin = clock();
    for (long long i = 0; i<nPoints; i++)
    {
        double x = (double)rand()/RAND_MAX;
        double y = (double)rand()/RAND_MAX;
        if (x*x + y*y <= 1) count++;
    }
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    double res = 4 * count / nPoints;
    printf("Pi is %lf\n", res);
    printf("Time is %lf\n", time_spent);
    return 0;
}