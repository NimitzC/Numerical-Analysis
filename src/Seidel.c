/**
 * Experiment 4
 * Seidel
 * Seidel 迭代法
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int n; //维度
int M; //允许最大迭代次数
double **A, *b, *x, *y, epsilon;

double nabs(double x)
{
    if(x < 0) return -x;
    return x;
}

void read_info()
{
    printf("Seidel\n");
    printf("Input the dimension of A: \n");
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
    y = (double*)malloc(n * sizeof(double));

    //memset(y, 0, n * sizeof(double));

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

    printf("input default vector Y: \n");
    for(j = 0; j < n; j++){
        scanf("%lf", &y[j]);
    }

    printf("input epsilon: \n");
    scanf("%lf", &epsilon);

    printf("input max iteration M: \n");
    scanf("%d", &M);
}

void print_x()
{       
    int i;
    for(i = 0; i < n; i++){
        printf("x%d = %lf\n", (i+1), x[i]);
    }
}

int cal_main()
{
    int i, j, k;
    double T, *g;
    g = (double*) malloc(n * sizeof(double));

    for(i = 0; i < n; i++){
        x[i] = y[i];
    }

    //形成初始矩阵 B
    for(i = 0; i < n; i++){
        if(nabs(A[i][i]) < epsilon) {
            printf("A[i][i] < epsilon !\n");
            return 0;
        }
        T = A[i][i];
        for(j = 0; j < n; j++){
            A[i][j] = - (A[i][j] / T);
        }
        A[i][i] = 0;
        g[i] = b[i] / T;
    }

    //迭代
    for(k = 1; k <= M; k++){
        for(i = 0; i < n; i++){
            x[i] = g[i];
            for(j = 0; j < n; j++){
                if(j != i) x[i] += A[i][j]*x[j];
            }
        }

        double tmp = 0;
        for(i = 0; i < n; i++){
            tmp += (x[i] - y[i]) * (x[i] - y[i]);
        }
        tmp = sqrt(tmp);

        if(tmp < epsilon) return k;
        
        for(i = 0; i < n; i++){
            y[i] = x[i];
        }
    }

    printf("max iteration!\n");
    return 0;
}

int main()
{
    read_info();
    int res = cal_main();
    if(res == 0){
        printf("error!\n");
        system("pause");
        return 1;
    }
    print_x();
    printf("k = %d\n", res);
    system("pause");
    return 0;
}