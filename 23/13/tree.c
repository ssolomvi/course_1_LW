#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "tree.h"

// Forest = list of trees
// Tree = node's value + children forest + pointer to first child (for convenience)

typedef struct tagForest *Forest;

struct tagTree {
    TreeItem value;
    Forest children;    // Double-linked list of child trees (== Forest)
    Forest first_child; // Only for convenience!
};

struct tagForest {
    Tree node;
    Forest next;
    Forest prev;
};


Forest forest_create(Tree tree);
Forest forest_append_tree(Forest forest, Tree tree);


Tree tree_create(TreeItem rootValue)
{
    Tree result = (Tree) malloc(sizeof(*result));

    result->value = rootValue;
    result->children = NULL;
    result->first_child = NULL;

    return result;
}

Forest forest_create(Tree tree)
{
    Forest result = (Forest) malloc(sizeof(*result));

    result->node = tree;
    result->next = NULL;
    result->prev = NULL;

    return result;
}

Tree *tree_add(Tree parent, TreeItem value)
{
    Tree child = tree_create(value);

    if (parent->children == NULL) {
        parent->children = forest_create(child);
        parent->first_child = parent->children;
    } else {
        parent->children = forest_append_tree(parent->children, child);
    }

    return &(parent->children->node);
}

Forest forest_append_tree(Forest forest, Tree tree)
{
    Forest result = forest_create(tree);

    result->prev = forest;
    forest->next = result;

    return result;
}

void tree_print_children(Tree tree, int depth)
{
    if (tree == NULL) {
        return;
    }

    if (tree->children != NULL) {
        for (int i = 0; i < depth; ++i) {
            printf("      ");
        }
        depth == 0 ? printf("%c|\n", tree->value) : printf("|---%c\n", tree->value);
        for (Forest child = tree->first_child; child != NULL; child = child->next) {
            tree_print_children(child->node, depth + 1);
        }
    } else {
        for (int i = 0; i < depth; ++i) {
            printf("      ");
        }
        printf("|---%c|\n", tree->value);
    }
}

void tree_print(Tree tree)
{
    if (tree != NULL && tree->children != NULL) {
        tree_print_children(tree, 0);
    } else {
        printf("Empty tree\n");
    }
}

void tree_remove(Tree *tree)
{
    if (((*tree) != NULL) && ((*tree)->children != NULL)) {
        Forest child = (*tree)->first_child;

        while (child != NULL) {
            free(child->prev);
            tree_remove(&(child->node));
            child = child->next;
        }

        free((*tree)->children);
    }

    free(*tree);
    *tree = NULL;
}

Tree *tree_find(Tree *tree, TreeItem c)
{
    if ((*tree) == NULL) {
        return NULL;
    }

    if ((*tree)->value == c) {
        return tree;
    }

    Tree *result = NULL;

    if ((*tree)->children != NULL) {
        for (Forest child = (*tree)->first_child; result == NULL && child != NULL;
             child = child->next) {
            result = tree_find(&(child->node), c);
        }
    }

    return result;
}

bool is_linear_list(Tree tree)
{
    if (tree == NULL) {
        return false;
    } else if (tree->children == NULL) {
        return true;
    }

    bool is_internal = true;

    for (Forest child = tree->first_child; child != NULL; child = child->next) {
        if (child->next != NULL && child->next->node != NULL) {
            return false;
        }
    }
    return is_internal;
}
