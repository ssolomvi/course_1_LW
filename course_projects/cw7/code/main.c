#include <stdio.h>
#include "matrix.h"

#define VALID_USER_INPUT(x) ((x) == '1' || (x) == '2' || (x) == '3' || (x) == '4' || (x) == '5' || (x) == '6')
#define ASCII_ZERO 48

void help();

int main(int argc, char *argv[])
{
    matrix m;
    int i, exited = 0;
    char user_input[BUFSIZ];
    read_matrix_statuses read_status;
    replace_with_max_value_by_modulo_statuses replace_with_max_value_by_modulo_status;
    print_matrix_st_statuses print_matrix_st_status;
    print_matrix_nonst_statuses print_matrix_nonst_status;

    init_matrix(&m);

    if (argc < 2)
    {
        printf("Please, pass input file path as parameter!");
        return -1;
    }

    // TODO clean status handling
    help();
    while (!exited)
    {
        printf(">>>");

        scanf("%s", user_input);
        if (!VALID_USER_INPUT(*user_input))
        {
            printf("Invalid input! Print 6 for help...\n\n");
            continue;
        }

        switch (*user_input - ASCII_ZERO)
        {
            case 1:
                read_status = read_matrix(argv[1], &m);
                if (read_status == read_matrix_file_not_exists) {
                    printf("File does not exist\n");
                } else if (read_status == read_matrix_matrix_not_exists) {
                    printf("Matrix does not exist\n");
                } else if (read_status == read_matrix_memory_allocation_error) {
                    printf("Allocation error\n");
                } else {
                    printf("The matrix was read\n");
                }
                break;

            case 2:
                replace_with_max_value_by_modulo_status = replace_with_max_value_by_modulo(&m);
                if (replace_with_max_value_by_modulo_status == replace_with_max_value_by_modulo_matrix_not_exists) {
                    printf("Matrix does not exist\n");
                } else if (replace_with_max_value_by_modulo_status == replace_with_max_value_by_modulo_allocation_error) {
                    printf("Unknown error happened\n");
                } else {
                    printf("Matrix was divided by max modulo\n");
                }
                break;

            case 3:
                print_matrix_st_status = print_matrix_st(m);
                if (print_matrix_st_status == print_matrix_st_matrix_not_exists) {
                    printf("Matrix does not exist\n");
                }
                break;

            case 4:
                print_matrix_nonst_status = print_matrix_nonst(m);
                if (print_matrix_nonst_status == print_matrix_nonst_matrix_not_exists) {
                    printf("Matrix does not exist\n");
                }
                break;

            case 5:
                exited = 1;
                printf("\n");
                break;

            case 6:
                help();
                break;
        }
    }

    clear_matrix(&m);

    return 0;
}

void help()
{
    printf("The program operates with sparse matrix with values of integer type\n");
    printf("    1 - read matrix\n");
    printf("    2 - execute task\n");
    printf("    3 - print matrix in standard view\n");
    printf("    4 - print matrix in vector-keeped view\n");
    printf("    5 - exit\n");
}
