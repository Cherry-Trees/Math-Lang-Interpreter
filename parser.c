#include "../include/symbol.h"
#include <stdlib.h>
#include <stdio.h>

Symbol st_symbol_make(char *name, const SymbolType type, const SymbolDataType data_type, const int dim, int *shape, void *data) {
    Symbol s;// = (Symbol *) malloc(sizeof(Symbol));
    s.name = name;
    s.type = type;
    s.data_type = data_type;
    s.dim = dim;
    s.data = data;
    s.shape = shape;
    s.hash_value = st_hash(name);
    return s;
}

SymbolTableNode *st_node_make(Symbol *s, SymbolTableNode *st_node_left, SymbolTableNode *st_node_right) {
    SymbolTableNode *st_node = (SymbolTableNode *) malloc(sizeof(SymbolTableNode));
    st_node->symbol = s;
    st_node->left = st_node_left;
    st_node->right = st_node_right;
    return st_node;
}

SymbolTable st_make(const int st_scope_level, SymbolTable *st_enclosing_scope, SymbolTableNode *st_root) {
    SymbolTable st;
    st.next = NULL;
    st.scope_level = st_scope_level;
    st.enclosing_scope = st_enclosing_scope;
    st.root = st_root;
    return st;
}

int st_hash(char *s_name) {
    unsigned long hash = 5381;
    int c;

    while (c = *s_name++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

Error st_node_lookup(SymbolTableNode *st_node, unsigned long hash_value) {
    printf("hi\n");
    if (!st_node)
        return err_make(ERR_SYM_TABLE_LOOKUP, "Symbol not found", NULL);
    
    if (hash_value < st_node->symbol->hash_value)
        return st_node_lookup(st_node->left, hash_value);
    
    if (hash_value > st_node->symbol->hash_value)
        return st_node_lookup(st_node->right, hash_value);
    
    return err_make(ERR_NONE, NULL, st_node->symbol);
}

Error st_lookup(SymbolTable *st, char *name) {
    if (!st)
        return err_make(ERR_SYM_TABLE_LOOKUP, "Missing symbol table", name);
    
    if (st->enclosing_scope) {
        Error result = st_lookup(st->enclosing_scope, name);
        if (result.type == ERR_NONE)
            return result;
    }
    
    return st_node_lookup(st->root, st_hash(name));
}

Error st_node_insert(SymbolTableNode *st_node, Symbol *s) {
    if (!st_node) {
        
        st_node = st_node_make(s, NULL, NULL);
        // printf("%p", st_node);
        return err_make(ERR_NONE, NULL, st_node);
    }

    if (s->hash_value == st_node->symbol->hash_value)
        return err_make(ERR_SYM_TABLE_INSERT, "Symbol with this name already exists", s);
    
    else {
        if (s->hash_value < st_node->symbol->hash_value)
            st_node->left = (SymbolTableNode *) st_node_insert(st_node->left, s).data;
        
        else
            st_node->right = (SymbolTableNode *) st_node_insert(st_node->right, s).data;
    }
    return err_make(ERR_NONE, NULL, st_node);
}

Error st_insert(SymbolTable *st, Symbol *s) {
    Error result = st_node_insert(st->root, s);
    if (result.type == ERR_NONE)
        st->root = (SymbolTableNode *) result.data;
    return result;
}

void st_node_free(SymbolTableNode *st_node) {
    if (st_node) {
        st_node_free(st_node->left);
        st_node_free(st_node->right);
        free(st_node);
    }
}

Error st_free(SymbolTable *st) {
    if (!st)
        return err_make(ERR_SYM_TABLE_FREE, "Missing symbol table", NULL);
    
    st_node_free(st->root);
    return err_make(ERR_NONE, NULL, NULL);
}