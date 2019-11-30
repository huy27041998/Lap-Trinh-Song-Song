#include <stdio.h>
#include <stdlib.h>
float D = 0.1, dx = 0.1, dt = 0.01;
int Time = 1;
typedef struct{
    int x, y;
} Source;
void printMatrix(int m, int n, float *C){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++)
        {
            printf("%-7.2f", C[i * n + j]);
        }
    printf("\n");                                                                                                                                              
    }
}
void FD(float *C, float *dC, int m, int n){
    float c, u, d, r, l;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c = C[i * n + j];
            u = (i==0)   ?       25      : C[(i-1) * n + j];
            l = (j==0)   ?       25      : C[i * n + j-1];
            d = (i==m-1) ?  25 : C[(i+1) * n + j];
            r = (j==n-1) ?  25 : C[i * n + j+1];
            dC[i * n + j] = D * (u + d + l + r - 4 * c) / (dx * dx);
        }
    }
}

int main()
{
    int Ntime = Time/dt;
    int m = 18, n = 20;
    Source s[3];
    s[0].x = 4;
    s[0].y = 10;
    s[1].x = 9;
    s[1].y = 17;
    s[2].x = 14;
    s[2].y = 19;
    float *C = malloc(m * n * sizeof(float));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i * n + j] = 25;
        }
    }
    for (int i = 0 ; i < 3; i++) {
        C[s[i].x * n + s[i].y] = 100;
    }
    float *dC = malloc(m * n * sizeof(float));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j < j++)
        {
            dC[i *m + j] = 0;
        }
    }
    C[m / 2 * n + n / 2] = 100;
    for (int i = 0; i < Ntime; i++){
        FD(C, dC, m, n);
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (!((j == s[0].x && k == s[0].y)||
                      (j == s[1].x && k == s[1].y)||
                     (j == s[2].x && k == s[2].y))) {
                    C[j * n + k] += dC[j * n + k] * dt;
                }
            }
        }
    }
    printMatrix(m, n, C);
    free(C);
    free(dC);
}