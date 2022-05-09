# Отчет по лабораторной работе N 23 по курсу
# "Фундаментальная информатика"

Студентка группы: M8О-113Б, Соломатина Светлана Викторовна\
Контакты: ssolomvi@gmail.com\
Работа выполнена: 18.04.2022\
Преподаватель: Довженко Анастасия Александровна

## 1. Тема

Динамические структуры данных. Обработка деревьев.

## 2. Цель работы

Научиться работать с динамическими структурами данных и обрабатывать деревья.

## 3. Задание

Вариант 12. Проверить, является ли двоичное дерево линейным списком вершин.

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

Проверять от корневого элемента дерева, используя япостфиксный обход, наличие двух не равных NULL "детей". В случае, если дерево пустое, или потомков не существует, дерево удовлетворяет условиям. В противном случае нет. 
В программе используется меню помощи, в котором есть 6 опций:
1 - Вставка значения в дерево;
2 - Удаление значения из дерева;
3 - Печать дерева;
4 - Выполнение задания варианта (является ли дерево линейным списком);
5 - Спецификация (это меню);
6 - Выход;

## 7. Сценарий выполнения работы

1. Изучить материалы лекции, дополнительные источиники
2. Разработать алгоритм для решения задачи варианта
3. Создать программу и провести тесты
4. Запротоколировать сеанс

Тесты:
1)
```
The program operates with a general tree with items of integer type
    1 - insert value into tree
    2 - remove value from tree
    3 - print tree
    4 - check tree for list structure
    5 - help menu
    6 - exit
Your choose:1
 Input value to insert:1
 Input value of parent element:2

1
Input value to insert:2
 Input value of parent element:1
 1. 1

Select way to inserted item's parent:1

1
Input value to insert:3
 Input value of parent element:2
 1. 1 ---0---> 2

Select way to inserted item's parent:1

1
Input value to insert:4
 Input value of parent element:3
 1. 1 ---0---> 2 ---0---> 3

Select way to inserted item's parent:1

1
Input value to insert:2
 Input value of parent element:1
 1. 1

Select way to inserted item's parent:1

4
Tree is not structured as list

3
Tree state:
--------------------

1|
    2|
        3|
            4|
    2|

--------------------

2
Input value to remove it and it's subtree from tree:2
 1. 1 ---0---> 2
2. 1 ---1---> 2

Select way to [subtree's to remove] root:2


1
Input value to insert:5
 Input value of parent element:4
 1. 1 ---0---> 2 ---0---> 3 ---0---> 4

Select way to inserted item's parent:1

3
Tree state:
--------------------

1|
    2|
        3|
            4|
                5|

--------------------

4
Tree is structured as list
Your choose:6


Process finished with exit code 0
```

2)
```
The program operates with a general tree with items of integer type
    1 - insert value into tree
    2 - remove value from tree
    3 - print tree
    4 - check tree for list structure
    5 - help menu
    6 - exit
Your choose:4
 Tree is not structured as list

1
Input value to insert:1
 Input value of parent element:10

2
Input value to remove it and it's subtree from tree:1
 1. 1

Select way to [subtree's to remove] root:1


4
Tree is not structured as list

3
Tree state:
--------------------


--------------------

1
Input value to insert:4
 Input value of parent element:1

4
Tree is structured as list

3
Tree state:
--------------------

4|

--------------------

6


Process finished with exit code 0
```

3)
```
The program operates with a general tree with items of integer type
    1 - insert value into tree
    2 - remove value from tree
    3 - print tree
    4 - check tree for list structure
    5 - help menu
    6 - exit
Your choose:2
 Input value to remove it and it's subtree from tree:0
 There is no such value = 0 in tree... Try again

1
Input value to insert:2
 Input value of parent element:3

3
Tree state:
--------------------

2|

--------------------

4
Tree is structured as list

6


Process finished with exit code 0
```

4)
```
The program operates with a general tree with items of integer type
    1 - insert value into tree
    2 - remove value from tree
    3 - print tree
    4 - check tree for list structure
    5 - help menu
    6 - exit
Your choose:1
 Input value to insert:1
 Input value of parent element:0

1
Input value to insert:2
 Input value of parent element:1
 1. 1

Select way to inserted item's parent:1

1
Input value to insert:3
 Input value of parent element:1
 1. 1

Select way to inserted item's parent:1

1
Input value to insert:3
 Input value of parent element:2
 1. 1 ---0---> 2

Select way to inserted item's parent:1

1
Input value to insert:4
 Input value of parent element:3
 1. 1 ---0---> 2 ---0---> 3
2. 1 ---1---> 3

Select way to inserted item's parent:1

1
Input value to insert:5
 Input value of parent element:3
 1. 1 ---0---> 2 ---0---> 3
2. 1 ---1---> 3

Select way to inserted item's parent:2

3
Tree state:
--------------------

1|
    2|
        3|
            4|
    3|
        5|

--------------------

4
Tree is not structured as list

r
Invalid input! Try again...

2
Input value to remove it and it's subtree from tree:3
 1. 1 ---0---> 2 ---0---> 3
2. 1 ---1---> 3

Select way to [subtree's to remove] root:2


4
Tree is structured as list

3
Tree state:
--------------------

1|
    2|
        3|
            4|

--------------------

6


Process finished with exit code 0

```

