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
