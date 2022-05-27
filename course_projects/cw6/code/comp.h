#ifndef COMP_H
#define COMP_H

#include "structure.h"

typedef struct computer_item {
    Computer comp;
    struct computer_item* next;
} computer_item;

typedef struct {
    computer_item* head;
} CompList;

CompList *list_create();

void list_add(CompList* list, Computer item);

void list_print(const CompList list);

void list_destroy(CompList* list);

#endif // COMP_H
