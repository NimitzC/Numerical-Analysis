/**
 * Experiment 2
 * Auto-Trapezoid Quadrature Formula
 * 自动选取步长的梯形法
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define f(x) sqrt(x)
#define Gmax 100

double a, b, epsilon, res;
int n;

void read_info()
{
    printf("Auto-TQF\n");
    printf("f(x) = sqrt(x)\n");
    printf("Input a, b, epsilon: \n");
    scanf("%lf%lf%lf", &a, &b, &epsilon);
}

double nabs(double x)
{
    if(x < 0) return -x;
    return x;
}

int cal_main()
{
    double h, T0, T1, S;
    int i, k;

    // init
    h = (b - a) / 2;
    T1 = (f(a) + f(b)) * h;
    n = 1;

    // main
    for (i = 0; i < Gmax; i++)
    {
        T0 = T1;
        S = 0;
        for (k = 1; k <= n; k++)
        {
            S += f((a + (2 * (double)k - 1) * (h / (double)n)));
        }
        
        T1 = (T0 / 2) + (S * (h / n));

        if (nabs(T1 - T0) < 3 * epsilon)
        {
            res = T1;
            return 1;
        }
        n <<= 1;
    }
    printf("G > Gmax\n");
    return 0;
}

int main()
{
    read_info();
    if (cal_main() == 0){
        printf("error\n");
        system("pause");
        return 1;
    }
    printf("n = %d\n", n);
    printf("res = %lf\n", res);
    system("pause");
    return 0;
}