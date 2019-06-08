//
// Created by Martina on 08/06/2019.
//
#include <ntsid.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "include/steganography.h"
#include "include/image_manipulation.h"
#include "include/matrices.h"

void append(char* s, const char* number, size_t* char_array_size, size_t number_size) {
    for (int i = 0; i < number_size; ++i) {
        s[*char_array_size] = number[i];
        *char_array_size += 1;
    }
}

char modifyBit(char n, char p, char b) {
    char mask = 1 << p;
    return (n & ~mask) | ((b << p) & mask);
}

void print_array(char* char_array, size_t char_array_size) {
    for (int k = 0; k < char_array_size; ++k) {
        for (int i = 0; i < 8; i++) {
            printf("%d ", 0 != ((char_array[k] << i) & 0x80));
        }
        printf("\n");
    }
}

BMP_Image* hide_matrix(Matrix* m, char* path, int number_of_bits) {
    char* char_array = malloc(0);
    size_t char_array_size = 0;
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            double number = m->numbers[i][j];
            printf("%f\n", number);
            char aux[sizeof(number)];
            memcpy(aux, &number, sizeof(number));
            append(char_array, aux, &char_array_size, sizeof(number));
        }
    }
    print_array(char_array, char_array_size);
    BMP_Image* image = readBMP(path);
    int data_counter = 0;
    for (int k = 0; k < char_array_size; ++k) {
        for (int i = 0; i < 8; i++) {
            image->data[data_counter] = modifyBit(image->data[data_counter], 7, (char_array[k] << i));
            data_counter += 8;
        }
    }

    return NULL;
}

Matrix* recover_matrix(BMP_Image image, int number_of_bits){

}