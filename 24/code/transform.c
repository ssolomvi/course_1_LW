#include <stdio.h>
#include "tree.h"
#include "transform.h"

void find_minus_operator(Tree* tree)
{
    if (*tree == NULL) {
        return;
    }

    push_minus_up(tree);

    if ((*tree)->node.type == OPERATOR) {
        remove_extra_minuses(tree);
    }

    find_minus_operator(&(*tree)->left);
    find_minus_operator(&(*tree)->right);
}

void push_minus_up(Tree* tree)
{
    if ((*tree) == NULL) {
        return;
    }

    if ((*tree)->node.type == OPERATOR && ((*tree)->node.data.operator_name == '*' || (*tree)->node.data.operator_name == '/')) {
        if ((*tree)->right->node.type == OPERATOR && ((*tree)->right->node.data.operator_name == '*' || (*tree)->right->node.data.operator_name == '/')) {
            push_minus_up(&(*tree)->right);
        }
        if ((*tree)->left->node.type == OPERATOR && ((*tree)->left->node.data.operator_name == '*' || (*tree)->left->node.data.operator_name == '/')) {
            push_minus_up(&(*tree)->left);
        }

        int minus_count = 0;
        if ((*tree)->right->node.type == OPERATOR && (*tree)->right->node.data.operator_name == '-' &&
            (*tree)->right->left == NULL) {
            Tree tmp_for_right = (Tree) malloc(sizeof (struct tree_node));
            copy(&(*tree)->right->right, &tmp_for_right);
            tree_delete(&(*tree)->right);
            (*tree)->right = tmp_for_right;

            minus_count++;
        }

        if ((*tree)->left->node.type == OPERATOR && (*tree)->left->node.data.operator_name == '-' &&
            (*tree)->right->left == NULL) {
            Tree tmp_for_left = (Tree) malloc(sizeof (struct tree_node));
            copy(&(*tree)->left->right, &tmp_for_left);
            tree_delete(&(*tree)->left);
            (*tree)->left = tmp_for_left;

            minus_count++;
        }

        if (minus_count == 1) {
            Tree tmp_for_tree_to_push_minus = (Tree) malloc(sizeof (struct tree_node));
            tmp_for_tree_to_push_minus->node.type = OPERATOR; tmp_for_tree_to_push_minus->node.data.operator_name = '-';
            tmp_for_tree_to_push_minus->left = NULL;
            copy(tree, &tmp_for_tree_to_push_minus->right);
            tree_delete(tree);
            *tree = tmp_for_tree_to_push_minus;
        }
    }

    push_minus_up(&(*tree)->right);
    push_minus_up(&(*tree)->left);
}

// sub_tree is where we suppose to be extra minus, prev_node to remove -- case
void remove_extra_minuses(Tree* prev_node)
{
    if ((*prev_node)->node.type == OPERATOR) {
        char prev_node_operator_name = (*prev_node)->node.data.operator_name;

        if (prev_node_operator_name == '-') {
            if ((*prev_node)->left == NULL) {
                if ((*prev_node)->right->node.type == OPERATOR && (*prev_node)->right->node.data.operator_name == '-' &&
                    (*prev_node)->right->left == NULL) {  // --a

                    Tree new_tree = (Tree) malloc(sizeof(struct tree_node));
                    copy(&(*prev_node)->right->right, &new_tree);
                    tree_delete(prev_node);
                    *prev_node = new_tree;
                    return;
                }
            } else if ((*prev_node)->right->node.type == OPERATOR && (*prev_node)->right->node.data.operator_name == '-' &&
                       (*prev_node)->right->left == NULL) {
                Tree tmp_for_right = (Tree) malloc(sizeof (struct tree_node));
                copy(&(*prev_node)->right->right, &tmp_for_right);
                tree_delete(&(*prev_node)->right);
                (*prev_node)->right = tmp_for_right;

                (*prev_node)->node.data.operator_name = '+';
            } else {
                return;
            }
        }

        if (prev_node_operator_name == '+') {
            if ((*prev_node)->right->node.type == OPERATOR && (*prev_node)->right->node.data.operator_name == '-' &&
                (*prev_node)->right->left == NULL) {
                Tree tmp_for_right = (Tree) malloc(sizeof (struct tree_node));
                copy(&(*prev_node)->right->right, &tmp_for_right);
                tree_delete(&(*prev_node)->right);
                (*prev_node)->right = tmp_for_right;

                (*prev_node)->node.data.operator_name = '-';
            }
        }
    }
}

void do_div(Tree* tree)
{
    if ((*tree) != NULL) {
        find_minus_operator(tree);
        check_if_mult(tree);
    }

    division_transform_iterator(tree);
    division_transform_iterator(tree);
}

