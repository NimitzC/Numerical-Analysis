/**
 * Experiment 2
 * 复化 Simpson 法
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define f(x) sqrt(x)

double a, b, res;
int n;

void read_info()
{
    printf("input a, b, n: \n");
    printf("Attention: n must be even (n = 2k, k > 1)\n");
    scanf("%lf%lf%d", &a, &b, &n);
}

void cal_main()
{
    double h, S1, S2;
    int k, m;
    h = (b - a) / (double)n;
    S1 = 0;
    S2 = 0;
    m = n / 2;
    for (k = 1; k <= m; k++)
    {
        S1 += f((a + (2 * (double)k - 1) * h));
    }
    for (k = 1; k <= m - 1; k++)
    {
        S2 += f((a + 2 * (double)k * h));
    }
    res = (h / 3) * (f(a) + f(b) + 4 * S1 + 2 * S2);
}

int main()
{
    read_info();
    cal_main();
    printf("res = %lf\n", res);
    system("pause");
    return 0;
}