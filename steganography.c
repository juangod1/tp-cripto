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

void print_array(const char* char_array, size_t char_array_size) {
    for (int k = 0; k < char_array_size; ++k) {
        for (int i = 0; i < 8; i++) {
            printf("%d", 0 != ((char_array[k] << i) & 0x80));
        }
        printf("\n");
    }
}

void print_hexa_array(const char* char_array, size_t char_array_size) {
    for (int k = 0; k < char_array_size; ++k) {
        printf("%x ", char_array[k] & 0xff);
        if(k % 8 == 7) {
            printf("\n");
        }
    }
}

char modifyBit(char n, char p, char b) {
    char mask = 1 << p;
    return (n & ~mask) | ((b << p) & mask);
}

char* build_char_array(const Matrix* m, size_t* size) {
    char* char_array = malloc(0);

    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            char number = m->numbers[i][j];
            *size += 1;
            char_array = realloc(char_array, *size * sizeof(char));
            char_array[*size - 1] = number;
        }
    }

    return char_array;
}

BMP_Image* lsb_replacement(const char *char_array, size_t char_array_size, BMP_Image* image) {
    int data_counter = 0;
    for (int k = 0; k < char_array_size; ++k) {
        for (int i = 0; i < 8; i++) {
            image->data[data_counter] = modifyBit(image->data[data_counter], 0, 0 != ((char_array[k] << i) & 0x80));
            data_counter++;
        }
    }
//    print_hexa_array(image->data, char_array_size * 8);
    return image;
}

BMP_Image* lsb2_replacement(const char *char_array, size_t char_array_size, BMP_Image* image) {
    int data_counter = 0;
    for (int k = 0; k < char_array_size; ++k) {
        for (int i = 0; i < 8; i++) {
            image->data[data_counter] = modifyBit(image->data[data_counter], 1, 0 != ((char_array[k] << i) & 0x80));
            i++;
            image->data[data_counter] = modifyBit(image->data[data_counter], 0, 0 != ((char_array[k] << i) & 0x80));
            data_counter++;
        }
    }
//    print_hexa_array(image->data, char_array_size * 4);
    return image;
}


BMP_Image* hide_matrix(Matrix* m, char* path, char*path_to_write, int number_of_bits, char shadow_number) {
    size_t char_array_size = 0;
    char* char_array = build_char_array(m, &char_array_size);
//    print_array(char_array, char_array_size);

    BMP_Image* image = readBMP(path);
    image->shadow = shadow_number;
//
//    if(number_of_bits == 1)
//        image = lsb_replacement(char_array, char_array_size, image);
//    else
//        image = lsb2_replacement(char_array, char_array_size, image);

    writeBMP(image, path_to_write);
    return image;
}

Matrix* recover_matrix(BMP_Image image, int number_of_bits){
    return NULL;
}