// ... / (a*b) -> ... / a / b
void check_if_mult(Tree* tree)
{
    if ((*tree) == NULL) {
        return;
    }

    if ((*tree)->node.type == OPERATOR && (*tree)->node.data.operator_name == '/') {
        if ((*tree)->right->node.type == OPERATOR && (*tree)->right->node.data.operator_name == '*') {
            Tree tmp_for_right = (Tree) malloc(sizeof(struct tree_node));  // ... / (a * B)
            copy(&(*tree)->right->right, &tmp_for_right);

            Tree tmp_for_left = (Tree) malloc(sizeof(struct tree_node));   // ... / (A * b)
            copy(&(*tree)->right->left, &tmp_for_left);

            tree_delete(&(*tree)->right);
            (*tree)->right = tmp_for_right;

            Tree tmp_for_divisible;
            copy(&(*tree)->left, &tmp_for_divisible);
            tree_delete(&(*tree)->left);

            (*tree)->left = (Tree) malloc(sizeof(struct tree_node));
            (*tree)->left->node.type = OPERATOR;
            (*tree)->left->node.data.operator_name = '/';
            copy(&tmp_for_left, &(*tree)->left->right);
            (*tree)->left->left = tmp_for_divisible;
        }
    }
    check_if_mult(&(*tree)->right);
    check_if_mult(&(*tree)->left);
}

// iterator function
void division_transform_iterator(Tree* tree)
{
    Tree buf = NULL;
    if (((*tree) != NULL) && ((*tree)->node.type == OPERATOR) && ((*tree)->node.data.operator_name == '/')) {
        find_div(&(*tree)->left, tree, &buf);
    }

    if ((*tree) != NULL) {
        division_transform_iterator(&((*tree)->left));
        division_transform_iterator(&((*tree)->right));
    }
}

// tree where we suppose to be a division, tree node with div operand, if tree node with div operand was modified
void find_div(Tree* current_tree, Tree* tree_with_div, Tree *where_division_from)
{
    if (*current_tree == NULL) {
        return;
    }

    if (((*tree_with_div)->right->node.type == VARIABLE && (*current_tree)->node.type == VARIABLE &&
         (*tree_with_div)->right->node.data.variable_name == (*current_tree)->node.data.variable_name) ||
       (((*tree_with_div)->right->node.type == FLOATING || (*tree_with_div)->right->node.type == INTEGER) &&
        ((*current_tree)->node.type == FLOATING || (*current_tree)->node.type == INTEGER))) {
        div_transform(current_tree, tree_with_div, where_division_from);

    } else if ((*current_tree)->node.type == OPERATOR) {
        char curr_tree_operator_name = (*current_tree)->node.data.operator_name;

        if (curr_tree_operator_name == '/') {
            find_div(&(*current_tree)->left, current_tree, where_division_from);
            if ((*current_tree)->node.type == OPERATOR && (*current_tree)->node.data.operator_name == '/') {
                find_div(&(*current_tree)->left, tree_with_div, where_division_from);
            }

        } else if (curr_tree_operator_name == '-' || curr_tree_operator_name == '+' || curr_tree_operator_name == '^') {
            return;

        } else if (curr_tree_operator_name == '*') {
            *where_division_from = *current_tree;

            Tree copy_of_right_sub;
            copy(&(*current_tree)->right, &copy_of_right_sub);
            find_div(&(*current_tree)->right, tree_with_div, where_division_from);

            if (*where_division_from != NULL && copy_of_right_sub->node.type == (*current_tree)->right->node.type) {
                find_div(&(*current_tree)->left, tree_with_div, where_division_from);
            }

            *where_division_from = NULL;
            tree_delete(&copy_of_right_sub);
        }
    }
}

void div_transform(Tree *tree_with_division, Tree *tree_node_with_divider, Tree *where_division_from)
{
    if ((*tree_with_division)->node.type == VARIABLE) {
        (*tree_with_division)->node.type = FLOATING; (*tree_with_division)->node.data.value_float = 1;

    } else if ((*tree_with_division)->node.type == INTEGER) {
        (*tree_with_division)->node.type = FLOATING;

        if ((*tree_node_with_divider)->right->node.type == INTEGER) {
            (*tree_with_division)->node.data.value_float = (float) (*tree_with_division)->node.data.value_int /
                                                           (float) (*tree_node_with_divider)->right->node.data.value_int;
        } else {
            (*tree_with_division)->node.data.value_float = (float) (*tree_with_division)->node.data.value_int /
                                                                   (*tree_node_with_divider)->right->node.data.value_float;
        }
    } else {
        if ((*tree_node_with_divider)->right->node.type == INTEGER) {
            (*tree_with_division)->node.data.value_float =         (*tree_with_division)->node.data.value_float /
                                                           (float) (*tree_node_with_divider)->right->node.data.value_int;
        } else {
            (*tree_with_division)->node.data.value_float =         (*tree_with_division)->node.data.value_float /
                                                                   (*tree_node_with_divider)->right->node.data.value_float;
        }
    }

    Tree new_tree;
    copy(&(*tree_node_with_divider)->left, &new_tree);
    tree_delete(tree_node_with_divider); // на что будет ссылаться предыдущий '/'?
    *tree_node_with_divider = new_tree;
    *where_division_from = NULL;
}

void copy(Tree* to_copy, Tree* subtree_copy)
{
    *subtree_copy = (Tree) malloc(sizeof (struct tree_node));
    (*subtree_copy)->node = (*to_copy)->node;

    if ((*to_copy)->right != NULL) {
        copy(&(*to_copy)->right, &(*subtree_copy)->right);
    } else {
        (*subtree_copy)->right = NULL;
    }
    if ((*to_copy)->left != NULL) {
        copy(&(*to_copy)->left, &(*subtree_copy)->left);
    } else {
        (*subtree_copy)->left = NULL;
    }
}
