#ifndef LEXER_H
#define LEXER_H

typedef enum TokenType {
    TOK_ERROR = -1,
    TOK_EOF,
    TOK_COMMENT,
    TOK_SYMBOL,
    TOK_COLON,
    TOK_SEMICOLON, // Instruction delimiter.
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACK,
    TOK_RBRACK,
    TOK_LBRACE,
    TOK_RBRACE,

    TOK_INT_LIT,
    TOK_FLOAT_LIT,
    TOK_STRING_LIT,
    TOK_INT_KW,
    TOK_FLOAT_KW,
    TOK_STRING_KW,
    TOK_IF_KW,
    TOK_ELSE_KW,
    TOK_FOR_KW,
    TOK_IN_KW,
    TOK_WHILE_KW,

    TOK_ASSIGN_OP,
    TOK_ADD_OP,
    TOK_MUL_OP,
    TOK_MOD_OP,
    TOK_MATMUL_OP,
    TOK_MATSOLVE_OP,
    TOK_NOT_OP,
    TOK_EQUALS_OP,
    TOK_NOT_EQUALS_OP,
    TOK_GREATER_THAN_OP,
    TOK_GREATER_THAN_EQUALS_OP,
    TOK_LESS_THAN_OP,
    TOK_LESS_THAN_EQUALS_OP,
    TOK_AND_OP,                 // &&           
    TOK_OR_OP,
} TokenType;

typedef struct DFA {
    char data[128][256];
} DFA;

void dfa_set(DFA *dfa, const int value, const int row, const int col);
int dfa_get(DFA *dfa, const int row, const int col);
DFA dfa_make();

typedef struct Token {
    TokenType type;
    char *value;
} Token;

typedef struct CharStream {
    char *str;
    int index;
} CharStream;





#endif