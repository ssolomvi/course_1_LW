#include <stdio.h>
#include <math.h>

int is_num(char c)
{
    return c >= '0' && c <= '9'; 
}

void cout(long long x, int j, int s)
{
    int q;
    if (s == 1) {
        printf("+");
    } else if (s == -1) {
        printf("-");
    }
    if (x >= 0) {
        while (j != 0) {
            q = x / pow(10, j - 1);
            printf("%d", q);
            x = x - q * pow(10, j - 1);
            j = j - 1;
        }
    }
    printf(" ");
}

typedef enum {SEARCH1, IS_F_NUM, FIRST, SEARCH2, IS_L_DIGIT, LAST, IS_L} State;

int main(void)
{
    char c;
    long long number2 = 0, number3 = 0, number4 = 0;
    int fsign = 0, lsign = 0, lnumber = 0, i = 1, j = 1, znak = 0;

    State state = SEARCH1;
    while ((c = getchar()) != EOF) {
        switch (state) {
            case SEARCH1:
                if (c == '+') {
                    fsign = 1;
                    state = IS_F_NUM;
                } else if (c == '-') {
                    fsign = -1;
                    state = IS_F_NUM;
                } else if (is_num(c)) {
                    fsign = 0;
                    number2 = c - '0';
                    state = FIRST;
                }
                break;

            case IS_F_NUM:
                if (is_num(c)) {
                    number2 = c - '0';
                    state = FIRST;
                } else if (c == '\n' || c == ' ') {
                    state = SEARCH1;
                }
                break;


            case FIRST:
                if (is_num(c)) {
                    number2 = number2 * 10 + c - '0';
                    i += 1;
                } else if (c == '\n') {
                    cout(number2, i, fsign);
                    cout(number2, i, fsign);
                    printf("\n");
                    i = 1;
                    number2 = 0;
                    fsign = 0;
                    state = SEARCH1;
                } else if (c == ' ') {
                    cout(number2, i, fsign);
                    number4 = number2;
                    lnumber = i;
                    lsign = fsign;
                    state = SEARCH2;
                } else {
                    i = 1;
                    number2 = 0;
                    fsign = 0;
                    state = SEARCH1;
                }
                break;

            case SEARCH2:
                if (is_num(c)) {
                    number3 = c - '0';
                    lsign = 0;
                    state = LAST;
                } else if (c == '+') {
                    lsign = 1;
                    state = IS_L_DIGIT;
                } else if (c == '-') {
                    lsign = -1;
                    state = IS_L_DIGIT;
                } else if (c == ' ') {
                    number4 = number3;
                    lnumber = j;
                    znak = lsign;
                    lsign = 0;
                    j = 1;
                } else if (c == '\n') {
                    znak = lsign;
                    cout(number4, lnumber, znak);
                    printf("\n");
                    j = 1;
                    i = 1;
                    fsign = 0; lsign = 0; znak = 0;
                    lnumber = 0; number4 = 0; number3 = 0; number2 = 0;
                    state = SEARCH1;
                } else {
                    state = IS_L;
                }
                break;

            case IS_L_DIGIT:
                if (is_num(c)) {
                    number3 = c - '0';
                    state = LAST;
                } else if (c == ' ') {
                    state = SEARCH2;
                } else if (c == '\n') {
                    cout(number4, lnumber, znak);
                    printf("\n");
                    j = 1; i = 1;
                    fsign = 0; lsign = 0; znak = 0;
                    lnumber = 0; number4 = 0; number3 = 0; number2 = 0;
                    state = SEARCH1;
                } else {
                    state = IS_L;
                }
                break;

            case LAST:
                if (is_num(c)) {
                    number3 = number3 * 10 + c - '0';
                    j += 1;
                } else if (c == '\n') {
                    lnumber = j;
                    znak = lsign;
                    cout(number3, lnumber, znak);
                    printf("\n");
                    j = 1;
                    i = 1;
                    fsign = 0; lsign = 0; znak = 0;
                    lnumber = 0; number4 = 0; number3 = 0; number2 = 0;
                    state = SEARCH1;
                } else if (c == ' ') {
                    number4 = number3;
                    znak = lsign;
                    lsign = 0;
                    lnumber = j;
                    j = 1;
                    state = SEARCH2;
                } else {
                    j = 1;
                    number3 = 0;
                    lsign = 0;
                    state = IS_L;
                }
                break;

            case IS_L:
                if (c == ' ') {
                    state = SEARCH2;
                } else if (c == '\n') {
                    cout(number4, lnumber, znak);
                    printf("\n");
                    j = 1; i = 1;
                    fsign = 0; lsign = 0; znak = 0;
                    lnumber = 0; number4 = 0; number3 = 0; number2 = 0;
                    state = SEARCH1;
                }
                break;
        }
    }
    return 0;
}
