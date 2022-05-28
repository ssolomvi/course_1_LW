#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int get_priority(char c)
{
    switch (c) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 100;
    }
}

Tree tree_create(Token tokens[], int idx_left, int idx_right)
{
    Tree result_tree = (Tree) malloc(sizeof(struct tree_node));
    if (idx_left > idx_right) { // for correct unary minus process
        return NULL;
    }

    if (idx_left == idx_right) {
        result_tree->node  = tokens[idx_left];
        result_tree->left  = NULL;
        result_tree->right = NULL;
        return result_tree;
    }

    int priority;
    int minimal_priority = get_priority('a');
    int brackets_count = 0;
    int operator_position;
    // search position of the last operator with the least priority
    for (int i = idx_left; i <= idx_right; ++i) {
        if ((tokens[i].type == BRACKET) && (tokens[i].data.is_left_bracket)) {
            ++brackets_count;
            continue;
        }
        if ((tokens[i].type == BRACKET) && !(tokens[i].data.is_left_bracket)) {
            --brackets_count;
            continue;
        }
        if (brackets_count > 0) { // skip brackets content
            continue;
        }
        if (tokens[i].type == OPERATOR) {
            priority = get_priority(tokens[i].data.operator_name);
            if (priority <= minimal_priority) {
                minimal_priority = priority;
                operator_position = i;
            }
        }
    }
    if ((minimal_priority == get_priority('a')) &&
        (tokens[idx_left].type == BRACKET) &&
        (tokens[idx_left].data.is_left_bracket) &&
        (tokens[idx_right].type  == BRACKET) &&
        !(tokens[idx_right].data.is_left_bracket)) {
        free(result_tree);
        return tree_create(tokens, idx_left + 1, idx_right - 1);
    }

    // as ^ is right-associative operation: 2^3^4 = 2^(3^4)
    // we search for the most left '^' operator
    int i;
    if (tokens[operator_position].data.operator_name == '^') {
        brackets_count = 0;
        for (i = operator_position; i >= idx_left; --i) {
            if ((tokens[i].type == BRACKET) && !(tokens[i].data.is_left_bracket)) {
                ++brackets_count;
                continue;
            }
            if ((tokens[i].type == BRACKET) && (tokens[i].data.is_left_bracket)) {
                --brackets_count;
                continue;
            }
            if (brackets_count > 0) {
                continue;
            }
            if (tokens[i].type == OPERATOR) {
                priority = get_priority(tokens[i].data.operator_name);
                if (priority == 3) {
                    operator_position = i;
                }
            }
        }
    }

    result_tree->node  = tokens[operator_position]; // operator record
    result_tree->left  = tree_create(tokens, idx_left, operator_position - 1);
    result_tree->right = tree_create(tokens, operator_position + 1, idx_right);

    if (result_tree->right == NULL) {
        printf("Epic fail: operator is at the expression's end.");
        exit(1);
    }
    return result_tree;
}

void tree_delete(Tree *tree_to_delete)
{
    if ((*tree_to_delete) != NULL) {
        tree_delete(&((*tree_to_delete)->left));
        tree_delete(&((*tree_to_delete)->right));
    }
    free(*tree_to_delete);
    *tree_to_delete = NULL;
}

void tree_infix(Tree tree)
{
    if (tree != NULL) {
        if (tree->left && tree->right)
            printf("(");

        tree_infix(tree->left);
        token_print(&(tree->node));
        tree_infix(tree->right);

        if (tree->right && tree->left)
            printf(")");
    }
}

void print_with_levels(Tree tree, int level, bool is_left)
{
    if (tree == NULL) {
        return;
    }

    int i;
    print_with_levels(tree->right, level + 1, false);
    for (i = 0; i < level; i++) {
        printf("\t");
    }
    is_left ? printf("-|-- ") : printf("+|-- ");

    token_print(&(tree->node)); printf("\n");
    print_with_levels(tree->left, level + 1, true);
}
