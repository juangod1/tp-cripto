#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "include/steganography.h"
#include "include/image_manipulation.h"
#include "include/matrices.h"
#include "include/utils.h"

#define SIZE_BATCH 100

char modifyBit(char n, char p, char b) {
    char mask = 1 << p;
    return (n & ~mask) | ((b << p) & mask);
}

BMP_Image* lsb_replacement(BitArray* bit_array, BMP_Image* image) {
    int data_counter = 0;
    for (int k = 0; k < bit_array->size; ++k) {
        for (int i = 0; i < 8; i++) {
            image->data[data_counter] = modifyBit(image->data[data_counter], 0, 0 != ((bit_array->numbers[k] << i) & 0x80));
            data_counter++;
        }
    }
    return image;
}

BMP_Image* lsb2_replacement(BitArray* bit_array, BMP_Image* image) {
    int data_counter = 0;
    for (int k = 0; k < bit_array->size; ++k) {
        for (int i = 0; i < 8; i++) {
            image->data[data_counter] = modifyBit(image->data[data_counter], 1, 0 != ((bit_array->numbers[k] << i) & 0x80));
            i++;
            image->data[data_counter] = modifyBit(image->data[data_counter], 0, 0 != ((bit_array->numbers[k] << i) & 0x80));
            data_counter++;
        }
    }
    return image;
}

BMP_Image* hide_matrix(BitArray * bit_array, char* path, int number_of_bits, char shadow_number) {
    BMP_Image* image = readBMP(path);

    if(image == NULL)
        return NULL;

    image->shadow = shadow_number;

    if(number_of_bits == 1)
        image = lsb_replacement(bit_array, image);
    else
        image = lsb2_replacement(bit_array, image);

    if(writeBMP(image, path) == -1)
        return NULL;

//    free(char_array);

    return image;
}

uint8_t reconstruct_number_from_lsb2(BMP_Image *image, int* image_counter) {
    uint8_t number = '0';

    for (int j = 7; j >= 0; --j) {
        int bit = 0 != ((image->data[*image_counter] << 6) & 0x80);
        number = modifyBit(number, j--, bit);
        bit = 0 != ((image->data[*image_counter] << 7) & 0x80);
        number = modifyBit(number, j, bit);
        *image_counter += 1;
    }

    return number;
}

uint8_t reconstruct_number_from_lsb(BMP_Image *image, int* image_counter) {
    uint8_t number = '0';

    for (int j = 7; j >= 0; --j) {
        int bit = 0 != ((image->data[*image_counter] << 7) & 0x80);
        number = modifyBit(number, j, bit);
        *image_counter += 1;
    }

    return number;
}

BitArray * recover_matrix(BMP_Image* image, int number_of_bits) {
    int size = 0;
    BitArray* bit_array = construct_bit_array(size);

    for (int image_counter = 0; image_counter < image->data_size; size++) {
        uint8_t number;

        if(number_of_bits == 1)
            number = reconstruct_number_from_lsb(image, &image_counter);
        else
            number = reconstruct_number_from_lsb2(image, &image_counter);

        if(size % SIZE_BATCH == 0) {
            bit_array->numbers = realloc(bit_array->numbers, (size + SIZE_BATCH) * sizeof(uint8_t));
        }

        bit_array->numbers[size] = number;
    }

    bit_array->size = size;

    return bit_array;
}