#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
float D = 0.1, dx = 0.1, dt = 0.01;
int M = 18, N = 20;
int Time = 1;
void printArray(float A[], int n)  {
    for (int i = 0; i < n; i++)
    {
        printf("%-7.2f", A[i]);
    }
    printf("\n");
}
void printMatrix(float A[], int cols, int rows) {
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%6.2f ", A[i * cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}
void FD2(float T[], float dT[], float up[], float down[], int rows, int cols, int rank)
{
    float c, l, r, u, d;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            c = T[i * cols + j];
            u = (i==0)        ?  up[j]    : T[(i-1) * cols + j];
            l = (j==0)        ?  25       : T[i * cols + j-1];
            d = (i == rows-1) ?  down[j]  : T[(i+1) * cols + j];
            r = (j==cols-1)   ?  25       : T[i * cols + j+1];
            dT[i * cols + j] = D * (u + d + l + r - 4 * c) / (dx * dx);
        }
    }
}
int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rows = M / size;
    float T[rows * N];
    float dT[rows * N];
    float up[N];
    float down[N];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < N; j++)
        {
            T[i * N + j] = 25;
            dT[i * N + j] = 0;
        }
    }
    int Ntime = Time / dt;
    if (rank == size / 2) {
        T[rows / 2 * N + N / 2] = 100;
    }
    for (int t = 0; t < Ntime; t++) {
        //Gui len ben tren + nhan tu ben tren
        if (rank > 0) {
            MPI_Send(T, N, MPI_FLOAT, rank - 1, rank + t, MPI_COMM_WORLD);
            MPI_Recv(up, N, MPI_FLOAT, rank - 1, rank + size + t, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        //Gui xuong ben duoi + nhan tu ben duoi
        if (rank < size - 1) {
            MPI_Send(T + N * (rows - 1), N, MPI_FLOAT, rank + 1, rank + 1 + size + t, MPI_COMM_WORLD);
            MPI_Recv(down, N, MPI_FLOAT, rank + 1, rank + 1 + t, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        //Khoi tao up cho rank = 0
        if (rank == 0) {
            for (int i = 0; i < N; i++)
            {
                up[i] = 25;
            }
        }
        //Khoi tao down cho rank = size - 1
        if (rank == size - 1) {
            for (int i = 0; i < N; i++)
            {
                down[i] = 25;
            }
        }
        FD2(T, dT, up, down, rows, N, rank);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (!(rank == size/2 && i == rows / 2 && j == N / 2)){
                    T[i * N + j] += dT[i * N + j] * dt;
                }
            }
        }
    }
    float result[N*M];
    MPI_Gather(T, N * rows, MPI_FLOAT, result, N * rows, MPI_FLOAT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printMatrix(result, N, M);
    }
    MPI_Finalize();
}