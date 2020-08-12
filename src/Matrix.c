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
        return ERROR_FAILED_ALLOCATION;
    }   
    
    for(int i = 0 ; i < height ; ++i){
        temp->vals[i] = (double*) malloc(sizeof(double) * width); 
         if(temp->vals[i] == NULL){
            return ERROR_FAILED_ALLOCATION;
        }   
    }

    temp->height = height;
    temp->width = width;

    *matrix = temp;
    
    for(int i = 0; i < height ; ++i){
        for(int j = 0; j < width ; ++j){
            (*matrix)->vals[i][j] = 0;
        }
    }
    
      return ERROR_SUCCESS;
}

ErrorCode matrix_print(CPMatrix matrix){

    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    for(int i = 0; i < matrix->height ; ++i){
        for(int j = 0; j < matrix->width ; ++j){
            double val = matrix->vals[i][j];
            printf("%f ", val);
        }
        printf("\n");
    }
    printf("\n");

    return ERROR_SUCCESS;
 }

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {

    if(source == NULL){
        return ERROR_MATRIX_MISSING;
    }
    
    uint32_t height = 0;
    uint32_t width = 0;
    matrix_getHeight(source, &height);
    matrix_getWidth(source, &width);

    matrix_create(result, height, width);

    for(int i = 0; i < height ; ++i){
        for(int j = 0; j < width ; ++j){
           (*result)->vals[i][j] = source->vals[i][j];
        }
    }
    
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {

    if(matrix == NULL){
        return;
    }

    for(int i = 0 ; i < matrix->height ; ++i){
        free(matrix->vals[i]);   
    }
    free(matrix->vals);
    free(matrix);
  
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    
    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    *result = matrix->height;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {

    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    *result = matrix->width;

    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value) {
    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    matrix->vals[rowIndex][colIndex] = value;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value) {
    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    if(value == NULL){
        return ERROR_OUTPUT_MISSING;
    }

    *value = matrix->vals[rowIndex][colIndex];

    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    
    if(lhs == NULL || rhs == NULL){
        return ERROR_MATRIX_MISSING;
    }

    if(lhs->height != rhs->height || lhs->width != rhs->width){
        return ERROR_MATRIX_INCOMPATIBLE;
    }

    ErrorCode err = matrix_create(result, rhs->height, rhs->width);
    if(err != 0){
        return err;
    }

    for(int i = 0; i < rhs->height ; ++i){
        for(int j = 0; j < rhs->width ; ++j){
           double a;
           double b;
           matrix_getValue(lhs, i, j, &a);
           matrix_getValue(rhs, i, j, &b);
           matrix_setValue(*result, i, j, a + b);
        }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {

    if(lhs == NULL || rhs == NULL){
        return ERROR_MATRIX_MISSING;
    }


    if(lhs->width != rhs->height){
        return ERROR_MATRIX_INCOMPATIBLE;
    }

    ErrorCode err = matrix_create(result, lhs->height, rhs->width);
    if(err != 0){
        return err;
    }

    for (int i = 0; i < lhs->height; ++i) {
      for (int j = 0; j < rhs->width; ++j) {
         matrix_setValue(*result, i, j, 0);
         for (int k = 0; k < lhs->width; ++k) {
           double a;
           double b;
           double cur;
           matrix_getValue(lhs, i, k, &a);
           matrix_getValue(rhs, k, j, &b);
           matrix_getValue(*result, i, j, &cur);
           matrix_setValue(*result, i, j, cur + a*b);
         }
      }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {

    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    for(int i = 0; i < matrix->height ; ++i){
        for(int j = 0; j < matrix->width ; ++j){
           double a;
           matrix_getValue(matrix, i, j, &a);
           a = a * scalar;
           matrix_setValue(matrix, i, j, a);
        }
    }

    return ERROR_SUCCESS;
}