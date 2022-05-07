#include <stdbool.h>
#ifndef __TREE_H__
#define __TREE_H__

typedef char TreeItem;

typedef struct tagTree *Tree;

Tree   tree_create(TreeItem rootValue);
Tree  *tree_find(Tree *tree, TreeItem c);
Tree  *tree_add(Tree parent, TreeItem value);
void   tree_remove(Tree *tree);
bool   is_linear_list(Tree tree);
void   tree_print(Tree tree);

#endif // __TREE_H__
