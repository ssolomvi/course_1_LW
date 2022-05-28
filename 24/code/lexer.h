#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdbool.h>

typedef enum {
    FINAL,
    INTEGER,
    FLOATING,
    OPERATOR,
    VARIABLE,
    BRACKET
} TokenType;

typedef struct {
    TokenType type;
    union {
        int   value_int;
        float value_float;
        char  operator_name;
        bool  is_left_bracket;
        char  variable_name;
    } data;
} Token; // tree node

void token_print(Token *token);
void token_next(Token *token);

#endif // __LEXER_H__
