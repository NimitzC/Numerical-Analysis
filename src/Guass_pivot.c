/**
 * Experiment 3
 * Guass
 * 列主元高斯消去法
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// AX = b

int n; //维度
double **A, *b, *x, epsilon;

double nabs(double x)
{
    if(x < 0) return -x;
    return x;
}

void read_info()
{
    printf("Guass pivot\n");
    printf("input the dimension of A: \n");
    scanf("%d", &n);
    while(n <= 0){
        printf("n must be positive!\n");
        scanf("%d", &n);
    }

    int i, j;
    A = (double**)malloc(n * sizeof(double*));
    for(i = 0; i < n; i++){
        A[i] = (double*)malloc(n * sizeof(double));
    }
    b = (double*)malloc(n * sizeof(double));
    x = (double*)malloc(n * sizeof(double));

    printf("input A: \n");
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            scanf("%lf", &A[i][j]);
        }
    }
    printf("input b: \n");
    for(i = 0; i < n; i++){
        scanf("%lf", &b[i]);
    }
    printf("input epsilon: \n");
    scanf("%lf", &epsilon);
}

void print_A()
{
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }
}

void print_x()
{   
    int i;
    for(i = 0; i < n; i++){
        printf("x%d = %lf\n", (i+1), x[i]);
    }
}

void swap_A_row(int r1, int r2){
    int j;
    double tmp;
    for(int j = 0; j < n; j++){
        tmp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = tmp;
    }
}

void swap_b_row(int r1, int r2){
    double tmp;
    tmp = b[r1];
    b[r1] = b[r2];
    b[r2] = tmp;
}

int cal_main()
{
    int k, i, j, ik;
    double T = 1e-10;
    for(k = 0; k < n - 1; k++){

        //选主元 T
        for(i = k; i < n; i++){
            if(T < nabs(A[i][k])) {
                T = nabs(A[i][k]);
                ik = i;
            }
        }
        if(T < epsilon) return 0;
        if(ik != k) {
            swap_A_row(ik, k);
            swap_b_row(ik, k);
        }

        //消元
        for(i = k + 1; i < n; i++){
            T = A[i][k] / A[k][k];
            b[i] = b[i] - T*b[k];
            //A[i][k+1] = 0;
            for(j = k + 1; j < n; j++){
                A[i][j] = A[i][j] - T * A[k][j];
            }
        }
    }

    if(nabs(A[n-1][n-1]) <= epsilon) return 0;

    x[n-1] = b[n-1] / A[n-1][n-1];
    for(i = n - 2; i >= 0; i--){
        double tmp = 0;
        for(j = i + 1; j < n; j++){
            tmp += A[i][j] * x[j];
        }
        x[i] = (b[i] - tmp) / A[i][i];
    }
    return 1;
}

int main()
{
    read_info();
    if(cal_main() == 0){
        printf("error!\n");
        system("pause");
        return 1;
    }
    print_x();
    system("pause");
    return 0;
}