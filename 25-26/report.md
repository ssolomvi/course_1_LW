# Отчет по лабораторной работе N 25-26 по курсу
# "Фундаментальная информатика"

Студентка группы: M8О-113Б, Соломатина Светлана Викторовна\
Контакты: ssolomvi@gmail.com\
Работа выполнена: 11.05.2022\
Преподаватель: Довженко Анастасия Александровна

## 1. Тема

Абстрактные типы данных. Рекурсия. Модульное программирование на Си. Автоматизация сборки программ модульной структуры на языке Си с использованием утилиты Make.

## 2. Цель работы

Изучить утилиту make, абстрактные типы данных, модульное программирование и рекурсию.

## 3. Задание

Вариант S2. АТД -- стек. Процедура: вставка элемента в стек, упорядоченные по возрастанию, с сохранением порядка. Метод: сортировка простыми вставками. 

## 4. Оборудование

Процессор: AMD Ryzen 5 4500U with Radeon Graphics 2.38 GHz\
ОП: 16384 Мб\
ОЗУ: 512 Гб\
Монитор: 1920x1080

## 5. Программное обеспечение

Операционная система семейства: **linux (ubuntu)**, версия **21.04**\
Интерпретатор команд: **bash**, версия **5.1.4**.\
Местонахождение и имена файлов программ и данных на домашнем компьютере: **/home/ssolomvi**

## 6. Идея, метод, алгоритм решения задачи

1. Структуру стек задать как stack_item, где хранятся значение и указатель на следующий в стеке элемент.
2. Сортировку реализовать с помощью функций добавления элемента (stack_push), удаления элемента из стека (stack_pop_value). Создаётся буферный стек buffer, первый элемент -- осортированный -- кладётся в buffer, и, пока основной стек не будет пустым, происходит сортировка. Пока значение верхнего элемента в buffer больше того, что был последним в основном стеке, этот элемент из buffer добавляется в основной стек, в противном случае, добавляем сортирующийся элемент к buffer и кладём обратно элементы, ранее лежавшие в buffer. После сортировки всех элементов из основного стека, кладём в него все элементы из buffer.
3. В программе реализованны как вышеупомянутые функции stack_sort, stack_push, stack_pop_value, так и stack_pop_item, возвращающая верхний элемент стека stack_item и удаляющий его из стека, stack_traverse, stack_destroy, stack_empty, stack_size, stack_peek, возвращающая значение верхнего элемента стека без удаления элемента из структуры и stack_contains.

## 7. Сценарий выполнения работы

1. Изучить материалы лекции, дополнительные источиники
2. Разработать алгоритм для решения задачи варианта
3. Создать программу и провести тесты
4. Запротоколировать сеанс


## 8. Распечатка протокола
main.c
```C
#include <stdio.h>
#include <string.h>
#include "stack.h"

#define VALID_USER_INPUT(x) ((x) == '1' || (x) == '2' || (x) == '3' || (x) == '4' || (x) == '5' || (x) == '6')

void help();
void print(T value);

int main() {
    int exited = 0;
    T value;
    char c;
    stack head;
    head.top = NULL;
    char user_input[BUFSIZ];

    help();

    while (!exited) {
        printf(">>>");
        scanf("%s", user_input);
        if (strlen(user_input) != 1 || !VALID_USER_INPUT(*user_input)) {
            printf("Invalid input! Try again...\n\n");
            continue;
        }

        switch (*user_input - 48)
        {
            case 1: // add value to stack_item
                printf("Input values to add: ");
                while (scanf("%d%c", &value, &c)) {
                    printf("%s", get_error_msg(stack_push(&head, value)));
                    if (c == '\n') {
                        break;
                    }
                }
                break;

            case 2: // print stack_item -> traverse
                printf("%s", get_error_msg(stack_traverse(head, print)));
                break;

            case 3: // sort stack_item by insertions
                printf("%s", get_error_msg(stack_sort(&head)));
                break;

            case 4: // help menu
                help();
                break;

            case 5: // destroy stack_item
                printf("%s", get_error_msg(stack_destroy(&head)));
                break;

            case 6: // exit
                exited = 1;
                putchar('\n');
                break;
        }
    }
    return 0;
}

void help()
{
    printf("The program operates with stack_item structure with items of int type\n");
    printf("    1 - add value to stack_item\n");
    printf("    2 - print stack_item\n");
    printf("    3 - sort stack_item by insertions\n");
    printf("    4 - help menu\n");
    printf("    5 - destroy stack_item\n");
    printf("    6 - exit\n\n");
}

void print(T value)
{
    printf(" >> %d", value);
}
```

stack.c
```C
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
```

stack.h
```C
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
```

## 9. Дневник отладки

| №  | Лаб. или дом. | Дата       | Время | Событие   | Действие по исправлению | Примечание          |
|----|---------------|------------|-------|-----------|-------------------------|---------------------|
| 1  | Дом.          | 11.09.2022 | 15:30 | Структура stack вынесена в отдельный struct, реализована возиможность сообщения об ошибке        | --                      | Возможно, это поможет пониманию читателя |

## 10. Замечания автора по существу работы

Лабораторная показалась интересной и довольно простой. Работа с сортировками в контексте определённого АТД особенно понравилась.

## 11. Выводы

Изучила принципы работы утилиты make, абстрактные типы данных и модульное программирование.
