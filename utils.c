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

void initialize(BitArray* bit_array, int size, uint8_t* array) {
    memcpy(bit_array->numbers, array, size);
}

BitArray * build_bit_array_from_matrix(const GMatrix *m) {
    size_t size = 0;
    BitArray* bit_array = construct_bit_array(m->rows * m->columns);

    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            uint8_t number = m->numbers[j][i];

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

GMatrix* build_matrix(const uint8_t* bit_array, int rows, int columns) {
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

BitArray* concatenate_bit_array(const BitArray* array1, const BitArray* array2) {
    BitArray* result = construct_bit_array(array1->size + array2->size);
    initialize(result, array1->size, array1->numbers);
    memcpy(result->numbers + array1->size, array2->numbers, array2->size);
    return result;
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

