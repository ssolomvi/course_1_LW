#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "table.h"

#define ASCII_A 65
#define ASCII_Z 90
#define ASCII_A_to_a 32
#define SWAP(A, B) { Entry* T = (A); (A) = (B); (B) = T; };

char* to_lower(char key[KEY_SIZE])
{
    int i;
    for (i = 0; i < KEY_SIZE; i++) {
        if (key[i] >= ASCII_A && key[i] <= ASCII_Z) {
            key[i] += ASCII_A_to_a;
        }
    }
    return key;
}

init_statuses init_table(Table* table)
{
    if (!table) {
        return init_allocation_error;
    }
    table->entries = (Entry**) malloc(sizeof (Entry*));
    table->entries = NULL;
    table->num = 0;
    table->sorted = 0;
    return init_ok;
}

ins_entry_statuses insert(Table* table)
{
    int buf;
    Entry* tmp_entry, **for_reallocation;
    find_entry_statuses found_status;

    if (!table) {
        init_table(table);
    }
    tmp_entry = (Entry*) malloc(sizeof (Entry));

    scanf("%s", tmp_entry->key);
    tmp_entry->key[KEY_SIZE - 1] = '\0';
    to_lower(tmp_entry->key);

    scanf("%s", tmp_entry->data);
    tmp_entry->data[DATA_LEN - 1] = '\0';

    found_status = binary_find(table, tmp_entry->key, &buf);
    if (found_status == find_entry_ok) {
        free(tmp_entry);
        return ins_entry_key_repeated;
    }

    table->num++;
    for_reallocation = (Entry**) realloc(table->entries, table->num * sizeof(Entry*));
    if (!for_reallocation) {
        return ins_entry_allocation_error;
    }
    table->entries = for_reallocation;
    table->entries[table->num - 1] = tmp_entry;
    table->sorted = 0;

    return ins_entry_ok;
}

read_file_statuses read_file(const char *filePath, Table* result)
{
    FILE *test_file;
    if (!(test_file = fopen(filePath, "r")))
    {
        return read_file_file_not_exists;
    }

    if (!result) {
        init_table(result);
    }
    destroy(result);

    int i, found_status, buf;
    char key[KEY_SIZE], data[DATA_LEN];
    Entry ** for_reallocation, *tmp_entry;
    while ((fscanf(test_file, "%s%s", &key, &data)) != EOF) {
        to_lower(key);
        tmp_entry = (Entry*) malloc(sizeof(Entry));
        for (i = 0; i < KEY_SIZE; i++)
            tmp_entry->key[i] = key[i];
        for (i = 0; i < DATA_LEN; i++)
            tmp_entry->data[i] = data[i];
        found_status = binary_find(result, tmp_entry->key, &buf);
        if (found_status == find_entry_ok) {
            free(tmp_entry);
            return read_file_key_repeated;
        }

        result->num++;
        for_reallocation = (Entry**)realloc(result->entries, sizeof(Entry*) * result->num);
        if (!for_reallocation) {
            return read_file_allocation_error;
        }
        result->entries = for_reallocation;
        result->entries[result->num - 1] = tmp_entry;
        result->sorted = 0;
    }
    fclose(test_file);
    return read_file_ok;
}

del_entry_statuses delete(Table* table, char* key_to_delete)
{
    int position, i;
    Entry** for_reallocation;
    find_entry_statuses found_status = binary_find(table, key_to_delete, &position);
    if (found_status == find_entry_table_is_empty)
        return del_entry_table_is_empty;
    if (found_status == find_entry_entry_not_found)
        return del_entry_does_not_exist;

    Entry** entries_tail = (Entry**) malloc(sizeof (Entry*)
                                        * (table->num - position - 1));
    memcpy(entries_tail, table->entries + position + 1, sizeof (Entry*)
                                        * (table->num - position - 1));
    free(table->entries[position]);
    table->num--;
    for_reallocation = (Entry**) realloc(table->entries, sizeof (Entry*) * table->num);
    if (for_reallocation == NULL) {
        table->entries = NULL;
        free(for_reallocation);
        free(entries_tail);
        return del_entry_ok;
    }
    table->entries = for_reallocation;
    memcpy(table->entries + position, entries_tail, sizeof (Entry*)
                                        * table->num - position);
    for (i = 0; i < table->num - position - 1; i++) {
        free(entries_tail[i]);
    }
    free(entries_tail);

    return del_entry_ok;
}

find_entry_statuses binary_find(Table* table, char* key_to_find, int* position) {
    if (table->num == 0) {
        return find_entry_table_is_empty;
    }

    if (!table->sorted) {
        sort(table);
    }

    int start = 0, end = table->num, mid = (start + (end - start)) / 2, old_mid, compare;
    while ((compare = strcmp(key_to_find, table->entries[mid]->key)) != 0) {
        if (compare > 0) {
            start = mid;
        } else {
            end = mid;
        }
        old_mid = mid;
        mid = (start + end) / 2;

        if (old_mid == mid)
            return find_entry_entry_not_found;
    }
    *position = mid;

    return find_entry_ok;
}

void print(const Table* table)
{
    if (table->num == 0) {
        printf("The table is empty\n"); // the only text field in module file...
    }
    int i;
    for (i = 0; i < table->num; i++) {
        printf("<%s> : %s\n", table->entries[i]->key, table->entries[i]->data);
    }
}

sort_statuses sort(Table* table)
{
    if (table->num == 0) {
        return sort_table_is_empty;
    }

    int left, right, i;
    left = 0;
    right = table->num - 1;

    while (left < right) {
        for (i = left; i < right; i++) {

            if (strcmp(table->entries[i]->key, table->entries[i + 1]->key) > 0) {
                SWAP(table->entries[i], table->entries[i + 1])
            }
        }

        right--;

        for (i = right; i > left; i--) {
            if (strcmp(table->entries[i - 1]->key, table->entries[i]->key) > 0 ) {
                SWAP(table->entries[i - 1], table->entries[i])
            }
        }

        left++;
    }
    table->sorted = 1;

    return sort_ok;
}

shuffle_statuses shuffle(Table* table)
{
    if (table->num == 0) {
        return shuffle_table_is_empty;
    }

    int i, j, k;

    srand((int)time(0));

    for (i = 0; i < table->num - 1; i++) {
        j = rand() % table->num;
        k = rand() % table->num;
        SWAP(table->entries[j], table->entries[k])
    }
    table->sorted = 0;

    return shuffle_ok;
}

reverse_statuses reverse(Table* table)
{
    if (table->num == 0) {
        return reverse_table_is_empty;
    }

    int i;
    for (i = 0; i < (table->num) / 2; i++) {
        SWAP(table->entries[i], table->entries[table->num - i - 1])
    }
    table->sorted = 0;

    return reverse_ok;
}

void destroy(Table* table)
{
    int i;
    for (i = 0; i < table->num; i++) {
        free(table->entries[i]);
    }

    free(table->entries);
    table->entries = NULL;

    table->num = 0;
    table->sorted = 0;
}