## 8. Распечатка протокола
main.c

```C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

#define VALID_USER_INPUT(x) ((x) == '1' || (x) == '2' || (x) == '3' || (x) == '4' || (x) == '5' || (x) == '6')

void print_item(T, int);
void print_way(way, int, T);
void help();

int main()
{
    int i;
    char user_input[BUFSIZ];
    tree t;
    way_with_target* found_ways_to_parent;
    way_with_target* found_ways_to_value_to_remove;
    way_with_target selected_way_with_target;
    int found_ways_to_parent_count, selected_way_index;
    int found_ways_to_value_to_remove_count;
    bool is_tree_structured_as_list;

    T value_to_insert = -1, parent_value, value_to_remove;
    int exited = 0;

    init_tree(&t);
    help();

    while (!exited)
    {
        scanf("%s", user_input);
        if (strlen(user_input) != 1 || !VALID_USER_INPUT(*user_input))
        {
            printf("Invalid input! Try again...\n\n");
            continue;
        }

        switch (*user_input - 48)
        {
            case 1:
                printf("Input value to insert: ");
                scanf("%d", &value_to_insert);
                // TODO TYPE VALIDATION
                printf("Input value of parent element: ");
                scanf("%d", &parent_value);
                // TODO TYPE VALIDATION

                if (t.root != NULL)
                {
                    find_ways_to(t, parent_value, &found_ways_to_parent, &found_ways_to_parent_count);

                    if (found_ways_to_parent_count == 0) {
                        printf("There is no such value = %d in tree... Try again\n\n", parent_value);
                        continue;
                    }

                    for (i = 0; i < found_ways_to_parent_count; i++) {
                        print_way(found_ways_to_parent[i].way_to_target, i + 1, parent_value);
                    }

                    printf("\nSelect way to inserted item's parent: ");
                    scanf("%d", &selected_way_index);

                    if (selected_way_index <= 0 || selected_way_index > found_ways_to_parent_count) {
                        printf("Invalid selected way index! Try again...\n\n");
                        continue;
                    }

                    selected_way_with_target = found_ways_to_parent[selected_way_index - 1];

                    insert_item(&t, selected_way_with_target.target, value_to_insert);

                    for (i = 0; i < found_ways_to_parent_count; i++)
                    {
                        free(found_ways_to_parent[i].way_to_target.chain);
                    }
                    free(found_ways_to_parent);
                }
                else
                {
                    selected_way_with_target.target = NULL;
                    selected_way_with_target.way_to_target.chain = NULL;
                    selected_way_with_target.way_to_target.chain_length = 0;

                    insert_item(&t, selected_way_with_target.target, value_to_insert);
                }
                printf("\n");
                break;
            case 2:
                printf("Input value to remove it and it's subtree from tree: ");
                // TODO TYPE VALIDATION
                scanf("%d", &value_to_remove);

                found_ways_to_value_to_remove = NULL;
                found_ways_to_value_to_remove_count = 0;
                find_ways_to(t, value_to_remove, &found_ways_to_value_to_remove, &found_ways_to_value_to_remove_count);

                if (found_ways_to_value_to_remove_count == 0)
                {
                    printf("There is no such value = %d in tree... Try again\n\n", value_to_remove);
                    continue;
                }

                for (i = 0; i < found_ways_to_value_to_remove_count; i++)
                {
                    print_way(found_ways_to_value_to_remove[i].way_to_target, i + 1, value_to_remove);
                }

                printf("\nSelect way to [subtree's to remove] root: ");
                scanf("%d", &selected_way_index);

                if (selected_way_index <= 0 || selected_way_index > found_ways_to_value_to_remove_count)
                {
                    printf("Invalid selected way index! Try again...\n\n");
                    continue;
                }

                selected_way_with_target = found_ways_to_value_to_remove[selected_way_index - 1];

                remove_item(&t, selected_way_with_target.target);

                for (i = 0; i < found_ways_to_value_to_remove_count; i++)
                {
                    free(found_ways_to_value_to_remove[i].way_to_target.chain);
                }
                free(found_ways_to_value_to_remove);
                printf("\n\n");
                break;
            case 3:
                printf("Tree state:\n--------------------\n\n");
                prefix_traverse(t, print_item);
                printf("\n--------------------\n\n");
                break;
            case 4:
                is_tree_structured_as_list = is_structured_like_linear_list(t);
                printf("Tree is %structured as list\n\n", is_tree_structured_as_list == yes ? "s" : "not s");
                break;
            case 5:
                help();
                break;
            case 6:
                exited = 1;
                printf("\n");
                break;
        }
    }

    clear(&t);

    return 0;
}

void print_item(T value, int depth)
{
    int i;

    for (i = 0; i < depth; i++)
    {
        printf("    ");
    }

    printf("%d|\n", value);
}

void print_way(way found_way, int index, T target_value)
{
    int i;

    printf("%d. ", index);

    for (i = 0; i < found_way.chain_length; i++)
    {
        printf("%d ---%d---> ", found_way.chain[i].value,
               found_way.chain[i].index_from_parent_item);
    }

    printf("%d\n", target_value);
}

void help()
{
    printf("The program operates with a general tree with items of integer type\n");
    printf("    1 - insert value into tree\n");
    printf("    2 - remove value from tree\n");
    printf("    3 - print tree\n");
    printf("    4 - check tree for list structure\n");
    printf("    5 - help menu\n");
    printf("    6 - exit\n");
    printf("Your choose: ");
}
```


