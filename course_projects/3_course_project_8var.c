#include <stdio.h>

#define epsilon (7.0 / 3.0 - 4.0 / 3.0 - 1.0)
#define A 0.0
#define B 2.0

double function(double arg)
{
    return 1 / (2 * arg - 5);
}

double function_taylor(double arg)
{
    double res = - (1.0 / 5), prev = - (1.0 / 5), pres;
    int iter = 0;
    for (; prev < -epsilon && iter <= 100; ++iter) {
        pres = prev * 2 * arg / 5;
        res += pres;
        prev = pres;
    }
    iter > 100 ? printf("|n = %3d\t|\t", iter - 1) : printf("|n = %3d\t|\t", iter);
    return res;
}


int main(void)
{
    double d = 0.0;
    scanf("%lf", &d);
    d = 1.0 / (d * 2.0);
    printf("|Итерации   |\t|Значение x|\t|Значение функции       |\t|Зн-ие по ф-ле Тейлора  | \n");
    for (double arg = A; arg <= B; arg += d) {
        printf("|%.2lf      |\t|%.20lf|\t|%.20lf| \n", arg, function(arg), function_taylor(arg));
    }
    return 0;
}
