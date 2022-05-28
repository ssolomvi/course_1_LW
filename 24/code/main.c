#include <stdio.h>

#include "lexer.h"
#include "tree.h"
#include "transform.h"

int main(void)
{
    printf("Input expression:\n");
    Token tokens[256];
    size_t tokens_qty = 0;

    Token token;
    token_next(&token);

    while (token.type != FINAL) {
        tokens[tokens_qty++] = token;
        token_next(&token);
    }

    Tree tree = tree_create(tokens, 0, tokens_qty - 1);

    printf("\n+| -- right subtree, -| -- left subtree\n");
    printf("Expression tree:\n");
    print_with_levels(tree, 0, false);

    printf("\nSemitransformed expression tree:\n");

    do_div(&tree);
    print_with_levels(tree, 0, false);

    printf("\nTree's infix linearization:\n");
    tree_infix(tree);
    printf("\n");
    tree_delete(&tree);

    return 0;
}
