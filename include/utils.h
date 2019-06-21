#ifndef TP_CRIPTO_UTILS_H
#define TP_CRIPTO_UTILS_H

#include <stddef.h>
#include "Gmatrices.h"

#define SUCC 1
#define FAIL -1
#define TRUE 1
#define FALSE 0

typedef struct BitArray{
    int size;
    uint8_t *numbers;
} BitArray;

void print_binary_array(const char *char_array, size_t char_array_size);
void print_hexa_array(const char* char_array, size_t char_array_size);
BitArray * build_bit_array_from_matrix(const GMatrix *m);
BitArray* copy(BitArray* bit_array);
BitArray* concatenate_bit_array(const BitArray* array1, const BitArray* array2);
GMatrix* build_matrix(const uint8_t* bit_array, int rows, int columns);
BitArray* construct_bit_array(int size);
int bit_array_equals(const BitArray* array1, const BitArray* array2);

#endif //TP_CRIPTO_UTILS_H
