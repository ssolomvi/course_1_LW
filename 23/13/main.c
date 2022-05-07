#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define IGNORE '\f'
#define VALUE_NOT_FOUND "Error: value '%c' not found. 'p' to print tree\n"

void print_help()
{
    printf("Operations on general trees\n\n");

    printf("Program operates with a general tree, using commands, supplied by \
tree node's values of type char.\n\n");

    printf("Commands list: \n\
\t a - Add new node, \n\
\t r - Remove subtree, \n\
\t x - Execute task's action (if the tree is a linear list of its vertexes), \n\
\t p - Print tree, \n\
\t h - Show Help message, \n\
\t q - Quit.\n\n");
}

void skip_line()
{
    int c = getchar();
    while ((c != '\n') && (c != EOF)) {
        c = getchar();
    }
}

TreeItem prompt_item(char *prompt_msg)
{
    printf("%s", prompt_msg);
    char c = getchar();
    skip_line();
    return c;
}

int prompt_cmd()
{
    printf(">>> ");

    int c = getchar(), res = c;

    if ((c < 'a') || (c > 'z')) {
        if (c == EOF) {
            printf("\n");
            return EOF;
        } else if (c != '\n') { // (c == '\n') => nothing entered, don't raise error
            printf("Error: syntax error. Expected command. 'h' to get help\n");
        }
        res = IGNORE;
    }

    while ((c != '\n') && (c != EOF)) {
        c = getchar();
    }

    return res;
}

int main(int argc, char *argv[])
{
    if ((argc > 1) && !(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))) {
        print_help();
        exit(0);
    }

    Tree tree = tree_create(prompt_item("Tree's root value: "));

    int cmd = IGNORE;
    while ((cmd = prompt_cmd()) != EOF) {
        TreeItem looking_for, value;
        switch (cmd) {
            case 'a': // add new node with value after parent's node (by value)
                looking_for = prompt_item("Append new node after node with value: ");
                Tree *parent = tree_find(&tree, looking_for);

                if (parent == NULL) {
                    printf(VALUE_NOT_FOUND, looking_for);
                } else {
                    value = prompt_item("New node's value:");
                    tree_add(*parent, value);
                }
                break;

            case 'r': // remove first matching node by value
                looking_for = prompt_item("Value of node to be removed along with subnodes: ");
                Tree *to_remove = tree_find(&tree, looking_for);

                if (to_remove == NULL) {
                    printf(VALUE_NOT_FOUND, looking_for);
                } else {
                    tree_remove(to_remove);
                }
                break;

            case 'x': // if the tree is a linear list
                is_linear_list(tree) ? printf("True\n") : printf("False\n");
                break;

            case 'p': // print tree
                tree_print(tree);
                break;

            case 'q': // quit
                exit(0);

            case 'h': // print help message
                print_help();
                break;

            case IGNORE:
                break;

            default:
                printf("Error: unknown command '%c'. 'h' to get help\n", cmd);
        }
    }

    return 0;
}
