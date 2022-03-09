#include <stdio.h>
#include <stdlib.h>

int min(int x,int y){
    return (x < y) ? x : y;
}
int max(int x, int y){
    return (x > y) ? x : y;
}
int sign(int x){
    return (x > 0) - (x < 0);
}
int mod(int x, int y){
    return abs(((x % y) + y) % y);
}
_Bool in_area(int x,int y){
    return (x >= 5 && 15 >= x && y >= -15 && -5 >= y);
}
int compute_i(int i, int j, int l, int k){
    return mod((abs(max(i * (k + 5), j * (k + 6))) - abs(min(j * (k + 7), l * (k + 8)))), 20);
}
int compute_j(int i, int j, int l){
    return mod((3 - sign(i - j)) * abs(min(min(i * l + 5, j * l - 3), i * j + 6)), 25) - 7;
}
int compute_l(int i, int j, int l){
    return mod(i, 10) + mod(j, 10) + mod(l, 10);
}

int main(void) {
    int i, j, l, k;
    scanf("%d%d%d", &i, &j, &l);
    int i_old = i;
    int j_old = j;
    int l_old = l;

    for (k = 0; k < 50 && !in_area(i_old, j_old); ++k){
        i = compute_i(i_old, j_old, l_old, k);
        j = compute_j(i_old, j_old, l_old);
        l = compute_l(i_old, j_old, l_old);

        i_old = i;
        j_old = j;
        l_old = l;
    }
    printf("%s\n", in_area(i, j) ? "Yes" : "No");
    printf("%d %d %d %d\n", i, j, l, k);
    return 0;
}
