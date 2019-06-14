/**
 * Experiment 3
 * LU
 * 直接LU分解法
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// A(1) = L*A(n)
// A = LU，L 为下三角且对角线为1，U 为上三角为变换后的矩阵

int n; //维度
double **A, *b, epsilon;
double **L, **U, *x;

void read_info()
{
    printf("input the dimension of A: \n");
    scanf("%d", &n);
    while(n <= 0){
        printf("n must be positive!\nplease re-input:\n");
        scanf("%d", &n);
    }
    int i, j;

    //init []
    A = (double**)malloc(n * sizeof(double*));
    L = (double**)malloc(n * sizeof(double*));
    U = (double**)malloc(n * sizeof(double*));
    for(i = 0; i < n; i++){
        A[i] = (double*)malloc(n * sizeof(double));
        L[i] = (double*)malloc(n * sizeof(double));
        U[i] = (double*)malloc(n * sizeof(double));
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

int cal_L_U()
{
    int i, j, k, m;
    for(k = 0; k < n; k++){
        // cal U[k][j]
        for(j = k; i < n; i++){
            double tmp = 0;
            for(m = 0; m <= k - 1; m++){
                tmp += L[k][m]*U[m][j];
            }
            U[k][j] = A[k][j] - tmp;
        }

        // avoiding overflow
        if(abs(U[k][k]) < epsilon) return 0;

        // cal L[i][k]
        for(i = k + 1; i < n; i++){
            double tmp = 0;
            for(m = 0; m <= k - 1; m++){
                tmp += L[i][m]*U[m][k];
            }
            L[i][k] = (A[i][k] - tmp) / U[k][k];
        }
    }
    return 1;
}

void cal_Y_X()
{
    double *y = (double*)malloc(n * sizeof(double));
    int i, j;

    // cal y
    y[0] = b[0];
    for(i = 1; i < n; i++){
        double tmp = 0;
        for(j = 0; j <= i - 1; j++){
            tmp += L[i][j]*y[j];
        }
        y[i] = b[i] - tmp;
    }

    // cal x
    x[n-1] = y[n-1] / U[n-1][n-1];
    for(i = n - 2; i >= 0; i--){
        double tmp = 0;
        for(j = i + 1; j < n; j++){
            tmp += U[i][j]*x[j];
        }
        x[i] = (y[i] - tmp) / U[i][i];
    }
}

void print_x()
{   
    int i;
    for(i = 0; i < n; i++){
        printf("x%d = %lf\n", (i+1), x[i]);
    }
}

int main(){
    read_info();
    if(cal_L_U() == 0) {
        printf("error!\n");
        system("pause");
        return 1;
    }
    cal_Y_X();
    print_x();
    system("pause");
    return 0;
}