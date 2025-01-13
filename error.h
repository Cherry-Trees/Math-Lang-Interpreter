#ifndef ERROR_H
#define ERROR_H

typedef enum ErrorType {
    ERR_NONE,
    ERR_TYPE,
    ERR_GENERIC,
    ERR_SYNTAX,
    ERR_TODO,

    ERR_SYM_TABLE_HASH,
    ERR_SYM_TABLE_INSERT,
    ERR_SYM_TABLE_REMOVE,
    ERR_SYM_TABLE_LOOKUP,
    ERR_SYM_TABLE_FREE

} ErrorType;

typedef struct Error {
    ErrorType type;
    char *msg;
    void *data;
} Error;

Error err_make(const ErrorType error_type, char *error_msg, void *error_data);

#endif