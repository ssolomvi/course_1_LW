#include <stdio.h>
#include "table.h"

#define VALID_USER_INPUT(x) ((x) >= '0' && (x) <= '9' || (x) == '?')
#define ASCII_ZERO 48

void help();

int main(int argc, char *argv[])
{
    int exited = 0, rows_to_insert, i;
    char user_input[BUFSIZ], key[KEY_SIZE], c;
    Table table;
    ins_entry_statuses ins_entry_status;
    read_file_statuses read_file_status;
    del_entry_statuses del_entry_status;
    sort_statuses sort_status;
    shuffle_statuses shuffle_status;
    reverse_statuses reverse_status;

    if (init_table(&table) == init_allocation_error) {
        printf("Allocation error\n");
    }

    help();
    while (!exited) {
        printf(">>>");
        scanf("%s", user_input);

        if (!VALID_USER_INPUT(*user_input))
        {
            printf("Invalid input! Print ? for help...\n\n");
            continue;
        }

        switch (*user_input - ASCII_ZERO) {
            case 1:
                printf("Enter number of rows to insert:");
                scanf("%d", &rows_to_insert);
                for (i = 0; i < rows_to_insert; i++) {
                    ins_entry_status = insert(&table);
                    if (ins_entry_status == ins_entry_key_repeated) {
                        printf("The entry with that key already exists\n");
                    } else if (ins_entry_status == ins_entry_allocation_error) {
                        printf("Allocation error\n");
                    }
                }
                break;

            case 2:
                read_file_status = read_file(argv[1], &table);
                if (read_file_status == read_file_allocation_error) {
                    printf("Allocation error\n");
                } else if (read_file_status == read_file_file_not_exists) {
                    printf("Input file as a parameter to read it\n");
                } else if (read_file_status == read_file_key_repeated) {
                    printf("Wrong file input: key repeated\n");
                } else {
                    printf("The table was read\n");
                }
                break;

            case 3:
                printf("Enter the <key> of entry to delete:");
                scanf("%s%c", &key, &c);
                del_entry_status = delete(&table, key);
                if (del_entry_status == del_entry_does_not_exist) {
                    printf("The entry with this key does not exist\n");
                } else if (del_entry_status == del_entry_table_is_empty) {
                    printf("The table is empty\n");
                } else {
                    printf("The entry with <%s> key value was deleted\n", key);
                }
                break;

            case 4:
                print(&table);
                break;

            case 5:
                sort_status = sort(&table);
                if (sort_status == sort_table_is_empty) {
                    printf("The table is empty\n");
                } else {
                    printf("The table was sorted\n");
                }
                break;

            case 6:
                shuffle_status = shuffle(&table);
                if (shuffle_status == shuffle_table_is_empty) {
                    printf("The table is empty\n");
                } else {
                    printf("The table was shuffled\n");
                }
                break;

            case 7:
                reverse_status = reverse(&table);
                if (reverse_status == reverse_table_is_empty) {
                    printf("The table is empty\n");
                } else {
                    printf("The table was reversed\n");
                }
                break;

            case 8:
                destroy(&table);
                break;

            case 9:
                destroy(&table);
                exited = 1;
                break;

            case 15:
                help();
                break;
        }
    }

    return 0;
}

void help()
{
    printf("The program operates with table with keys of string type\n");
    printf("    1 - insert entries to the table <key> <data>\n");
    printf("    2 - read table from file\n");
    printf("    3 - delete the entry by <key>\n");
    printf("    4 - print the table\n");
    printf("    5 - sort the table with cocktail sort\n");
    printf("    6 - shuffle the table's entries\n");
    printf("    7 - reverse the table's entries\n");
    printf("    8 - destroy the table\n");
    printf("    9 - exit\n");
}
