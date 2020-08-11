#include <stdio.h>
#include <stdlib.h>

#include "ErrorCode.h"
#include "Matrix.h"

int main(){

    PMatrix matrix = NULL;
    PMatrix other = NULL;
    matrix_create(&matrix, 5, 5);

    matrix_print(matrix, 5, 5);

    matrix_copy(&other, matrix);

    printf("\n");
    matrix_print(other, 5, 5);

    return 0;
}
