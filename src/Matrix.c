#include "Matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct Matrix {
    double** vals;
    int height;
    int width;
};

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
      
    PMatrix temp = (PMatrix) malloc(sizeof(**matrix));
    temp->vals = (double**)malloc(sizeof(double*) * height); 
    
    if(temp->vals == NULL){
        return -1;
    }   
    
    for(int i = 0 ; i < height ; i++){
        temp->vals[i] = (double*) malloc(sizeof(double) * width); 
         if(temp->vals[i] == NULL){
            return -1;
        }   
    }

    temp->height = height;
    temp->width = width;

    *matrix = temp;
    
    for(int i = 0; i < height ; i++){
        for(int j = 0; j < width ; j++){
            (*matrix)->vals[i][j] = 0;
        }
    }
    
      return ERROR_SUCCESS;
}

ErrorCode matrix_print(PMatrix matrix, uint32_t height, uint32_t width){

    for(int i = 0; i < height ; i++){
        for(int j = 0; j < width ; j++){
            double val = matrix->vals[i][j];
            printf("%f ", val);
        }
        printf("\n");
    }

    return ERROR_SUCCESS;
 }

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    
    uint32_t height = 0;
    uint32_t width = 0;
    matrix_getHeight(source, &height);
    matrix_getWidth(source, &width);

    matrix_create(result, height, width);

    for(int i = 0; i < height ; i++){
        for(int j = 0; j < width ; j++){
           (*result)->vals[i][j] = source->vals[i][j];
        }
    }
    
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) { (void)matrix; }

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    *result = matrix->height;

    return ERROR_NOT_IMPLEMENTED;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
     *result = matrix->width;

    return ERROR_NOT_IMPLEMENTED;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value) {
    (void)matrix;
    (void)rowIndex;
    (void)colIndex;
    (void)value;
    return ERROR_NOT_IMPLEMENTED;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value) {
    (void)matrix;
    (void)rowIndex;
    (void)colIndex;
    (void)value;
    return ERROR_NOT_IMPLEMENTED;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    (void)result;
    (void)lhs;
    (void)rhs;
    return ERROR_NOT_IMPLEMENTED;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    (void)result;
    (void)lhs;
    (void)rhs;
    return ERROR_NOT_IMPLEMENTED;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
    (void)matrix;
    (void)scalar;
    return ERROR_NOT_IMPLEMENTED;
}