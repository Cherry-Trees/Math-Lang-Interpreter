#ifndef TENSOR_H
#define TENSOR_H

typedef struct Tensor {
    int dim;
    int *shape;
    void *data;
} Tensor;



#endif