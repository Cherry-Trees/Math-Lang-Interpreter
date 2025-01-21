#include "lexer.h"

static int dfa[26][256];
static bool dfa_inited = 0;
static int line_no = 1;
static char *keywords[12] = {
    "int",
    "real",
    "if",
    "else",
    "for",
    "in",
    "while",
    "procedure",
    "endif",
    "endfor",
    "endwhile",
    "endprocedure",
};

void lex_dfa_init(int dfa[26][256]) {

    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 256; j++)
            dfa[i][j] = -1;
    
    for (char ch = 'A'; ch <= 'Z'; ch++) dfa[0][(int)ch] = 1;
    for (char ch = 'a'; ch <= 'z'; ch++) dfa[0][(int)ch] = 1;
    dfa[0][(int)'_'] = 1;
    for (char ch = 'A'; ch <= 'Z'; ch++) dfa[1][(int)ch] = 1;
    for (char ch = 'a'; ch <= 'z'; ch++) dfa[1][(int)ch] = 1;
    for (char ch = '0'; ch <= '9'; ch++) dfa[1][(int)ch] = 1;
    dfa[1][(int)'_'] = 1;

    for (char ch = '1'; ch <= '9'; ch++) dfa[0][(int)ch] = 2;
    for (char ch = '0'; ch <= '9'; ch++) dfa[2][(int)ch] = 2;
    dfa[2][(int)'.'] = 3;
    for (char ch = '0'; ch <= '9'; ch++) dfa[3][(int)ch] = 4;
    for (char ch = '0'; ch <= '9'; ch++) dfa[4][(int)ch] = 4;
    dfa[0][(int)'0'] = 5;
    dfa[5][(int)'.'] = 3;

    dfa[0][(int)'\"'] = 6;
    for (int i = 0; i < 256; i++) dfa[6][i] = 6;
    dfa[6][(int)'\"'] = 7;

    dfa[0][(int)':'] = 8;
    dfa[8][(int)'='] = 9;

    dfa[0][(int)'+'] = 10;
    dfa[0][(int)'-'] = 11;
    for (char ch = '1'; ch <= '9'; ch++) dfa[11][(int)ch] = 2;
    dfa[11][(int)'0'] = 5;

    dfa[0][(int)'*'] = 12;
    dfa[0][(int)'/'] = 12;
    dfa[0][(int)'@'] = 12;
    dfa[0][(int)'\\'] = 12;

    dfa[0][(int)'^'] = 13;

    dfa[0][(int)'='] = 14;
    dfa[0][(int)'<'] = 15;
    dfa[15][(int)'='] = 14;
    dfa[0][(int)'>'] = 16;
    dfa[16][(int)'='] = 14;
    dfa[0][(int)'!'] = 17;
    dfa[17][(int)'='] = 14;

    dfa[0][(int)'&'] = 18;
    dfa[0][(int)'|'] = 19;

    dfa[0][(int)';'] = 20;
    dfa[0][(int)'('] = 21;
    dfa[0][(int)')'] = 22;
    dfa[0][(int)'['] = 23;
    dfa[0][(int)']'] = 24;
    dfa[0][(int)','] = 25;

    dfa_inited = 1;
}

TokenType lex_get_token_type(const int state) {
    switch (state) {
        case  0: return TOK_ERROR;
        case  1: return TOK_SYMBOL;
        case  2: return TOK_INT_LIT;
        case  3: return TOK_ERROR;
        case  4: return TOK_REAL_LIT;
        case  5: return TOK_INT_LIT;
        case  6: return TOK_ERROR;
        case  7: return TOK_STRING_LIT;
        case  8: return TOK_COLON;
        case  9: return TOK_ASSIGN_OP;
        case 10: return TOK_ADD_OP;
        case 11: return TOK_ADD_OP;
        case 12: return TOK_MUL_OP;
        case 13: return TOK_EXP_OP;
        case 14: return TOK_RELOP_OP;
        case 15: return TOK_RELOP_OP;
        case 16: return TOK_RELOP_OP;
        case 17: return TOK_NOT_OP;
        case 18: return TOK_AND_OP;
        case 19: return TOK_OR_OP;
        case 20: return TOK_SEMICOLON;
        case 21: return TOK_LPAREN;
        case 22: return TOK_RPAREN;
        case 23: return TOK_LBRACK;
        case 24: return TOK_RBRACK;
        case 25: return TOK_COMMA;
        
        default: return TOK_EOF;
    }
}

TokenType lex_get_kw_token_type(const int index) {
    switch (index) {
        case  0: return TOK_INT_KW;
        case  1: return TOK_REAL_KW;
        case  2: return TOK_IF_KW;
        case  3: return TOK_ELSE_KW;
        case  4: return TOK_FOR_KW;
        case  5: return TOK_IN_KW;
        case  6: return TOK_WHILE_KW;
        case  7: return TOK_PROCESS_KW;
        case  8: return TOK_ENDIF_KW;
        case  9: return TOK_ENDFOR_KW;
        case 10: return TOK_ENDWHILE_KW;
        case 11: return TOK_ENDPROCESS_KW;

        default: return TOK_ERROR;
    }
}

int lex_get_token(Token *tok, const char *is, int index) {
    tok->index = 0;
    tok->line_no = line_no;
    tok->type = TOK_ERROR;
    tok->value[0] = 0;
    if (!is || !tok)
        return -1;
    
    // Remove ws
    char ch = is[index];
    while (ch == ' ' || ch == '\t' || ch == '\n') {
        if (ch == '\n') 
            tok->line_no = ++line_no;
        ch = is[++index];
    }

    ch = 0;
    int curr_state = 0;
    int prev_state = -1;
    if (!dfa_inited)
        lex_dfa_init(dfa);
    while (curr_state != -1) {
        ch = is[index++];
        while (ch == '#') {
            while (ch != '\n')
                ch = is[index++];
            ch = is[index++];
        }
        // printf("%c\n", ch);
        tok->value[tok->index++] = ch;
        prev_state = curr_state;
        curr_state = dfa[curr_state][(int)ch];
    }
    --index;
    tok->value[--tok->index] = 0;
    if (*tok->value)
        tok->type = lex_get_token_type(prev_state);
    else
        tok->type = TOK_EOF;
        
    if (tok->type == TOK_SYMBOL) {
        for (int i = 0; i < 12; i++) {
            bool is_kw = 1;
            int j = 0;
            while (j < tok->index) {
                if (!keywords[i][j] || (keywords[i][j] != tok->value[j])) {
                    is_kw = 0;
                    break;
                }
                j++;
            }
            if (is_kw && !keywords[i][j]) {
                tok->type = lex_get_kw_token_type(i);
                break;
            }
        }
    }
    return index;
}
