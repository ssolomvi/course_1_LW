#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char* get_error_msg(enum error_type t)
{
    switch (t) {
        case stack_does_not_exist:
            return __not_exists;
        case stack_is_empty:
            return __empty;
        case stack_overflow:
            return __overflow;
        case stack_underflow:
            return __underflow;
        case operation_succeed:
            return __succeed;
        default:
            assert(false);
    }
}


// adds new element to the top of the stack_item;
enum error_type stack_push(stack* st, T value)
{
    if (!st)
        return stack_underflow;

    stack_item* new = (stack_item*) malloc(sizeof (stack_item));

    if (new == NULL)
        return stack_overflow;

    new->data = value;

    if (st->top == NULL) {
        new->next = NULL;
    } else {
        new->next = st->top;
    }

    st->top = new;

    return operation_succeed;
}

// returns top item, deletes it from stack_item
enum error_type stack_pop_item(stack* st, stack_item* popped)
{
    if (!st)
        return stack_underflow;

    popped = st->top;
    popped->next = NULL;
    st->top = st->top->next;
    return operation_succeed;
}

// returns top object value, deletes it from stack_item
enum error_type stack_pop_value(stack* st, T* value)
{
    if (!st)
        return stack_underflow;

    stack_item* popped = st->top;
    *value = popped->data;
    st->top = st->top->next;
    free(popped);
    return operation_succeed;
}

// sorting by insertions
enum error_type stack_sort(stack* st) {
    if (!st)
        return stack_underflow;
    if ((*st).top == NULL)
        return stack_is_empty;

    int i, counter;
    stack buffer;
    buffer.top = NULL;
    T buf_value1, buf_value2;

    stack_pop_value(st, &buf_value1);
    stack_push(&buffer, buf_value1); // first element is sorted

    while (st->top) {
        counter = 0;
        stack_pop_value(st, &buf_value1);

        while (buffer.top != NULL) {
            if (buffer.top->data > buf_value1) {
                stack_pop_value(&buffer, &buf_value2);
                stack_push(st, buf_value2);
                            // delete elements from buffer stack_item, adding them to the main one;
                counter++;
            } else break;
        }

        stack_push(&buffer, buf_value1); // add unsorted value to buffer stack_item

        for (i = 0; i < counter; i++) {
            stack_pop_value(st, &buf_value1);
            stack_push(&buffer, buf_value1);
        }
    }
    // when all elements from main stack_item are sorted
    while (buffer.top != NULL) {
        stack_pop_value(&buffer, &buf_value1);
        stack_push(st, buf_value1);
    }
    stack_destroy(&buffer);
    return operation_succeed;
}

enum error_type stack_traverse(stack st, void (*callback) (T value)) {
    if (st.top == NULL) {
        return stack_is_empty;
    }
    int size = stack_size(st), q;

    for (q = 0; q < size; q++) {
        callback(st.top->data);
        st.top = st.top->next;
    }
    putchar('\n');

    return operation_succeed;
}

// deletes elements from top to bottom;
enum error_type stack_destroy(stack* st)
{
    if (!st)
        return stack_underflow;
    if ((*st).top == NULL)
        return stack_is_empty;

    stack_item* to_destroy;
    while (st->top) {
        to_destroy = st->top;
        st->top = st->top->next;
        free(to_destroy);
    }
    return operation_succeed;
}

int stack_empty(const stack st)
{
    return (st.top == NULL);
}

int stack_size(stack st)
{
    int size = 0;
    while (st.top) {
        size++;
        st.top = st.top->next;
    }
    return size;
}

// returns top object without deleting it from stack_item
enum error_type stack_peek(const stack st, T* value)
{
    if (!st.top) {
        return stack_does_not_exist;
    }

    *value = st.top->data;
    return operation_succeed;
}

bool stack_contains(stack st, T value) {
    while (st.top) {
        if (st.top->data == value)
            return true;
        st.top = st.top->next;
    }
    return false;
}
