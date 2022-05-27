#ifndef CW8_LIST_H
#define CW8_LIST_H

#define element char

typedef struct list_item {
    element Data;
    struct list_item* Prev;
    struct list_item* Next;
} list_item;

typedef struct List {
    list_item* Barrier;
    list_item* Current;
} List;

typedef enum add_to_list_statuses {
    add_to_list_statuses_ok,
    add_to_list_statuses_list_does_not_exist,
    add_to_list_statuses_allocation_error
} add_to_list_statuses;

typedef enum delete_from_list_statuses {
    delete_from_list_statuses_ok,
    delete_from_list_statuses_list_is_empty,
    delete_from_list_statuses_element_is_not_in_list,
} delete_from_list_statuses;

typedef enum list_len_statuses {
    list_len_statuses_ok,
    list_len_statuses_list_is_empty
} list_len_statuses;

typedef enum print_list_statuses {
    print_list_statuses_ok,
    print_list_statuses_list_is_empty
} print_list_statuses;

typedef enum execute_statuses {
    execute_statuses_ok,
    execute_statuses_list_is_empty,
    execute_statuses_all_elements_out_of_range
} execute_statuses;

typedef enum destroy_list_statuses {
    destroy_list_statuses_ok,
    destroy_list_statuses_list_does_not_exist,
    destroy_list_statuses_list_is_empty
} destroy_list_statuses;

void init_list(List*);
add_to_list_statuses add_to_list(List*, element);
delete_from_list_statuses delete_from_list(List*, element);
list_len_statuses list_len(List, int*);
print_list_statuses print_list(List);
execute_statuses execute(List*, element, element, int*);
destroy_list_statuses destroy_list(List*);

#endif // CW8_LIST_H
