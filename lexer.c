#include "../include/lexer.h"

void dfa_set(DFA *dfa, const int curr_state, const int next_state, const int char_value) {
    dfa->data[curr_state][char_value] = next_state;
}

int dfa_get(DFA *dfa, const int curr_state, const int char_value) {
    return dfa->data[curr_state][char_value];
}

void dfa_set_range(DFA *dfa, const int curr_state, const int next_state, const int char_value_from, const int char_value_to) {
    for (int i = char_value_from; i <= char_value_to; i++)
        dfa_set(dfa, curr_state, next_state, i);
}

DFA dfa_make() {
    DFA dfa;

    // Default initialization
    for (int i = 0; i < 128; i++)
        for (int j = 0; j < 256; j++)
            dfa_set(&dfa, i, -1, j);

    // symbol
    dfa_set_range(&dfa, 0, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 0, 1, (int)'a', (int)'z');
    
    dfa_set_range(&dfa, 1, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 1, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 1, 1, (int)'0', (int)'9');
    
    dfa_set(&dfa, 0, 1, (int)'_');
    dfa_set(&dfa, 1, 1, (int)'_');

    // int_lit
    dfa_set_range(&dfa, 0, 2, (int)'1', (int)'9');
    dfa_set_range(&dfa, 2, 2, (int)'0', (int)'9');
    dfa_set(&dfa, 0, 3, (int)'0');

    // float_lit
    dfa_set(&dfa, 0, 4, (int)'.');
    dfa_set(&dfa, 2, 4, (int)'.');
    dfa_set(&dfa, 3, 4, (int)'.');

    dfa_set_range(&dfa, 4, 5, (int)'0', (int)'9');
    dfa_set_range(&dfa, 5, 5, (int)'0', (int)'9');
    
    // if
    dfa_set(&dfa, 0, 6, (int)'i');

    dfa_set_range(&dfa, 6, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 6, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 6, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 6, 1, (int)'_');
    dfa_set(&dfa, 6, 7, (int)'f');

    dfa_set_range(&dfa, 7, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 7, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 7, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 7, 1, (int)'_');

    // else
    dfa_set(&dfa, 0, 8, (int)'e');

    dfa_set_range(&dfa, 8, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 8, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 8, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 8, 1, (int)'_');
    dfa_set(&dfa, 8, 9, (int)'l');

    dfa_set_range(&dfa, 9, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 9, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 9, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 9, 1, (int)'_');
    dfa_set(&dfa, 9, 10, (int)'s');

    dfa_set_range(&dfa, 10, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 10, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 10, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 10, 1, (int)'_');
    dfa_set(&dfa, 10, 11, (int)'e');

    dfa_set_range(&dfa, 11, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 11, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 11, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 11, 1, (int)'_');

    // for
    dfa_set(&dfa, 0, 12, (int)'f');

    dfa_set_range(&dfa, 12, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 12, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 12, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 12, 1, (int)'_');
    dfa_set(&dfa, 12, 13, (int)'o');

    dfa_set_range(&dfa, 13, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 13, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 13, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 13, 1, (int)'_');
    dfa_set(&dfa, 13, 14, (int)'r');

    dfa_set_range(&dfa, 14, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 14, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 14, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 14, 1, (int)'_');

    // while
    dfa_set(&dfa, 0, 15, (int)'w');

    dfa_set_range(&dfa, 15, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 15, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 15, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 15, 1, (int)'_');
    dfa_set(&dfa, 15, 16, (int)'h');

    dfa_set_range(&dfa, 16, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 16, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 16, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 16, 1, (int)'_');
    dfa_set(&dfa, 16, 17, (int)'i');

    dfa_set_range(&dfa, 17, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 17, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 17, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 17, 1, (int)'_');
    dfa_set(&dfa, 17, 18, (int)'l');

    dfa_set_range(&dfa, 18, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 18, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 18, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 18, 1, (int)'_');
    dfa_set(&dfa, 18, 19, (int)'e');

    dfa_set_range(&dfa, 19, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 19, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 19, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 19, 1, (int)'_');



    dfa_set(&dfa, 0, 20, (int)':');
    dfa_set(&dfa, 20, 21, (int)'=');

    dfa_set(&dfa, 0, 22, (int)';');

    dfa_set(&dfa, 0, 23, (int)'=');
    
    dfa_set(&dfa, 0, 24, (int)'<');
    dfa_set(&dfa, 24, 25, (int)'=');
    dfa_set(&dfa, 24, 26, (int)'-');

    dfa_set(&dfa, 0, 27, (int)'!');
    dfa_set(&dfa, 27, 28, (int)'=');

    dfa_set(&dfa, 0, 29, (int)'>');
    dfa_set(&dfa, 29, 30, (int)'=');

    dfa_set(&dfa, 0, 31, (int)'+');

    dfa_set(&dfa, 0, 32, (int)'-');
    dfa_set(&dfa, 32, 33, (int)'>');

    dfa_set(&dfa, 0, 34, (int)'*');

    dfa_set(&dfa, 0, 35, (int)'/');
    dfa_set(&dfa, 35, 36, (int)'*');
    dfa_set_range(&dfa, 36, 36, 0, 255);
    dfa_set(&dfa, 36, 37, (int)'*');
    dfa_set_range(&dfa, 37, 36, 0, 255);
    dfa_set(&dfa, 37, 37, (int)'*');
    dfa_set(&dfa, 37, 38, (int)'/');

    dfa_set(&dfa, 0, 39, (int)'%');

    dfa_set(&dfa, 0, 40, (int)'^');

    dfa_set(&dfa, 0, 41, (int)'@');

    dfa_set(&dfa, 0, 42, (int)'\\');

    dfa_set(&dfa, 0, 43, (int)'&');

    dfa_set(&dfa, 0, 44, (int)'|');

    dfa_set(&dfa, 0, 45, (int)'(');

    dfa_set(&dfa, 0, 46, (int)')');

    dfa_set(&dfa, 0, 47, (int)'[');

    dfa_set(&dfa, 0, 48, (int)']');

    dfa_set(&dfa, 0, 49, (int)'{');

    dfa_set(&dfa, 0, 50, (int)'}');

    dfa_set(&dfa, 0, 51, (int)'\"');
    dfa_set_range(&dfa, 51, 51, 0, 255);
    dfa_set(&dfa, 51, 52, (int)'\"');

    // int
    dfa_set(&dfa, 6, 53, (int)'n');
    dfa_set_range(&dfa, 53, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 53, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 53, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 53, 1, (int)'_');
    dfa_set(&dfa, 53, 54, (int)'t');
    dfa_set_range(&dfa, 54, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 54, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 54, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 54, 1, (int)'_');

    // real
    dfa_set(&dfa, 0, 55, (int)'r');
    dfa_set_range(&dfa, 55, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 55, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 55, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 55, 1, (int)'_');
    dfa_set(&dfa, 55, 56, (int)'e');
    dfa_set_range(&dfa, 56, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 56, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 56, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 56, 1, (int)'_');
    dfa_set(&dfa, 56, 57, (int)'a');
    dfa_set_range(&dfa, 57, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 57, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 57, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 57, 1, (int)'_');
    dfa_set(&dfa, 57, 58, (int)'l');
    dfa_set_range(&dfa, 58, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 58, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 58, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 58, 1, (int)'_');

    // string
    dfa_set(&dfa, 0, 59, (int)'s');
    dfa_set_range(&dfa, 59, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 59, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 59, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 59, 1, (int)'_');
    dfa_set(&dfa, 59, 60, (int)'t');
    dfa_set_range(&dfa, 60, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 60, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 60, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 60, 1, (int)'_');
    dfa_set(&dfa, 60, 61, (int)'r');
    dfa_set_range(&dfa, 61, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 61, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 61, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 61, 1, (int)'_');
    dfa_set(&dfa, 61, 62, (int)'i');
    dfa_set_range(&dfa, 62, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 62, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 62, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 62, 1, (int)'_');
    dfa_set(&dfa, 62, 63, (int)'n');
    dfa_set_range(&dfa, 63, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 63, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 63, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 63, 1, (int)'_');
    dfa_set(&dfa, 63, 64, (int)'g');
    dfa_set_range(&dfa, 64, 1, (int)'A', (int)'Z');
    dfa_set_range(&dfa, 64, 1, (int)'a', (int)'z');
    dfa_set_range(&dfa, 64, 1, (int)'0', (int)'9');
    dfa_set(&dfa, 64, 1, (int)'_');



    return dfa;
}

