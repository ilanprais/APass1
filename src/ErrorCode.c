#include "ErrorCode.h"

bool error_isSuccess(const ErrorCode code) { return code == ERROR_SUCCESS; }

const char* error_getErrorMessage(const ErrorCode code) {
    switch (code) {
        case ERROR_SUCCESS:
            return "The operation completed successfully";
        case ERROR_NOT_IMPLEMENTED:
            return "The procedure was not implemented";
        case ERROR_MATRIX_MISSING:
            return "The given matrix poiner points to null";
        case ERROR_OUTPUT_MISSING:
            return "The given output pointer points to null";
        case ERROR_MATRIX_INCOMPATIBLE:
            return "Cannot execute function on matrixes as the dimenions do not fit";
        case  ERROR_FAILED_ALLOCATION:
            return "Dymanic memory allocation failed";
        default:
            return "Unexpected error";
    }
}
