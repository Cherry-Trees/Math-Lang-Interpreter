#ifndef LEXER_H
#define LEXER_H

#define TOKEN_BUFFER_SIZE 64

#include <stdbool.h>

typedef enum TokenType {
    TOK_ERROR = -1,
    TOK_EOF,
    TOK_SYMBOL,
    TOK_COLON,
    TOK_SEMICOLON, // Instruction delimiter.
    TOK_COMMA,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACK,
    TOK_RBRACK,
    // TOK_LBRACE,
    // TOK_RBRACE,

    TOK_INT_LIT,
    TOK_REAL_LIT,
    TOK_STRING_LIT,
    TOK_INT_KW,
    TOK_REAL_KW,
    TOK_IF_KW,
    TOK_ELSE_KW,
    TOK_FOR_KW,
    TOK_IN_KW,
    TOK_WHILE_KW,
    TOK_PROCESS_KW,
    TOK_ENDIF_KW,
    TOK_ENDFOR_KW,
    TOK_ENDWHILE_KW,
    TOK_ENDPROCESS_KW,

    TOK_ASSIGN_OP,
    TOK_ADD_OP,
    TOK_MUL_OP,
    TOK_EXP_OP,
    TOK_NOT_OP,
    TOK_RELOP_OP,
    // TOK_EQUALS_OP,
    // TOK_NOT_EQUALS_OP,
    // TOK_GREATER_THAN_OP,
    // TOK_GREATER_THAN_EQUALS_OP,
    // TOK_LESS_THAN_OP,
    // TOK_LESS_THAN_EQUALS_OP,
    TOK_AND_OP,                 // &&           
    TOK_OR_OP,
} TokenType;


// void dfa_set(DFA *dfa, const int value, const int row, const int col);
// int dfa_get(DFA *dfa, const int row, const int col);


typedef struct Token {
    TokenType type;
    char value[TOKEN_BUFFER_SIZE];
    int index;
    int line_no;
} Token;

typedef struct CharStream {
    char *str;
    int index;
} CharStream;

void lex_dfa_init(int dfa[25][256]);
TokenType lex_get_token_type(const int state);
TokenType lex_get_kw_token_type(const int index);
int lex_get_token(Token *tok, const char *is, int index);





#endif
