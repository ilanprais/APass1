#include <stdio.h>
#include <stdlib.h>

#include "ErrorCode.h"
#include "Matrix.h"

int main(){

    ErrorCode ec = ERROR_SUCCESS;
    printf("%d\n", error_isSuccess(ec));
    return 0;
}
