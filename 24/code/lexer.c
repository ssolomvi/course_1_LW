#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "lexer.h"

void token_next(Token *token)
{
    static bool can_be_unary = true; // http://en.wikipedia.org/wiki/Static_variable
    char read_char;

    scanf("%c", &read_char);

    while (read_char == ' ') {
        scanf("%c", &read_char);
    }

    if (read_char == '\n') {
        token->type = FINAL;
    }
    
    else if (isalpha(read_char) || read_char == '_') {
        token->type = VARIABLE;
        token->data.variable_name = read_char;
        can_be_unary = false;
    }
    
    else if (isdigit(read_char)) {
        float result;
        ungetc(read_char, stdin);
        scanf("%f", &result);
        
        if (result == (int) result) {
            token->type = INTEGER;
            token->data.value_int = (int) result;
        } else {
            token->type = FLOATING;
            token->data.value_float = result;
        }
        can_be_unary = false;
    }
    
    else if (read_char == '(' || read_char == ')') {
        token->type = BRACKET;
        token->data.is_left_bracket = (read_char == '(');
        can_be_unary = token->data.is_left_bracket;
    } else {
        token->type = OPERATOR;
        token->data.operator_name = read_char;
        can_be_unary = true;
    }
}

void token_print(Token *token)
{
    switch (token->type) {
        case FINAL:
            break;
        case INTEGER:
            printf("%d", token->data.value_int);
            break;
        case FLOATING:
            printf("%lg", token->data.value_float);
            break;
        case VARIABLE:
            printf("%c", token->data.variable_name);
            break;
        case OPERATOR:
            printf("%c", token->data.operator_name);
            break;
        case BRACKET:
            printf("%c", (token->data.is_left_bracket) ? '(' : ')');
            break;
    }
}
