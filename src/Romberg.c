/**
 * Experiment 2
 * Romberg
 * Romberg 求积法
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define f(x) sqrt(x)
#define MAX_K 100

double a, b, epsilon, res;

void read_info()
{   
    printf("Romberg\n");
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
    int k, m, i;
    double T[MAX_K+1][MAX_K+1];
    T[0][0] = ((b - a) / 2) * (f(a) + f(b));
    for(k = 1; k <= MAX_K; k++){
        //复化梯形公式
        T[0][k] = T[0][k-1] / 2;
        for(i = 1; i <= pow(2, k-1); i++){
            T[0][k] += f(a + (2*i - 1) * ((b-a) / pow(2, k))) * (b-a) / pow(2, k);
        }
        //end

        for(m = 1; m <= k; m++){
            T[m][k - m] = (pow(4, m)*T[m-1][k-m+1] - T[m-1][k-m]) / (pow(4,m)-1);
        }

        if(nabs(T[k][0] - T[k-1][0]) < epsilon){
            //printf("达到精度需求！\n");
            res = T[k][0];
            printf("k = %d\n", k);
            return 1;
        }
    }
    printf("k > MAX_K\n");
    return 0;
}

int main()
{
    read_info();
    if(cal_main() == 0){
        printf("error!\n");
        system("pause");
        return 1;
    }
    printf("res = %lf\n", res);
    system("pause");
    return 0;
}