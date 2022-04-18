#include <stdio.h>
#include <math.h>

#define eps (7.0 / 3.0 - 4.0 / 3.0 - 1.0)

const double e = 2.718281828459045;
const double a1 = 1, b1 = 2, a2 = 0, b2 = 0.8;

double f1v1(double x)
{
    return 0.1 * x * x - x * log(x);
}

double f1v2(double x)
{
    return pow(e, 0.1 * x) ;
}

double f2v1(double x)
{
    return tan(x) - pow(tan(x), 3) / 3 + pow(tan(x), 5) / 5 - 1.0 / 3;
}

double f2v2(double x)
{
    return atan(pow(tan(x), 3) / 3 - pow(tan(x), 5) / 5 + 1.0 / 3);
}

double f1d1(double x)
{
    return 0.2 * x - log(x) - 1;
}

double f1d2(double x)
{
    return 0.2 - 1 / x;
}

double f2d1(double x)
{
    return 1 / pow(cos(x), 2) - pow(sin(x), 2) / pow(cos(x), 4) + pow(sin(x), 4) / pow(cos(x), 6) - 1.0 / 3;
}

double f2d2(double x)
{
    return 2 / pow(cos(x), 3) - (2 * sin(x) + pow(sin(x), 3)) / pow(cos(x), 5) + (4 * pow(sin(x), 3) + pow(sin(x), 5)) / pow(
            cos(x), 7) - 1.0 / 3;
}

double dichotomy(double f(double), double a, double b)
{
    while (fabs(a - b) > eps) {
        if (f(a) * f((a + b) / 2) > 0) {
            a = (a + b) / 2;
        }
        if (f(b) * f((a + b) / 2) > 0) {
            b = (a + b) / 2;
        }
    }

    return (a + b) / 2;
}

double iteration(double f(double), double a, double b)
{
    double x0 = (a + b) / 2;
    double xn = x0 + 1;
    while (fabs(x0 - xn) > eps) {
        xn = x0;
        x0 = f(x0);
    }
    return x0;
}

double newton(double f(double), double d1(double), double d2(double), double a, double b)
{
    double x0, xn;
    if (f(a) * d2(a) > 0) {
        x0 = a;
    } else {
        x0 = b;
    }

    xn = x0 - f(x0) / d1(x0);
    while (fabs(x0 - xn) > eps) {
        x0 = xn;
        xn = x0 - f(x0) / d1(x0);
    }
    return xn;
}

int main(void) {

    printf("|Вариант|\t|Метод дихотомии |\t|Метод итераций |\t|Метод Ньютона |\n");

    printf("|  20\t|\t");
    printf("|%lf\t\t |\t", dichotomy(f1v1, a1, b1));
    printf("|%lf\t\t|\t", iteration(f1v2, a1, b1));
    printf("|%lf\t   |\t\n", newton(f1v1, f1d1, f1d2, a1, b1));

    printf("|  21\t|\t");
    printf("|%lf\t\t |\t", dichotomy(f2v1, a2, b2));
    printf("|%lf\t\t|\t", iteration(f2v2, a2, b2));
    printf("|%lf\t   |\t\n", newton(f2v1, f2d1, f2d2, a2, b2));

    return 0;
}

