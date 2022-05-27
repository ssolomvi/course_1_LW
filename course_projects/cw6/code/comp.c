#include <stdio.h>
#include <stdlib.h>

#include "comp.h"
#include "io.h"


CompList *list_create()
{
    CompList *list = (CompList*)malloc(sizeof (CompList));
    list->head = NULL;
    return list;
}

void list_add(CompList* list, Computer item)
{
    computer_item* tmp = (computer_item*) malloc(sizeof(computer_item));
    tmp->comp = item;
    tmp->next = list->head;
    list->head = tmp;
}

void list_print(const CompList list)
{
    int i;
    computer_item* item;
    for (item = list.head, i = 1; item != NULL; item = item->next, ++i) {
        printf("%d. ", i);
        computer_print(&item->comp);
    }
}

void list_destroy(CompList* list)
{
    computer_item* tmp;
    while (list->head != NULL) {
        tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }
    free(list);
}