#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init_list(List* list)
{
    list_item* barrier = (list_item*) malloc(sizeof(list_item));
    list->Barrier = barrier;
    list->Barrier->Data = 0;
    list->Barrier->Next = NULL;
    list->Barrier->Prev = NULL;
    list->Current = list->Barrier;
}

add_to_list_statuses add_to_list(List* list, element value)
{
    if (!list) {
        return add_to_list_statuses_list_does_not_exist;
    }

    list_item* new = (list_item*)malloc(sizeof(list_item));
    if (!new) {
        return add_to_list_statuses_allocation_error;
    }

    new->Data = value;

    if (list->Barrier->Next == NULL) {
        new->Prev = list->Barrier;
        new->Next = list->Barrier;
        list->Barrier->Next = new;
        list->Barrier->Prev = new;
        return add_to_list_statuses_ok;
    }

    list->Barrier->Prev->Next = new;
    new->Prev = list->Barrier->Prev;
    new->Next = list->Barrier;
    list->Barrier->Prev = new;
    return add_to_list_statuses_ok;
}

delete_from_list_statuses delete_from_list(List* list, element value)
{
    if (list->Barrier->Next == NULL || list->Barrier->Next == list->Barrier) {
        return delete_from_list_statuses_list_is_empty;
    }

    int found = 0;
    list_item* tmp;
    list->Current = list->Barrier->Next;

    while (list->Current != list->Barrier || !found) {
        if (list->Current->Data == value) {
            tmp = list->Current;
            list->Current->Next->Prev = list->Current->Prev;
            list->Current->Prev->Next = list->Current->Next;
            list->Current = list->Current->Next;
            free(tmp);
            found = 1;
            continue;
        }
        if (list->Current->Next == list->Barrier) {
            break;
        }
        list->Current = list->Current->Next;
    }

    if (!found) {
        return delete_from_list_statuses_element_is_not_in_list;
    }

    return delete_from_list_statuses_ok;
}

list_len_statuses list_len(List list, int* len)
{
    if (list.Barrier->Next == NULL || list.Barrier->Next == list.Barrier) {
        return list_len_statuses_list_is_empty;
    }

    list.Current = list.Barrier->Next;
    while (list.Current != list.Barrier) {
        (*len)++;
        list.Current = list.Current->Next;
    }

    return list_len_statuses_ok;
}

print_list_statuses print_list(List list)
{
    if (list.Barrier->Next == NULL || list.Barrier->Next == list.Barrier) {
        return print_list_statuses_list_is_empty;
    }

    list.Current = list.Barrier->Next;
    while (list.Current->Next != list.Barrier) {
        printf("%c >> ", list.Current->Data);
        list.Current = list.Current->Next;
    }
    printf("%c\n", list.Current->Data);
    return print_list_statuses_ok;
}

// delete all elements
execute_statuses execute(List* list, element start, element finish, int* counter)
{
    if (list->Barrier->Next == NULL || list->Barrier->Next == list->Barrier) {
        return execute_statuses_list_is_empty;
    }

    list_item* tmp;
    list->Current = list->Barrier->Next;

    while (list->Current != list->Barrier) {
        if (list->Current->Data >= start && list->Current->Data <= finish) {
            tmp = list->Current;
            list->Current->Next->Prev = list->Current->Prev;
            list->Current->Prev->Next = list->Current->Next;
            list->Current = list->Current->Next;
            free(tmp);
            (*counter)++;
            continue;
        }
        list->Current = list->Current->Next;
    }

    if (counter == 0) {
        return execute_statuses_all_elements_out_of_range;
    }

    return execute_statuses_ok;
}

destroy_list_statuses destroy_list(List* list)
{
    if (!list) {
        return destroy_list_statuses_list_does_not_exist;
    }
    if (list->Barrier->Next == NULL || list->Barrier->Next == list->Barrier) {
        return destroy_list_statuses_list_is_empty;
    }
    list_item* tmp;
    list->Current = list->Barrier->Next;
    while (list->Current != list->Barrier) {
        tmp = list->Current;
        list->Current = list->Current->Next;
        free(tmp);
    }
    list->Barrier->Next = NULL;
    list->Barrier->Prev = NULL;
    return destroy_list_statuses_ok;
}
