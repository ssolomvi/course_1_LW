#ifndef CW7_MATRIX_H
#define CW7_MATRIX_H

typedef struct matrix
{
    int* values;
    int values_count;
    int columns_count;
} matrix;

typedef enum init_matrix_statuses
{
    init_matrix_ok,
    init_matrix_matrix_not_exists,
} init_matrix_statuses;

typedef enum read_matrix_statuses
{
    read_matrix_ok,
    read_matrix_file_not_exists,
    read_matrix_matrix_not_exists,
    read_matrix_memory_allocation_error,
} read_matrix_statuses;

typedef enum replace_with_max_value_by_modulo_statuses
{
    replace_with_max_value_by_modulo_ok,
    replace_with_max_value_by_modulo_matrix_not_exists,
    replace_with_max_value_by_modulo_allocation_error,
} replace_with_max_value_by_modulo_statuses;

typedef enum print_matrix_st_statuses {
    print_matrix_st_ok,
    print_matrix_st_matrix_not_exists,
} print_matrix_st_statuses;

typedef enum print_matrix_nonst_statuses {
    print_matrix_nonst_ok,
    print_matrix_nonst_matrix_not_exists,
} print_matrix_nonst_statuses;

typedef enum clear_matrix_statuses
{
    clear_matrix_ok,
    clear_matrix_matrix_not_exists,
    clear_matrix_unknown_error
} clear_matrix_statuses;

init_matrix_statuses init_matrix(matrix*);
read_matrix_statuses read_matrix(const char * filePath, matrix*);
replace_with_max_value_by_modulo_statuses replace_with_max_value_by_modulo(matrix*);
print_matrix_st_statuses print_matrix_st(matrix);
print_matrix_nonst_statuses print_matrix_nonst(matrix);
clear_matrix_statuses clear_matrix(matrix*);

#endif //CW7_MATRIX_H
