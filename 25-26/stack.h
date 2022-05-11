#ifndef TREE_H
#define TREE_H

static char* __empty = "Stack is empty\n";
static char* __not_exists = "Stack does not exists\n";
static char* __overflow = "Stack overflow\n";
static char* __underflow = "Stack underflow\n";
static char* __succeed = "";

#include <stdbool.h>

typedef int T;

typedef struct stack_item {
    T data;
    struct stack_item* next;
} stack_item;

typedef struct stack {
    stack_item* top;
} stack;

typedef enum error_type {
    stack_does_not_exist,
    stack_is_empty,
    stack_overflow,
    stack_underflow,
    operation_succeed
} error_type;

char* get_error_msg(enum error_type t);
enum error_type stack_push(stack*, T);
enum error_type stack_pop_item(stack*, stack_item*); // returns top stack_item, deletes it from stack_item
enum error_type stack_pop_value(stack*, T*); // returns top value, deletes it from stack_item
enum error_type stack_sort(stack*);
enum error_type stack_traverse(stack, void (*callback) (T));
enum error_type stack_destroy(stack*);
int stack_empty(stack);
int stack_size(stack);
enum error_type stack_peek(stack, T*); // returns top object without deleting it from stack_item
bool stack_contains(stack, T);

#endif // TREE_H
