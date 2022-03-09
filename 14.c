#include <stdio.h>

void space(int kos2)
{
    if (kos2 != 1) {
        putchar(' ');
    }
}

int main(void)
{
    int k, kos;
    scanf("%d%d", &k, &kos);

    while (k > 0) {
        int size;
        scanf("%d", &size);
        int kos2 = size * size;
        int array[size][size];

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                scanf("%d", &array[i][j]);
            }
        }

        int upper_border = 0, down_border = size, right_border = size, left_border = 0;

        while (down_border - upper_border > 0 || right_border - left_border > 0) {
            for (int j = upper_border; j < down_border; j++) {
                printf("%d", array[j][right_border - 1]);
                space(kos2);
                kos2--;
            }
            right_border--;
            for (int j = right_border - 1; j >= left_border; j--) {
                printf("%d", array[down_border - 1][j]);
                space(kos2);
                kos2--;
            }
            down_border--;
            for (int j = down_border - 1; j >= upper_border; j--) {
                printf("%d", array[j][left_border]);
                space(kos2);
                kos2--;
            }
            left_border++;
            for (int j = left_border; j < right_border; j++) {
                printf("%d", array[upper_border][j]);
                space(kos2);
                kos2--;
            }
            upper_border++;
        }
        putchar('\n');
        k--;
    }
    return 0;
}
