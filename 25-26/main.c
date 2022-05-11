#include <stdio.h>
#include <string.h>
#include "stack.h"

#define VALID_USER_INPUT(x) ((x) == '1' || (x) == '2' || (x) == '3' || (x) == '4' || (x) == '5' || (x) == '6')

void help();
void print(T value);

int main() {
    int exited = 0;
    T value;
    char c;
    stack head;
    head.top = NULL;
    char user_input[BUFSIZ];

    help();

    while (!exited) {
        printf(">>>");
        scanf("%s", user_input);
        if (strlen(user_input) != 1 || !VALID_USER_INPUT(*user_input)) {
            printf("Invalid input! Try again...\n\n");
            continue;
        }

        switch (*user_input - 48)
        {
            case 1: // add value to stack_item
                printf("Input values to add: ");
                while (scanf("%d%c", &value, &c)) {
                    printf("%s", get_error_msg(stack_push(&head, value)));
                    if (c == '\n') {
                        break;
                    }
                }
                break;

            case 2: // print stack_item -> traverse
                printf("%s", get_error_msg(stack_traverse(head, print)));
                break;

            case 3: // sort stack_item by insertions
                printf("%s", get_error_msg(stack_sort(&head)));
                break;

            case 4: // help menu
                help();
                break;

            case 5: // destroy stack_item
                printf("%s", get_error_msg(stack_destroy(&head)));
                break;

            case 6: // exit
                exited = 1;
                putchar('\n');
                break;
        }
    }
    return 0;
}

void help()
{
    printf("The program operates with stack_item structure with items of int type\n");
    printf("    1 - add value to stack_item\n");
    printf("    2 - print stack_item\n");
    printf("    3 - sort stack_item by insertions\n");
    printf("    4 - help menu\n");
    printf("    5 - destroy stack_item\n");
    printf("    6 - exit\n\n");
}

void print(T value)
{
    printf(" >> %d", value);
}