// TokenType dfa_state_to_token(const int state) {
//     switch (state) {
//         case  0: return TOK_EOF;
//         case  1: return TOK_SYMBOL;
//         case  2: return TOK_INT_LIT;
//         case  3: return TOK_INT_LIT;
//         case  4: return TOK_ERROR;
//         case  5: return TOK_FLOAT_LIT;
//         case  6: return TOK_SYMBOL;
//         case  7: return TOK_IF_KW;
//         case  8: return TOK_SYMBOL;
//         case  9: return TOK_SYMBOL;
//         case 10: return TOK_SYMBOL;
//         case 11: return TOK_ELSE_KW;
//         case 12: return TOK_SYMBOL;
//         case 13: return TOK_SYMBOL;
//         case 14: return TOK_FOR_KW;
//         case 15: return TOK_SYMBOL;
//         case 16: return TOK_SYMBOL;
//         case 17: return TOK_SYMBOL;
//         case 18: return TOK_SYMBOL;
//         case 19: return TOK_WHILE_KW;
//         case 20: return TOK_COLON;
//         case 21: return TOK_ASSIGN_OP;
//         case 22: return TOK_SEMICOLON;
//         case 23: return TOK_EQUALS_OP;
//         case 24: return TOK_LESS_THAN_OP;
//         case 25: return TOK_LESS_THAN_EQUALS_OP;
//         case 26: return TOK_NOT_OP;
//         case 27: return TOK_NOT_EQUALS_OP;
//         case 27: return TOK_GREATER_THAN_OP;
//         case 28: return TOK_GREATER_THAN_EQUALS_OP;
//         case 29: return TOK_ADD_OP;
//         case 30: return TOK_MUL_OP;
//         case 31: return TOK_MOD_OP;
//         case 32: return TOK_MATMUL_OP;
//         case 33: return TOK_MATSOLVE_OP;
//         case 34: return TOK_ERROR;
//         case 35: return TOK_AND_OP;
//         case 36: return TOK_ERROR;
//         case 37: return TOK_OR_OP;
//         case 38: return TOK_LPAREN; 
//         case 39: return TOK_RPAREN;
//         case 40: return TOK_LBRACK; 
//         case 41: return TOK_RBRACK; 
//         case 42: return TOK_LBRACE; 
//         case 43: return TOK_RBRACE;  
//         case 44: return TOK_ERROR;
//         case 45: return TOK_ERROR;
//         case 46: return TOK_STRING_LIT;
//         default: return TOK_ERROR;
//     }
// }

int look(DFA *dfa, CharStream *stream) {
    int curr_state = 0;
    int prev_state = -1;

    while (curr_state != -1) {
        prev_state = curr_state;
        curr_state = dfa_get(dfa, curr_state, stream->str[stream->index]);
        stream->index++;
    }

    return prev_state;
}