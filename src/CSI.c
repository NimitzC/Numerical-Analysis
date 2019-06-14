/**
 * Experiment 1
 * Cubic Spline Interpolation
 * 三次样条插值
 * chcp 65001
 */

#include <stdio.h>
#include <stdlib.h>

int N;
double *X, *Y, *h, *alpha, *beta, *a, *b, *m;
double rX, rY;
double m0, mn;  
int toggle = 0; //0 第一种边界条件， 1 第二种边界条件

void read_info()
{
    int i;
    printf("Input the number of interpolation nodes (N):\n");
    scanf("%d", &N);
    X = malloc(N * sizeof(double));
    if (X == NULL)
        perror("X malloc");
    Y = malloc(N * sizeof(double));
    if (Y == NULL)
        perror("Y malloc");

    printf("Input Xi:\n");
    for (i = 0; i < N; i++)
    {
        scanf("%lf", &X[i]);
    }

    printf("Input Yi:\n");
    for (i = 0; i < N; i++)
    {
        scanf("%lf", &Y[i]);
    }

    printf("Input discrimination point (xx):\n");
    scanf("%lf", &rX);

    printf(
        "Select the boundary condition:\n"
        "1: the first boundary condition - f'(x)\n"
        "2: the second boundary condition - f''(x) == 0\n");
    scanf("%d", &toggle);
    while (toggle != 1 && toggle != 2)
    {
        printf("Please input 1 or 2 !\n");
        scanf("%d", &toggle);
    }

    if (toggle == 1)
    {
        printf(
            "The first boundary condition selected\n"
            "Input X0 and XN-1 derivative\n");
        scanf("%lf%lf", &m0, &mn);
    }
    else
    {
        printf("The second boundary condition selected\n");
    }
}

void cal_h()
{
    h = malloc(N * sizeof(double));
    int i;
    for (i = 0; i <= N - 2; i++)
    {
        h[i] = X[i + 1] - X[i];
    }
}

void cal_alpha_beta()
{
    alpha = malloc(N * sizeof(double));
    if (alpha == NULL)
        perror("alpha malloc");
    beta = malloc(N * sizeof(double));
    if (beta == NULL)
        perror("beta malloc");

    if (toggle == 1)
    {
        alpha[0] = 0;
        beta[0] = 2 * m0;
        alpha[N - 1] = 1;
        beta[N - 1] = 2 * mn;
    }
    else
    {
        alpha[0] = 1;
        beta[0] = (3 / h[0]) * (Y[1] - Y[0]);
        alpha[N - 1] = 0;
        beta[N - 1] = (3 / h[N - 2]) * (Y[N - 1] - Y[N - 2]);
    }
    int i;
    for (i = 1; i <= N - 2; i++)
    {
        alpha[i] = h[i - 1] / (h[i - 1] + h[i]);
        beta[i] = 3 * (((1 - alpha[i]) / h[i - 1]) * (Y[i] - Y[i - 1]) + ((alpha[i] / h[i]) * (Y[i + 1] - Y[i])));
    }
}

void cal_a_b()
{
    a = malloc(N * sizeof(double));
    if (a == NULL)
        perror("a malloc");
    b = malloc(N * sizeof(double));
    if (b == NULL)
        perror("b malloc");

    a[0] = -(alpha[0] / 2);
    b[0] = beta[0] / 2;

    int i;
    for (i = 1; i <= N - 1; i++)
    {
        a[i] = -(alpha[i] / (2 + ((1 - alpha[i]) * a[i - 1])));
        b[i] = (beta[i] - (1 - alpha[i]) * b[i - 1]) / (2 + ((1 - alpha[i]) * a[i - 1]));
    }
}

void cal_m()
{
    m = malloc((N + 1) * sizeof(double));
    m[N] = 0;
    int i;
    for (i = N - 1; i >= 0; i--)
    {
        m[i] = a[i] * m[i + 1] + b[i];
    }
}

void cal_res()
{
    int i;
    for(i = 0; i < N - 1; i++){
        if(rX >= X[i] && rX <= X[i+1]) break;
    }
    rY = ((1 + 2 * ((rX - X[i]) / (X[i+1] - X[i]))) * ((rX - X[i+1]) / (X[i] - X[i + 1])) * ((rX - X[i+1]) / (X[i] - X[i + 1])) * Y[i])
       + ((1 + 2 * ((rX - X[i + 1]) / (X[i] - X[i + 1]))) * ((rX - X[i]) / (X[i+1] - X[i])) * ((rX - X[i]) / (X[i+1] - X[i])) * Y[i+1])
       + ((rX - X[i]) * ((rX - X[i+1]) / (X[i] - X[i + 1])) * ((rX - X[i+1]) / (X[i] - X[i + 1])) * m[i])
       + ((rX - X[i+1]) * ((rX - X[i]) / (X[i+1] - X[i])) * ((rX - X[i]) / (X[i+1] - X[i])) * m[i + 1]);
}

int main()
{
    read_info();
    cal_h();
    cal_alpha_beta();
    cal_a_b();
    cal_m();
    cal_res();
    printf("rY = %lf\n", rY);
    system("pause");
    return 0;
}
