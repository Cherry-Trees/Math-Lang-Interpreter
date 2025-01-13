#include "../include/lexer.h"

Token make_token() {
    Token token;
    token.type = EOF_T;
    token.value = '\0';
    return token;
}

Token make_token(const TokenType token_type, const char *token_value) {
    Token token;
    token.type = token_type;
    token.value = token_value;
    return token;
}