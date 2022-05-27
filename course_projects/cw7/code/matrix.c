#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "matrix.h"

#define IS_OK(x) ((x) == '-' || (x) == '+' || isdigit((x)))

init_matrix_statuses init_matrix(matrix *m)
{
    if (m == NULL)
    {
        return init_matrix_matrix_not_exists;
    }

    m->values = NULL;
    m->values_count = 0;

    return init_matrix_ok;
}

read_matrix_statuses read_matrix(const char *filePath, matrix *result)
{
    FILE *file_with_matrix;
    char c, _c = ' ';
    clear_matrix_statuses clear_status;
    int matrix_columns_count = 0, i, q, column, value;
    int *matrix_line, values_not_equal_to_zero_count, *for_realloc;
    int matrix_line_id;

    if (result == NULL)
    {
        return read_matrix_matrix_not_exists;
    }

    if (!(file_with_matrix = fopen(filePath, "r")))
    {
        return read_matrix_file_not_exists;
    }

    clear_status = clear_matrix(result);
    // TODO: received clear_status handling...

    while (1)
    {
        c = fgetc(file_with_matrix);

        if (c == EOF || c == '\n')
        {
            break;
        }

        if (!IS_OK(_c) && IS_OK(c))
        {
            matrix_columns_count++;
        }

        _c = c;
    } // get columns_count

    result->columns_count = matrix_columns_count;

    fclose(file_with_matrix);
    file_with_matrix = fopen(filePath, "r");

    matrix_line = (int*)malloc(sizeof(int) * result->columns_count);
    matrix_line_id = 0;

    result->values = (int*)malloc(sizeof(int));
    *(result->values) = 0;
    result->values_count = 1;

    while (!feof(file_with_matrix)) {
        matrix_line_id++;
        values_not_equal_to_zero_count = 0;

        for (i = 0; i < result->columns_count; i++) {
            fscanf(file_with_matrix, "%d", matrix_line + i);
            if (matrix_line[i] != 0) {
                values_not_equal_to_zero_count++;
            }
        }

        if (values_not_equal_to_zero_count == 0) {
            for_realloc = (int*)realloc(result->values, (result->values_count += 2) * sizeof(int));
            if (!for_realloc) {
                return read_matrix_memory_allocation_error;
            }

            result->values = for_realloc;
            result->values[result->values_count - 2] = matrix_line_id;
            result->values[result->values_count - 1] = 0;
            continue;
        }

        for_realloc = (int*)realloc(result->values,
                              (result->values_count + values_not_equal_to_zero_count * 2 + 2) * sizeof(int));
        if (!for_realloc) {
            return read_matrix_memory_allocation_error;
        }

        result->values = for_realloc;
        result->values[result->values_count++] = matrix_line_id;

        for (i = 0; i < values_not_equal_to_zero_count; i++) {
            for (q = 0; q < result->columns_count; q++) {
                if (matrix_line[q] != 0) {
                    column = q + 1;
                    value = matrix_line[q];
                    matrix_line[q] = 0;
                    break;
                }
            }
            result->values[result->values_count++] = column;
            result->values[result->values_count++] = value;
        }

        result->values[result->values_count++] = 0;
    }

    for_realloc = (int*) realloc(result->values, ++result->values_count * sizeof(int));
    if (!for_realloc) {
        return read_matrix_memory_allocation_error;
    }

    result->values = for_realloc;
    result->values[result->values_count - 1] = 0;

    free(matrix_line);

    return read_matrix_ok;
}