tree.c
```C
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_ways_to(tree context, T value, way_with_target** target_ways, int* target_ways_count)
{
    way constructed_way;
    constructed_way.chain = NULL;
    constructed_way.chain_length = 0;

    *target_ways = NULL;
    *target_ways_count = 0;

    inner_find_ways_to(context.root, value, &constructed_way, target_ways, target_ways_count);

    free(constructed_way.chain);
}

void inner_find_ways_to(tree_item* subtree_root, T value, way* constructed_way,
                        way_with_target** target_ways, int* target_ways_count)
{
    int i;

    if (subtree_root == NULL)
    {
        return;
    }

    if (subtree_root->data == value)
    {
        *target_ways = (way_with_target*)realloc(*target_ways,
                                                 ++*target_ways_count * sizeof(way_with_target));

        (*target_ways)[(*target_ways_count) - 1].target = subtree_root;
        (*target_ways)[(*target_ways_count) - 1].way_to_target.chain_length = constructed_way->chain_length;
        (*target_ways)[(*target_ways_count) - 1].way_to_target.chain = (way_item*)malloc(
                constructed_way->chain_length * sizeof(way_item));
        memcpy((*target_ways)[(*target_ways_count) - 1].way_to_target.chain, constructed_way->chain,
               constructed_way->chain_length * sizeof(way_item));
    }

    constructed_way->chain = (way_item*)realloc(constructed_way->chain,
                                                ++constructed_way->chain_length * sizeof(way_item));
    constructed_way->chain[constructed_way->chain_length - 1].value = subtree_root->data;

    for (i = 0; i < subtree_root->subtrees_count; i++)
    {
        constructed_way->chain[constructed_way->chain_length - 1].index_from_parent_item = i;

        inner_find_ways_to(subtree_root->subtrees + i, value, constructed_way,
                           target_ways, target_ways_count);
    }

    constructed_way->chain = (way_item*)realloc(constructed_way->chain,
                                                --constructed_way->chain_length * sizeof(way_item));
}

void find_parent(tree context, tree_item* child, tree_item** target_parent, int* child_index)
{
    *target_parent = NULL;

    find_parent_inner(context.root, child, target_parent, child_index);
}

void find_parent_inner(tree_item* subtree_root, tree_item* child, tree_item** target_parent, int* child_index)
{
    int i;

    if (subtree_root == NULL)
    {
        return;
    }

    for (i = 0; i < subtree_root->subtrees_count; i++)
    {
        if (subtree_root->subtrees + i == child)
        {
            *target_parent = subtree_root;
            *child_index = i;
            return;
        }

        find_parent_inner(subtree_root->subtrees + i, child, target_parent, child_index);

        if (*target_parent != NULL)
        {
            return;
        }
    }
}

void free_item_and_null(tree_item** to_free)
{
    if (*to_free == NULL)
    {
        // TODO: validation
        return;
    }

    free((*to_free)->subtrees);
    free((*to_free));
    *to_free = NULL;
}

void init_tree(tree* target_tree)
{
    target_tree->root = NULL;
}

void insert_item(tree* target_tree, tree_item* parent_for_item_to_insert, T value)
{
    if (target_tree->root == NULL)
    {
        target_tree->root = (tree_item*)malloc(sizeof(tree_item));
        target_tree->root->data = value;
        target_tree->root->subtrees_count = 0;
        target_tree->root->subtrees = NULL;

        return;
    }

    parent_for_item_to_insert->subtrees = (tree_item*)realloc(parent_for_item_to_insert->subtrees,
                                                              ++parent_for_item_to_insert->subtrees_count * sizeof(tree_item));

    parent_for_item_to_insert->subtrees[parent_for_item_to_insert->subtrees_count - 1].subtrees = NULL;
    parent_for_item_to_insert->subtrees[parent_for_item_to_insert->subtrees_count - 1].subtrees_count = 0;
    parent_for_item_to_insert->subtrees[parent_for_item_to_insert->subtrees_count - 1].data = value;
}

void remove_item(tree* target_tree, tree_item* to_remove)
{
    tree_item* to_remove_parent;
    int to_remove_index_in_parent_context;

    if (target_tree == NULL)
    {
        return;
    }

    if (to_remove == NULL)
    {
        return;
    }

    if (target_tree->root == NULL)
    {
        return;
    }

    if (target_tree->root == to_remove)
    {
        free_item_and_null(&target_tree->root);
        return;
    }

    find_parent(*target_tree, to_remove, &to_remove_parent, &to_remove_index_in_parent_context);

    if (to_remove_parent == NULL)
    {
        printf("The element to remove does not exist. Try again...\n");
        // TODO: val // АШИПКА ПЭРЭНТ НЕ НАЙДЕН! ?? может выведем в консоль? ^_^ А почему мы не инициализируем to_remove_parent?
        return;
    }

    memcpy(to_remove_parent->subtrees + to_remove_index_in_parent_context,
           to_remove_parent->subtrees + to_remove_index_in_parent_context + 1,
           --to_remove_parent->subtrees_count * sizeof(tree_item));

    to_remove_parent->subtrees = (tree_item*)realloc(to_remove_parent->subtrees,
                                                     to_remove_parent->subtrees_count * sizeof(tree_item));
}

void prefix_traverse(tree target_tree, void (*callback)(T value, int depth))
{
    prefix_traverse_inner(target_tree.root, 0, callback);
}

void prefix_traverse_inner(tree_item* subtree_root, int depth, void (*callback)(T value, int depth))
{
    int i;

    if (subtree_root == NULL)
    {
        return;
    }

    callback(subtree_root->data, depth);

    for (i = 0; i < subtree_root->subtrees_count; i++)
    {
        prefix_traverse_inner(subtree_root->subtrees + i, depth + 1, callback);
    }
}

bool is_structured_like_linear_list(tree target_tree)
{
    tree_item* iterator;

    if ((iterator = target_tree.root) == NULL)
    {
        // TODO: ?!
        return no;
    }

    while (1)
    {
        if (iterator->subtrees_count > 1)
        {
            return no;
        }
        else if (iterator->subtrees_count == 0)
        {
            return yes;
        }
        iterator = iterator->subtrees;
    }
}

void clear(tree* target_tree)
{
    if (target_tree == NULL)
    {
        return;
    }

    remove_item(target_tree, target_tree->root);
}
```

