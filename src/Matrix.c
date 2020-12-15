#include "Matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct Matrix {
    double** vals;
    uint32_t height;
    uint32_t width;
};

ErrorCode matrix_create(PMatrix* matrix, const uint32_t height, const uint32_t width) {

    if(height < 0 || width < 0){
        return ERROR_MATRIX_INCOMPATIBLE;
    }

    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }
      
    PMatrix temp = (PMatrix) malloc(sizeof(**matrix));
    temp->vals = (double**)malloc(sizeof(double*) * height); 
    
    if(temp->vals == NULL){
        free(matrix);
        return ERROR_FAILED_ALLOCATION;
    }   
    
    for(uint32_t i = 0 ; i < height ; ++i){
        temp->vals[i] = (double*) malloc(sizeof(double) * width); 
        if(temp->vals[i] == NULL){
            for(uint32_t j = 0 ; j < i ; ++j){
                 free(temp->vals[i]);   
            }
            free(temp->vals);
            free(matrix);
            return ERROR_FAILED_ALLOCATION;
        }   
    }

    temp->height = height;
    temp->width = width;

    *matrix = temp;
    
    for(uint32_t i = 0; i < height ; ++i){
        for(uint32_t j = 0; j < width ; ++j){
            (*matrix)->vals[i][j] = 0;
        }
    }
    
      return ERROR_SUCCESS;
}

ErrorCode matrix_print(CPMatrix matrix){

    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    for(uint32_t i = 0; i < matrix->height ; ++i){
        for(uint32_t j = 0; j < matrix->width ; ++j){
            double val = matrix->vals[i][j];
            printf("%f ", val);
        }
        printf("\n");
    }
    printf("\n");

    return ERROR_SUCCESS;
 }

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {

    if(source == NULL || result == NULL){
        return ERROR_MATRIX_MISSING;
    }
    
    uint32_t height = source->height;
    uint32_t width = source->width;

    ErrorCode err = matrix_create(result, height, width);
    if(err != 0){
        return err;
    }

    for(uint32_t i = 0; i < height ; ++i){
        for(uint32_t j = 0; j < width ; ++j){
           (*result)->vals[i][j] = source->vals[i][j];
        }
    }
    
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {

    if(matrix == NULL){
        return;
    }

    for(uint32_t i = 0 ; i < matrix->height ; ++i){
        free(matrix->vals[i]);   
    }
    free(matrix->vals);
    free(matrix);
  
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    
    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    if(result ==  NULL){
        return ERROR_OUTPUT_MISSING;
    }

    *result = matrix->height;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {

    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

     if(result == NULL){
        return ERROR_OUTPUT_MISSING;
    }

    *result = matrix->width;

    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, const uint32_t rowIndex, const uint32_t colIndex,
                         const double value) {
    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    matrix->vals[rowIndex][colIndex] = value;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, const uint32_t rowIndex, const uint32_t colIndex,
                          double* value) {

    if(rowIndex < 0 || colIndex < 0){
        return ERROR_MATRIX_INCOMPATIBLE;
    }

    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    if(value == NULL){
        return ERROR_OUTPUT_MISSING;
    }

    *value = matrix->vals[rowIndex][colIndex];

    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix leftMatrix, CPMatrix rightMatrix) {
    
    if(leftMatrix == NULL || rightMatrix == NULL || result == NULL){
        return ERROR_MATRIX_MISSING;
    }

    if(leftMatrix->height != rightMatrix->height || leftMatrix->width != rightMatrix->width){
        return ERROR_MATRIX_INCOMPATIBLE;
    }

    ErrorCode err = matrix_create(result, rightMatrix->height, rightMatrix->width);
    if(err != 0){
        return err;
    }

    for(uint32_t i = 0; i < rightMatrix->height ; ++i){
        for(uint32_t j = 0; j < rightMatrix->width ; ++j){
           double a = leftMatrix->vals[i][j];
           double b = rightMatrix->vals[i][j];
           (*result)->vals[i][j] = a + b;
        }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix leftMatrix, CPMatrix rightMatrix) {

    if(leftMatrix == NULL || rightMatrix == NULL || result == NULL){
        return ERROR_MATRIX_MISSING;
    }


    if(leftMatrix->width != rightMatrix->height){
        return ERROR_MATRIX_INCOMPATIBLE;
    }

    ErrorCode err = matrix_create(result, leftMatrix->height, rightMatrix->width);
    if(err != 0){
        return err;
    }

    for (uint32_t i = 0; i < leftMatrix->height; ++i) {
      for (uint32_t j = 0; j < rightMatrix->width; ++j) {
         (*result)->vals[i][j] = 0;
         for (uint32_t k = 0; k < leftMatrix->width; ++k) {
           double a = leftMatrix->vals[i][k];
           double b = leftMatrix->vals[k][j];
           double cur = (*result)->vals[i][j];
           (*result)->vals[i][j] =  cur + a*b;
         }
      }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, const double scalar) {

    if(matrix == NULL){
        return ERROR_MATRIX_MISSING;
    }

    for(uint32_t i = 0; i < matrix->height ; ++i){
        for(uint32_t j = 0; j < matrix->width ; ++j){
           double a = matrix->vals[i][j];
           a = a * scalar;
           matrix->vals[i][j] = a;
        }
    }

    return ERROR_SUCCESS;
}
