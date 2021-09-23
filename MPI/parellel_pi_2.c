#include <stdio.h>
#include <mpi.h>
#include <math.h>
double serial_pi(long long a,long long b);

int main(void) {
    int my_rank,comm_sz,source;
    long long n=1000000000,local_n,local_a,local_b;
    double local_est, total_est;
    double start,finish;
    double local_start,local_finish,local_elapsed,elapsed;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);



    local_n = n/comm_sz;
    local_a = 0+my_rank*local_n;
    local_b = local_a+local_n;

    MPI_Barrier(MPI_COMM_WORLD);
    local_start = MPI_Wtime();

    /*start = MPI_Wtime();*/
    local_est = serial_pi(local_a,local_b);

    if (my_rank!=0){
        MPI_Send(&local_est,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);

    } else{
        total_est=local_est;
        for (source = 1; source < comm_sz; source++) {
            MPI_Recv(&local_est,1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            total_est+=local_est;
        }
    }
    /*finish=MPI_Wtime();*/
    local_finish =MPI_Wtime();
    local_elapsed = local_finish-local_start;
    MPI_Reduce(&local_elapsed,&elapsed,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
    if (my_rank==0) {
        printf("\n Estimated of pi: %1.10f.\n", total_est);
        printf("\nAcutal value of pi: %1.10f.\n\n", atan(1) * 4);
        printf("Elapsed time = %e seconds\n",elapsed);
    }

    MPI_Finalize();
    return 0;
}

double serial_pi(long long a,long long b){
    double sum = 0.0;
    double factor;
    if (a/2 == 0){
        factor = 1.0;
    } else{
        factor = -1.0;
    }

    for (; a < b; a++,factor=-factor) {
        sum += factor/(2*a+1);
    }

    return 4.0*sum;
}
