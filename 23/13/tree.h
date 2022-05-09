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
