#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "include/Gmatrices.h"
#include "include/utils.h"

#define SIZE_BATCH 100

BitArray* construct_bit_array(int size) {
    BitArray* bit_array = malloc(sizeof(BitArray));
    bit_array->numbers = calloc(size, sizeof(uint8_t));
    bit_array->size = size;
    return bit_array;
}

BitArray* copy(BitArray* bit_array) {
    BitArray* new_bit_array = malloc(sizeof(BitArray));
    memcpy(new_bit_array, bit_array, bit_array->size);
    return new_bit_array;
}

void initialize(BitArray* bit_array, uint8_t* array, int size) {
    memcpy(bit_array->numbers, array, size);
}


BitArray* concatenate_bit_array(const BitArray* array1, const BitArray* array2) {
    BitArray* result = construct_bit_array(array1->size + array2->size);
    initialize(result, array1->numbers, array1->size);
    memcpy(result->numbers + array1->size, array2->numbers, array2->size);
    return result;
}

BitArray* concatenate(BitArray* dest, BitArray* src) {
    int new_size = dest->size + src->size;
    dest->numbers = realloc(dest->numbers, new_size * sizeof(uint8_t));

    if(dest->numbers == NULL)
        return NULL;

    memcpy(dest->numbers + dest->size, src->numbers, src->size);
    dest->size = new_size;
    return dest;
}

BitArray * build_bit_array_from_matrix(const Matrix *m) {
    size_t size = 0;
    BitArray* bit_array = construct_bit_array(m->rows * m->columns);

    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            uint8_t number = (uint8_t ) m->numbers[j][i];

            if(size % SIZE_BATCH == 0) {
                bit_array->numbers = realloc(bit_array->numbers, (size + SIZE_BATCH) * sizeof(uint8_t));
            }

            bit_array->numbers[size] = number;
            size += 1;
        }
    }

    bit_array->size = size;
    return bit_array;
}

GMatrix* build_Gmatrix_from_array(const uint8_t *bit_array, int rows, int columns) {
    GMatrix* matrix = Gconstructor(rows, columns);
    int size_array = rows * columns;
    int array_counter = 0;

    for (int i = 0; i < rows && array_counter < size_array; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix->numbers[j][i] = bit_array[array_counter];
            array_counter++;
        }
    }

    return matrix;
}

Matrix* build_matrix_from_array(const uint8_t *bit_array, int rows, int columns) {
    Matrix* matrix = constructor(rows, columns);
    int size_array = rows * columns;
    int array_counter = 0;

    for (int i = 0; i < rows && array_counter < size_array; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix->numbers[j][i] = bit_array[array_counter];
            array_counter++;
        }
    }

    return matrix;
}

void print_bit_array(BitArray* bit_array) {
//    print_hexa_array(bit_array->numbers, bit_array->size);
    for (int i = 0; i < bit_array->size; ++i) {
        printf("%d ", bit_array->numbers[i]);
    }
    printf("\n");
}

int bit_array_equals(const BitArray* array1, const BitArray* array2) {
    if(array1->size != array2->size)
        return 0;

    for (int i = 0; i < array1->size; ++i) {
        if(array1->numbers[i] != array2->numbers[i])
            return 0;
    }
    return 1;
}

void destroy_bit_array(BitArray* bit_array) {
    free(bit_array->numbers);
    free(bit_array);
}

