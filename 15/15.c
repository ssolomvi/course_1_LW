// Замена всех максимальных элементов матрицы на число столбцов, содержащих её минимальный элемент
#include <stdio.h>

void print_m(long long size, long long matrix[size][size])
{
    for (long long i = 0; i < size; ++i) {
        for (long long j = 0; j < size; ++j) {
            printf("%lld ", matrix[i][j]);
        }
        putchar('\n');
    }
}

int main(void)
{
    long long k, kos;
    scanf("%lld%lld", &k, &kos);

    for (int q = 0; q < k; q++) {
        long long size;
        scanf("%lld", &size);
        long long array[size][size];

        for (long long i = 0; i < size; ++i) {
            for (long long j = 0; j < size; ++j) {
                scanf("%lld", &array[i][j]);
            }
        }

        long long max = array[0][0], min = array[0][0];
        long long counter = 0;

        for (long long i = 0; i < size; ++i) {
            for (long long j = 0; j < size; ++j) {
                if (array[i][j] >= max) {
                    max = array[i][j];
                }
                if (array[i][j] <= min) {
                    min = array[i][j];
                }
            }
        }

        for (long long i = 0; i < size; ++i) {
            for (long long j = 0; j < size; ++j) {
                if (array[j][i] == min) {
                    counter++;
                    break;
                }
            }
        }
        for (long long i = 0; i < size; ++i) {
            for (long long j = 0; j < size; ++j) {
                if (array[i][j] == max) {
                    array[i][j] = counter;
                }
            }
        }
        print_m(size, array);
    }
    return 0;
}