replace_with_max_value_by_modulo_statuses replace_with_max_value_by_modulo(matrix *m)
{
    int max_value = 0;
    int *iterator, iterator_minus_start;
    int is_line_with_max_by_modulo;
    int *current_line_id_ptr;
    int *array_tail_temp;
    int *for_realloc;

    if (m == NULL)
    {
        return replace_with_max_value_by_modulo_matrix_not_exists;
    }

    if (m->values == NULL)
    {
        return replace_with_max_value_by_modulo_matrix_not_exists;
    }

    iterator = (m->values) + 1;
    if (*iterator == 0)
    {
        return replace_with_max_value_by_modulo_ok;
    }

    // get max_value
    while (iterator < m->values + m->values_count)
    {
        iterator++;

        if (*iterator != 0)
        {
            iterator++;
            if (abs(*iterator) > abs(max_value)) {
                max_value = *iterator;
            }
        } else {
            iterator++;
            if (*iterator == 0) {
                break;
            }
        }
    }

    if (max_value == 0)
    {
        return replace_with_max_value_by_modulo_ok;
    }

    iterator = m->values + 1;
    is_line_with_max_by_modulo = 0;
    while (iterator < m->values + m->values_count)
    {
        current_line_id_ptr = iterator;

        if (*iterator == 0)
        {
            break;
        }

        while (*(iterator + 1) != 0)
        {
            iterator += 2;
// one may store a value which meets the conditions
            if (abs(*iterator) == abs(max_value))
            {
                is_line_with_max_by_modulo = 1;
                break;
            }
        }

        if (is_line_with_max_by_modulo == 0)
        {
            iterator += 2;
            continue;
        }

        is_line_with_max_by_modulo = 0;

        iterator = current_line_id_ptr;

        while (*(iterator + 1) != 0)
        {
            iterator += 2;
            *iterator /= max_value;
            if (*iterator == 0)
            {
                iterator_minus_start = iterator - m->values;
                array_tail_temp = (int*)malloc(sizeof(int) *
                    (m->values_count - iterator_minus_start - 1));
                memcpy(array_tail_temp, iterator + 1, sizeof(int) *
                    (m->values_count - iterator_minus_start - 1));
                m->values_count -= 2;
                for_realloc = (int*)realloc(m->values, sizeof(int) *
                    m->values_count);
                if (for_realloc == NULL)
                {
                    // TODO
                    return replace_with_max_value_by_modulo_allocation_error;
                }
                m->values = for_realloc;
                memcpy(m->values + iterator_minus_start - 1, array_tail_temp,
                       sizeof(int) * (m->values_count - iterator_minus_start + 1));
                free(array_tail_temp);
                iterator = m->values + iterator_minus_start - 2;
            }
        }

        iterator += 2;
    }

    return replace_with_max_value_by_modulo_ok;
}

print_matrix_st_statuses print_matrix_st(matrix m)
{
    int* iterator;
    int i, last_column = 0;

    if (m.values == NULL)
    {
        return print_matrix_st_matrix_not_exists;
    }

    iterator = m.values + 1;

    if (*iterator == 0)
    {
        return print_matrix_st_ok;
    }

    while (iterator < m.values + m.values_count) {
        if (*(iterator + 1) != 0) {

            iterator++;
            for (i = 0; i < *iterator - last_column - 1; i++) {
                printf("0 ");
            }
            last_column = *iterator;

            iterator++;
            printf("%d ", *iterator);

        } else {
            for (i = last_column; i < m.columns_count; i++) {
                printf("0 ");
            }
            putchar('\n');

            iterator++;

            if (*(iterator + 1) == 0) {
                return print_matrix_st_ok;
            }

            last_column = 0;
            iterator++;
        }
    }
    return print_matrix_st_ok;
}

print_matrix_nonst_statuses print_matrix_nonst(matrix m) {
    if (m.values == NULL)
    {
        return print_matrix_nonst_matrix_not_exists;
    }

    int i = 0;

    putchar('|');
    for (i = *m.values; i < m.values_count; i++) {
        printf("%d | ", m.values[i]);
    }

    putchar('\n');
    return print_matrix_nonst_ok;
}

clear_matrix_statuses clear_matrix(matrix *m)
{
    if (m == NULL)
    {
        return clear_matrix_matrix_not_exists;
    }

    free(m->values);
    m->values = NULL;
    m->values_count = 0;

    return clear_matrix_ok;
}
