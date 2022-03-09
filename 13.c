#include <stdio.h>
typedef unsigned long Set;

#define EMPTY_SET (Set (0UL))


Set set_insert(Set s, unsigned idx)
{
    return s | ((Set) 1UL << idx);
}

Set set_intersection(Set s1, Set s2)
{
    return s1 & s2;
}

Set set_union(Set s1, Set s2)
{
    return s1 | s2;
}
Set set_complement(Set s1)
{
    return ~s1;
}
Set set_difference(Set s1, Set s2)
{
    return set_complement(set_intersection(s1, s2));
}
Set set_symmetric_difference(Set s1, Set s2)
{
    return set_difference(set_union(s1, s2), set_intersection(s1, s2));
}

int to_lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

int main(void)
{
    int vowel = 1 << 0 | 1 << ('e' - 'a') | 1 << ('i' - 'a') | 1 << ('o' - 'a') | 1 << ('u' - 'a');
    int son = 1 << ('m' - 'a') | 1 << ('n' - 'a')  | 1 << ('l' - 'a') | 1 << ('j' - 'a')  | 1 << ('h' - 'a') | 1 << ('r' - 'a')  | 1 << ('w' - 'a');
    int mask = 0, flag = 0;
    char c;

    while ((c = getchar()) != EOF) {
        c = to_lower(c);
        if (c >= 'a' && c <= 'z') {
            if ((1 << (c - 'a')) & son) {
                flag = 1;
            }
            mask |= 1 << (c - 'a');
        } else if (c == ' ' || c == ',' || c == '\t' || c == '\n') {
            if ((mask & ~vowel & ~son) == 0 && flag) {
                printf("Yes\n");
                return 0;
            } else {
                mask = 0;
                flag = 0;
            }
        }
    }
    printf("No\n");
    return 0;
}
