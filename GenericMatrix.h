//
// Created by juraj on 18. 1. 2025.
//

#ifndef GENERICMATRIX_H
#define GENERICMATRIX_H
#ifndef GENERIC_MATRIX_H
#define GENERIC_MATRIX_H

#include <stdlib.h>

// Generická štruktúra matice
typedef struct {
    void** data;      // Ukazovateľ na dáta
    size_t rows;      // Počet riadkov
    size_t cols;      // Počet stĺpcov
    size_t elemSize;  // Veľkosť jedného prvku
} GenericMatrix;

// Funkcie na prácu s generickou maticou
GenericMatrix* create_matrix(size_t rows, size_t cols, size_t elemSize);
void destroy_matrix(GenericMatrix* matrix);

void* get_element(const GenericMatrix* matrix, size_t row, size_t col);
void set_element(GenericMatrix* matrix, size_t row, size_t col, const void* value);

#endif // GENERIC_MATRIX_H

#endif //GENERICMATRIX_H
