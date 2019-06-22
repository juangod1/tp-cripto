#ifndef TP_CRIPTO_UTILS_H
#define TP_CRIPTO_UTILS_H

#include <stddef.h>
#include "matrices.h"

#define SUCC 1
#define FAIL -1
#define TRUE 1
#define FALSE 0

typedef struct BitArray{
    int size;
    uint8_t *numbers;
} BitArray;

void print_binary_array(const uint8_t * char_array, size_t char_array_size);
void print_hexa_array(const uint8_t * char_array, size_t char_array_size);
BitArray * build_bit_array_from_matrix(const Matrix *m);
BitArray* copy(BitArray* bit_array);
BitArray* concatenate(BitArray* dest, BitArray* src);
BitArray* concatenate_bit_array(const BitArray* ba1, const BitArray* ba2);
BitArray* construct_bit_array(int size);
void destroy_bit_array(BitArray* bit_array);
void print_bit_array(BitArray* bit_array);
Matrix* build_matrix_from_array(const uint8_t *bit_array, int rows, int columns);
int bit_array_equals(const BitArray* array1, const BitArray* array2);

#endif //TP_CRIPTO_UTILS_H
