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

Проверять от корня наличие двух не равных NULL "детей". В случае, если дерево пустое, или оба потомка равны NULL, дерево удовлетворяет условиям. В противном случае нет. 
В программе используется меню помощи, в котором есть 6 опций:
1. a - Добавить новый узел,
2. r - Удалить указанный узел, 
3. x - Выполнить задание варианта (проверить, является ли дерево линейным списком своих вершин),
4. p - Напечатать дерево в консоли,
5. h - Показать меню помощи,
6. q - завершить работу программы

## 7. Сценарий выполнения работы

1. Изучить материалы лекции, дополнительные источиники
2. Разработать алгоритм для решения задачи варианта
3. Создать программу и провести тесты
4. Запротоколировать сеанс

Тесты:
1)
```a
Enter a node
6
a
Enter a node
10
a
Enter a node
12
x
The tree IS a linear list of its vertices.
p
              |-------12
       |-------10
|-------6
q

Process finished with exit code 0
```

2)
```h
Commands list:
         a - Add new node,
         r - Remove subtree,
         x - Execute task's action (if the tree is a linear list of its vertexes),
         p - Print tree,
         h - Show Help message,
         q - Quit.

a
Enter a node
5
a
Enter a node
4
a
Enter a node
1
x
The tree IS a linear list of its vertices.
p
|-------5
       |-------4
              |-------1
a
Enter a node
3
p
|-------5
       |-------4
                     |-------3
              |-------1
x
The tree IS NOT a linear list of its vertices.
q

Process finished with exit code 0
```

3)
```
x
The tree IS a linear list of its vertices.
a
Enter a node
13
x
The tree IS a linear list of its vertices.
a
Enter a node
8
a
Enter a node
6
a
Enter a node
7
x
The tree IS NOT a linear list of its vertices.
p
|-------13
       |-------8
                     |-------7
              |-------6
r
Enter a node
6
x
The tree IS a linear list of its vertices.
p
|-------13
       |-------8
              |-------7
q

Process finished with exit code 0
```

## 8. Распечатка протокола
main.c

```C
#include <stdio.h>
#include <string.h>

#include "tree.h"

void help() {
    printf("Commands list: \n\
\t a - Add new node, \n\
\t r - Remove subtree, \n\
\t x - Execute task's action (if the tree is a linear list of its vertexes), \n\
\t p - Print tree, \n\
\t h - Show Help message, \n\
\t q - Quit.\n\n");
}

int main(void)
{
    printf("A program operates with a binary tree, using commands, supplied by \
tree node's values. Type 'h' for help.\n\n");
    Node * tree = NULL; char in[55]; int k;
    while (strcmp(in, "q") != 0) {
        scanf("%s", in);
        if (strcmp(in, "a") == 0) {
            printf("Enter a node \n");
            scanf("%d", &k);
            tree = tree_insert(tree, k);
        }
        if (strcmp(in, "r") == 0) {
            printf("Enter a node \n");
            scanf("%d", &k);
            tree = tree_delete(tree, k);
        }
        if (strcmp(in, "p") == 0) {
            new_print(tree);
        }
        if (strcmp(in, "x") == 0) {
            if (isLinList(tree))
                printf("The tree IS a linear list of its vertices.\n");
            else
                printf("The tree IS NOT a linear list of its vertices.\n");
        }
        if (strcmp(in, "h") == 0) {
            help();
        }
    }
    alldelete(tree);
    return 0;
}
```


tree.c
```C
tree.c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"

typedef int K;

typedef struct Node {
    K key;
    struct Node * left;
    struct Node * right;
} Node;

Node * tree_insert(Node * tree, K key)
{
    if (tree == NULL) {
        Node * t = malloc(sizeof(Node));
        t->key = key;
        t->right = t->left = NULL;
        return t;
    }
    if (tree->key > key)
        tree->left = tree_insert(tree->left, key);
    if (tree->key < key)
        tree->right = tree_insert(tree->right, key);
    return tree;
}

Node * tree_delete(Node * tree, K key)
{
    if (tree == NULL)
        return tree;
    if (key == tree->key){
        Node * tmp;
        if (tree->right == NULL)
            tmp = tree->left;
        else {
            Node * p = tree->right;
            if (p->left == NULL){
                p->left = tree->left;
                tmp = p;
            } else {
                Node * pmin = p->left;
                while (pmin->left != NULL) {
                    p = pmin;
                    pmin = p->left;
                }
                p->left = pmin->right;
                pmin->left = tree->left;
                pmin->right = tree->right;
                tmp = pmin;
            }
        }
        free(tree);
        return tmp;
    } else if (key < tree->key)
        tree->left  = tree_delete(tree->left, key);
    else
        tree->right = tree_delete(tree->right, key);
    return tree;
}

bool LinList(Node * node, int flag)
{
    if (node->left == NULL && flag == 0)
        return ((node->left == NULL && node->right == NULL) || LinList(node->right, 0));
    if (node->right == NULL && flag)
        return ((node->left == NULL && node->right == NULL) || LinList(node->left, 1));
    return 0;
}

bool isLinList(Node * tree)
{
    if (!tree || (tree->left == NULL && tree->right == NULL))
        return true;
    if (tree->left == NULL)
        return LinList(tree->right, 0);
    if (tree->right == NULL)
        return LinList(tree->left, 1);
    return 0;
}

void print_with_levels(Node * tree, int level, bool is_left){
    if (tree == NULL){
        return;
    }
    print_with_levels(tree->right, level + 1, false);
    for (int i = 0; i < level; i++){
        printf("       ");
    }
    printf("|-------%d\n", tree->key);
    print_with_levels(tree->left, level + 1, true);
}

void new_print(Node * tree){
    print_with_levels(tree, 0, false);
}

void alldelete(Node * tree) {
    if (tree != NULL) {
        alldelete(tree->left);
        alldelete(tree->right);
        free(tree);
    }
}
```

tree.h
```C
tree.h
#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int K;
typedef struct Node Node;

Node * tree_insert(Node * tree, K key);
Node * tree_delete(Node * tree, K key);

bool LinList(Node * node, int flag);
bool isLinList(Node * tree);

void print_with_levels(Node * tree, int level, bool is_left);
void new_print(Node * tree);
void alldelete(Node * tree);

#endif // _TREE_H_
```

## 9. Дневник отладки

| №  | Лаб. или дом. | Дата       | Время | Событие   | Действие по исправлению | Примечание          |
|----|---------------|------------|-------|-----------|-------------------------|---------------------|
| 0  | Дом.          | 18.04.2022 | 21:30 | --        | --                      | Всё прошло исправно |

## 10. Замечания автора по существу работы

Работа с динамическими структурами данных и бинарными деревьями показалась интересной, поскольку подобным структурам находиться широкое применение, они довольно просты и очень удобны.

## 11. Выводы

В этой лабораторной работе я узнала, что представляют динамические структуры данных и по каким правилам растут бинарные деревья. Выполнила задание согласно своему варианту.
