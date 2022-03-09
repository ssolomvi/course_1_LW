// Требуется проверить упорядоченность цифр числа по неубыванию
#include <stdio.h>

int abs(int x)
{
    return (x < 0) ? -x : x;
}

int main(void)
{
    int number = 0;
    while (scanf("%d", &number) == 1) {
        number = abs(number);
        while (number != 0 && number % 10 >= number % 100 / 10) {
            number /= 10;
        }
        if (number == 0) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return 0;
}
