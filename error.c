#include "../include/error.h"

Error err_make(const ErrorType error_type, char *error_msg, void *error_data) {
    Error error;
    error.type = error_type;
    error.msg = error_msg;
    error.data = error_data;
    return error;
}