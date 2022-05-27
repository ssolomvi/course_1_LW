#ifndef TABLE_H
#define TABLE_H

#define KEY_SIZE 7
#define DATA_LEN 101

typedef struct Entry {
    char key[KEY_SIZE];
    char data[DATA_LEN];
} Entry;

typedef struct Table {
    Entry** entries;
    int num;
    int sorted;
} Table;

typedef enum init_statuses {
    init_ok,
    init_allocation_error,
} init_statuses;

typedef enum ins_entry_statuses {
    ins_entry_ok,
    ins_entry_key_repeated,
    ins_entry_allocation_error,
} ins_entry_statuses;

typedef enum read_file_statuses {
    read_file_file_not_exists,
    read_file_allocation_error,
    read_file_key_repeated,
    read_file_ok,
} read_file_statuses;

typedef enum del_entry_statuses {
    del_entry_ok,
    del_entry_does_not_exist,
    del_entry_table_is_empty,
} del_entry_statuses;

typedef enum find_entry_statuses {
    find_entry_ok,
    find_entry_table_is_empty,
    find_entry_entry_not_found,
} find_entry_statuses;

typedef enum sort_statuses {
    sort_ok,
    sort_table_is_empty,
} sort_statuses;

typedef enum shuffle_statuses {
    shuffle_ok,
    shuffle_table_is_empty,
} shuffle_statuses;

typedef enum reverse_statuses {
    reverse_ok,
    reverse_table_is_empty,
} reverse_statuses;

init_statuses init_table(Table*);
ins_entry_statuses insert(Table*);
read_file_statuses read_file(const char*, Table*);

del_entry_statuses delete(Table*, char*);
find_entry_statuses binary_find(Table *table, char* key_to_find, int *position);
void print(const Table*);

sort_statuses sort(Table*);
shuffle_statuses shuffle(Table*);
reverse_statuses reverse(Table*);
void destroy(Table*);

#endif // TABLE_H
