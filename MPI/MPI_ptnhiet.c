#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

float D = 0.1, dx = 0.1, Time = 1, dt = 0.01;
int M = 18;
void DHB2(float T[], float dT[], int n, float left, float right)
{
    float c, l, r;
    for (int i = 0; i < n; i++)
    {
        c = T[i];
        l = (i == 0) ? left : T[i-1];
        r = (i == n-1) ? right : T[i+1];
        dT[i] = D * (l - 2 * c + r) / (dx * dx);
    }
}
void print(float *T, int c) {
    for (int i = 0; i < c; i++)
    {
        printf("%5.3f ", T[i]);
    }
    printf("\n");
}
int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int t, Ntime = Time / dt, i, c = M / size;
    float *T = malloc(c * sizeof(float));
    float *dT = malloc(c * sizeof(float));
    for (int i = 0; i < c; i++) {
        T[i] = 25;
    }
    for (t = 0; t <= Ntime; t++) 
    {
        float left; float right;
        left = 100; right = 25;
        if (rank < size - 1){
            MPI_Send(T + c - 1, 1, MPI_FLOAT, rank + 1, 2 * rank + 2 + t * c, MPI_COMM_WORLD);
            MPI_Recv(&right, 1, MPI_FLOAT, rank + 1, 2 * (rank + 1) + 1 + t * c, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (rank > 0){
            MPI_Send(T, 1, MPI_FLOAT, rank - 1, 2 * rank + 1 + t * c, MPI_COMM_WORLD);
            MPI_Recv(&left, 1, MPI_FLOAT, rank - 1, 2 * (rank - 1) + 2 + t * c, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        DHB2(T, dT, c, left, right);
        for (int i = 0; i < c; i++){
            for (i = 0; i < c; i++)
                T[i] = (T[i] + dT[i] * dt >= 100) ? 100 : T[i] + dT[i] * dt;
        }
    }
    float * result = malloc(M * sizeof(float));
    MPI_Gather(T, c, MPI_FLOAT, result, c, MPI_FLOAT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        print(result, M);
    }
    MPI_Finalize();
}