tree.h
```C
#ifndef TREE_H
#define TREE_H

typedef int T;

typedef struct tree_item
{
    T data;
    unsigned subtrees_count;
    struct tree_item* subtrees;
} tree_item;

typedef struct tree
{
    tree_item* root;
} tree;

typedef enum bool
{
    yes,
    no
} bool;

typedef struct way_item
{
    T value;
    int index_from_parent_item;
} way_item;

typedef struct way
{
    way_item* chain;
    int chain_length;
} way;

typedef struct way_with_target
{
    way way_to_target;
    tree_item* target;
} way_with_target;

void find_ways_to(tree, T, way_with_target**, int*);
void inner_find_ways_to(tree_item*, T, way*, way_with_target**, int*);
void find_parent(tree, tree_item*, tree_item**, int*);
void find_parent_inner(tree_item*, tree_item*, tree_item**, int*);
void free_item_and_null(tree_item**);
void init_tree(tree*);
void insert_item(tree*, tree_item*, T);
void remove_item(tree*, tree_item*);
void prefix_traverse(tree, void (*)(T value, int depth));
void prefix_traverse_inner(tree_item*, int, void (*)(T value, int depth));
bool is_structured_like_linear_list(tree);
void clear(tree*);

#endif //TREE_H
```

## 9. Дневник отладки

| №  | Лаб. или дом. | Дата       | Время | Событие   | Действие по исправлению | Примечание          |
|----|---------------|------------|-------|-----------|-------------------------|---------------------|
| 0  | Дом.          | 18.04.2022 | 21:30 | --        | --                      | Всё прошло исправно |

## 10. Замечания автора по существу работы

Работа с динамическими структурами данных и бинарными деревьями показалась интересной, поскольку подобным структурам находиться широкое применение, они довольно просты и очень удобны.

## 11. Выводы

В этой лабораторной работе я узнала, что представляют динамические структуры данных и по каким правилам растут деревья. Выполнила задание согласно своему варианту.
