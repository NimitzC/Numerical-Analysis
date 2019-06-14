/**
 * Experiment 3
 * LU_pivot
 * 列主元LU分解法
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

double nabs(double x)
{
    if(x < 0) return -x;
    return x;
}

void read_info()
{
    printf("LU pivot\n");
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

void swap_A_row(int r1, int r2)
{
    int j;
    double tmp;
    for(j = 0; j < n; j++){
        tmp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = tmp;
    }
}

void swap_b_row(int r1, int r2)
{
    double tmp;
    tmp = b[r1];
    b[r1] = b[r2];
    b[r2] = tmp;
}

int cal_L_U()
{
    int i, j, k, m, ik;
    double *S = (double*)malloc(n * sizeof(double));
    
    for(k = 0; k < n; k++){
        // cal S[i]
        for(i = k; i < n; i++){
            S[i] = A[i][k];
            for(m = 0; m <= k - 1; m++){
                S[i] -= L[i][m]*U[m][k];
            }
        }

        // find pivot
        double pivot = 0;
        ik = k;
        for(i = k; i < n; i++){
            if(pivot < nabs(S[i])){
                pivot = nabs(S[i]);
                ik = i;
            }
        }

        // avoding overflow
        if(pivot < epsilon) {
            printf("k = %d\n", k);
            printf("pivot = %lf\n", pivot);
            return 0;
        }

        if(k != ik) {
            swap_A_row(k, ik);
            swap_b_row(k, ik);
        }

        // cal U[k][j]
        for(j = k; j < n; j++){
            U[k][j] = A[k][j];
            for(m = 0; m <= k - 1; m++){
                U[k][j] -= L[k][m]*U[m][j];
            }
        }

        // cal L[i][k]
        for(i = k + 1; i < n; i++){
            L[i][k] = A[i][k] / U[k][k];
            for(m = 0; m <= k - 1; m++){
                L[i][k] -= L[i][m]*U[m][k] / U[k][k];
            }
        }
    }
}

void cal_Y_X()
{
    double *y = (double*)malloc(n * sizeof(double));
    int i, j;

    // cal y
    for(i = 0; i < n; i++){
        y[i] = b[i];
        for(j = 0; j <= i - 1; j++){
            y[i] -= L[i][j]*y[j];
        }
    }

    // cal x
    for(i = n - 1; i >= 0; i--){
        x[i] = y[i] / U[i][i];
        for(j = i + 1; j < n; j++){
            x[i] -= U[i][j]*x[j] / U[i][i];
        }
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