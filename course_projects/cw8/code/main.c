#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define VALID_USER_INPUT(x) ((x) == '1' || (x) == '2' || (x) == '3' || (x) == '4' || (x) == '5' || (x) == '6' || (x) == '7' || (x) == '8')
#define ASCII_ZERO 48

void help();

int main() {
    int exited = 0, length, counter;
    char user_input[BUFSIZ];
    List list;
    init_list(&list);
    char value, start, finish, tmp;

    add_to_list_statuses add_to_list_status;
    delete_from_list_statuses delete_from_list_status;
    list_len_statuses list_len_status;
    print_list_statuses print_list_status;
    execute_statuses execute_status;
    destroy_list_statuses destroy_list_status;

    help();
    while (!exited) {
        printf(">>>");

        scanf("%s", user_input);
        if (!VALID_USER_INPUT(*user_input))
        {
            printf("Invalid input! Print 8 for help...\n\n");
            continue;
        }

        switch (*user_input - ASCII_ZERO) {
            case 1:
                printf("Enter elements to add: ");
                scanf("\n%c", &value);
                add_to_list_status = add_to_list(&list, value);
                if (add_to_list_status == add_to_list_statuses_allocation_error) {
                    printf("Allocation error\n");
                } else if (add_to_list_status == add_to_list_statuses_list_does_not_exist) {
                    printf("List does not exist\n");
                }

                while (scanf( "%c", &value) && value != '\n') {
                    if (value == ' ') {
                        continue;
                    }
                    add_to_list_status = add_to_list(&list, value);
                    if (add_to_list_status == add_to_list_statuses_allocation_error) {
                        printf("Allocation error\n");
                    } else if (add_to_list_status == add_to_list_statuses_list_does_not_exist) {
                        printf("List does not exist\n");
                    }
                }

                printf("The elements were added to the list\n");
                break;

            case 2:
                printf("Enter an element to delete: ");
                scanf("\n%c", &value);
                delete_from_list_status = delete_from_list(&list, value);
                if (delete_from_list_status == delete_from_list_statuses_element_is_not_in_list) {
                    printf("This element is not in the list\n");
                } else if (delete_from_list_status == delete_from_list_statuses_list_is_empty) {
                    printf("The list is empty\n");
                } else {
                    printf("The element was deleted\n");
                }
                break;

            case 3:
                length = 0;
                list_len_status = list_len(list, &length);
                if (list_len_status == list_len_statuses_list_is_empty) {
                    printf("The list is empty\n");
                } else {
                    printf("The number of elements in list is: %d\n", length);
                }
                break;

            case 4:
                print_list_status = print_list(list);
                if (print_list_status == print_list_statuses_list_is_empty) {
                    printf("The list is empty\n");
                }
                break;

            case 5:
                printf("For range [char_start; char_finish]\n  enter char_start, char_finish: ");
                scanf("\n%c %c", &start, &finish);
                if (start > finish) {
                    tmp = start;
                    start = finish;
                    finish = tmp;
                }
                counter = 0;
                execute_status = execute(&list, start, finish, &counter);

                if (execute_status == execute_statuses_list_is_empty) {
                    printf("The list is empty\n");
                } else if (execute_status == execute_statuses_all_elements_out_of_range) {
                    printf("Elements of the list are out of range\n");
                } else {
                    printf("%d elements were deleted\n", counter);
                }
                break;

            case 6:
                destroy_list_status = destroy_list(&list);
                if (destroy_list_status == destroy_list_statuses_list_does_not_exist) {
                    perror("Error: ");
                } else if (destroy_list_status == destroy_list_statuses_list_is_empty) {
                    printf("The list is empty\n");
                } else {
                        printf("The list was deleted\n");
                }
                break;

            case 7:
                exited = 1;
                break;

            case 8:
                help();
                break;
        }

    }
    destroy_list(&list);
    free(list.Barrier);
    return 0;
}

void help()
{
    printf("The program operates with linear bidirectional list with barrier element\n\t with values of char type\n");
    printf("    1 - add elements to the list\n");
    printf("    2 - delete element from the list\n");
    printf("    3 - print number of elements in the list\n");
    printf("    4 - print the list\n");
    printf("    5 - delete elements in [start, finish]\n");
    printf("    6 - destroy list\n");
    printf("    7 - exit\n");
}
