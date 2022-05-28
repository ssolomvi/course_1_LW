#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include "lexer.h"

typedef struct tree_node *Tree;
struct tree_node {
    Token node;
    Tree left;
    Tree right;
};

void print_with_levels(Tree tree, int level, bool is_left);


Tree tree_create(Token tokens[], int idx_left, int idx_right);
void tree_infix(Tree tree);
void tree_delete(Tree *tree_to_delete);

#endif // _TREE_H_
