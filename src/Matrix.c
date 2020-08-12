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
    
    for(int i = 0 ; i < height ; ++i){
        temp->vals[i] = (double*) malloc(sizeof(double) * width); 
         if(temp->vals[i] == NULL){
            return -1;
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
        return -1;
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
        return -1;
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

    for(int i = 0 ; i < matrix->height ; ++i){
        free(matrix->vals[i]);   
    }
    free(matrix->vals);
    free(matrix);
  
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    
    if(matrix == NULL){
        return -1;
    }

    *result = matrix->height;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {

    if(matrix == NULL){
        return -1;
    }

    *result = matrix->width;

    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value) {
    if(matrix == NULL){
        return -1;
    }

    matrix->vals[rowIndex][colIndex] = value;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value) {
    if(matrix == NULL){
        return -1;
    }

    *value = matrix->vals[rowIndex][colIndex];

    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    
    if(lhs == NULL || rhs == NULL){
        return -1;
    }

    if(lhs->height != rhs->height || lhs->width != rhs->width){
        return -1;
    }

    matrix_create(result, rhs->height, rhs->width);

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
        return -1;
    }


    if(lhs->width != rhs->height){
        return -1;
    }

    matrix_create(result, lhs->height, rhs->width);

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