/**
 * Experiment 2
 * Auto-Simpson
 * 自动选取步长的 Simpson 法
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define f(x) sqrt(x)
#define GMAX 100

double a, b, epsilon, res;
int n;

void read_info()
{
    printf("Auto-Simpson\n");
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
    double h, T0, T1, S0, S1, S2;
    int i, k;

    // init
    h = (b - a) / 2;
    n = 2;
    S0 = f(a) + f(b);
    S1 = 0;
    S2 = f((a + b) / 2);
    T1 = (h / 3) * (S0 + 2*S1 + 4*S2);

    // main
    for(i = 1; i <= GMAX; i++){
        T0 = T1;
        S1 += S2;
        S2 = 0;
        for(k = 1; k <= n; k++){
            S2 += f(a + (2*k-1)*(h / n));
        }
        T1 = (h / (3 * n)) * (S0 + 2*S1 + 4*S2);

        if(nabs(T1 - T0) < 3 * epsilon){
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
    if(cal_main() == 0){
        printf("error\n");
        system("pause");
        return 1;
    }
    printf("n = %d\n", n);
    printf("res = %lf\n", res);
    system("pause");
    return 0;
}