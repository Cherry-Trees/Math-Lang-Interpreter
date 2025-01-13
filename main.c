#include <stdio.h>
#include <string.h>
#include "../include/symbol.h"
#include "../include/lexer.h"

int main() {
    // int data[5] = {1, 3, 5, 7, 9};
    // Symbol sym1 = st_symbol_make("x", SYM_VARIABLE, SYMDATA_DOUBLE, 1, (int *)5, data);
    // Symbol sym2 = st_symbol_make("y", SYM_VARIABLE, SYMDATA_DOUBLE, 0, NULL, (int *)7);
    // Symbol sym3 = st_symbol_make("z", SYM_VARIABLE, SYMDATA_DOUBLE, 0, NULL, (int *)100);

    // SymbolTable global_st = st_make(0, NULL, NULL);
    // SymbolTable function_st = st_make(1, &global_st, NULL);

    // Error ins_res1 = st_insert(&global_st, &sym1);
    // Error ins_res2 = st_insert(&global_st, &sym2);

    // Error ins_res3 = st_insert(&function_st, &sym3);


    // Error lu_res1 = st_lookup(&function_st, "z");


    // printf("%s\n", ((Symbol *)lu_res1.data)->name);



    DFA dfa = dfa_make();

    int token = -1;

    while (token != TOK_EOF) {
        char symbol;
        char buffer[128];
        short i = 0;
        int token = 0;
        while (symbol != '\0') {
            symbol = getchar();
            buffer[i++] = symbol;
        }
        putchar('\n');
        printf("%s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    return 0;
}