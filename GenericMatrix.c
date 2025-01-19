//
// Created by juraj on 18. 1. 2025.
//

#include "GenericMatrix.h"

#include <stdio.h>
#include <string.h>

GenericMatrix* create_matrix(size_t rows, size_t cols, size_t elemSize) {
    GenericMatrix* matrix = (GenericMatrix*)malloc(sizeof(GenericMatrix));
    if (!matrix) return NULL;

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->elemSize = elemSize;

    // Alokácia dátového poľa
    matrix->data = (void**)malloc(rows * sizeof(void*));
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix->data[i] = malloc(cols * elemSize);
        if (!matrix->data[i])
        {
            for (size_t j = 0; j < i; j++) {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void destroy_matrix(GenericMatrix* matrix) {
    if (!matrix) return;

    for (size_t i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

void* get_element(const GenericMatrix* matrix, size_t row, size_t col) {
    if (!matrix || row >= matrix->rows || col >= matrix->cols) {
        printf("Chyba: Neplatný prístup k prvku (%zu, %zu)\n", row, col);
        return NULL;
    }
    return (void*)((char*)matrix->data[row] + col * matrix->elemSize);
}

void set_element(GenericMatrix* matrix, size_t row, size_t col, const void* value) {
    if (!matrix || row >= matrix->rows || col >= matrix->cols || !matrix->data[row]) {
        printf("Chyba: Neplatný prístup na nastavenie prvku (%zu, %zu)\n", row, col);
        return;
    }
    memcpy((char*)matrix->data[row] + col * matrix->elemSize, value, matrix->elemSize);
}
