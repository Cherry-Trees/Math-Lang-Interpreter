#ifndef SYMBOL_H
#define SYMBOL_H

#include "error.h"

typedef enum SymbolType SymbolType;
typedef enum SymbolDataType SymbolDataType;
typedef struct Symbol Symbol;
typedef struct SymbolTableNode SymbolTableNode;
typedef struct SymbolTable SymbolTable;


enum SymbolType {
    SYM_CONSTANT,
    SYM_VARIABLE,
    SYM_FUNCTION,
    SYM_PARAMETER
};

enum SymbolDataType {
    SYMDATA_INT, // Note: a string is a 1D tensor of ints cast to char.
    SYMDATA_DOUBLE
};

struct Symbol {
    char *name;
    SymbolType type;
    SymbolDataType data_type;
    int dim;
    int *shape;
    void *data;
    unsigned long hash_value;
};

struct SymbolTableNode {
    Symbol *symbol;
    SymbolTableNode *left;
    SymbolTableNode *right;
};

struct SymbolTable {
    SymbolTableNode *root; // Then here.
    SymbolTable *next; // linked list is kinda ass.
    int scope_level;
    SymbolTable *enclosing_scope; // First look here for symbols.
};

Symbol st_symbol_make(char *name, const SymbolType type, const SymbolDataType data_type, const int dim, int *shape, void *data);
SymbolTableNode *st_node_make(Symbol *s, SymbolTableNode *st_node_left, SymbolTableNode *st_node_right);
int st_hash(char *s_name);
SymbolTable st_make(const int st_scope_level, SymbolTable *st_enclosing_scope, SymbolTableNode *st_root);

Error st_lookup(SymbolTable *st, char *name);
Error st_node_insert(SymbolTableNode *st_node, Symbol *s);
Error st_insert(SymbolTable *st, Symbol *s);
Error st_modify(SymbolTableNode *st_node, Symbol *s);
void st_node_free(SymbolTableNode *st_node);
Error st_free(SymbolTable *st);



#endif