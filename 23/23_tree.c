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
