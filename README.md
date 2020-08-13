# Assignment 1 - matrix
## Overview
In this assignment I wrote a c library for matrix operations.
A program using the library can use the functions and operate on matrixes;
**matrix_create** will create a new dynamically allocated matrix, and functions like
**matrix_add** and **matrix_multiplyWithScalar** can be used on the matrix (or matrixes).

## Functions
The following function were implemented:
```c
ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width);
```
This function recieves a pointer to a pointer to a matrix and allocates in the memory the neccesary
space, sets the values to 0, and points the pointer to the matrix allocated in the memory.
```c
ErrorCode matrix_copy(PMatrix* result, CPMatrix source);
```
This function creates a deep copy of a matrix by copying each cell of the matrix.
```c
void matrix_destroy(PMatrix matrix);
```
This function frees all the heap memory taken by the matrix.

```c
ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result);

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result);

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value);

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value);
```
These function are quite straightforward; get height or width of a matrix, set a value to a matrix cell, or get a value from a matrix cell.

```c
ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs);

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs);

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar);
```
These function are the main operations we can do on a matrix or matrixes; add or multiply 2 matrixes and put the result into a given matrix, 
or multiply a single matrix with a given scalar.

```c
ErrorCode matrix_print(CPMatrix matrix);

```
This function will print the matrix in a visual format on the console.


## Details
the code was written by Ilan Prais
**ID 329034557**
