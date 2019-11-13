#include <stdio.h>
float D = 0.1, dx = 0.1, dt = 0.01;
int Time = 1;
void printMatrix(int m, int n, int **C){
    for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] += dC[i][j];
            }
        }
    }
}
void FD(float **C, float **dC, int m, int n){
    int i, j;
    float c, u, d, r, l;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            c = C[i][j];
            u = (i==0)   ?   C[i][j] : C[i-1][j];
            d = (i==m-1) ?   C[i][j] : C[i+1][j];
            l = (j==0)   ?   C[i][j] : C[i][j-1];
            r = (j==n-1) ?   C[i][j] : C[i][j+1];
        }
        
    }
    dC[i][j] = D * (u + d + l + r + 4 * c) / dx / dx;
    
}

int main()
{
    int Ntime = Time/dt;
    int m = 20, n = 20;
    int **C = malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++)
    {
        C[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; n)
        {
            C[i][j] = 25;
        }
    }
    int **dC = malloc(m * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        dC[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; n)
        {
            dC[i][j] = 0;
        }
    }
    C[i][j] = 100;
    for (int i = 0; i < Ntime; i++){
        FD(C, dC, m, n);
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] += dC[i][j];
            }
        }
    }
    printMatrix(m, n, C);
}