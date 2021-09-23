#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

#define GET_TIME(now){ \
    struct timeval t;     \
    gettimeofday(&t,NULL);\
    now = t.tv_sec+t.tv_sec/1000000.0;\
}

double serial_pi(long long n);
int main(int argc,char** argv) {
    double start,finish;
    GET_TIME(start);
    double estimate_of_pi = serial_pi(1000000000);
    printf("\n Estimated of pi: %1.10f.\n",estimate_of_pi);
    GET_TIME(finish);

    printf("\nAcutal value of pi: %1.10f.\n\n", atan(1)*4);
    printf("The elapsed time is %e seconds\n",finish-start);
}

double serial_pi(long long n){
    double sum = 0.0;
    long long i;
    double factor = 1.0;

    for (i = 0; i < n; i++,factor=-factor) {
        sum += factor/(2*i+1);
    }

    return 4.0*sum;
}