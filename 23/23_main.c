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
