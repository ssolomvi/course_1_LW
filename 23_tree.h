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
