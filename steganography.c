#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "include/steganography.h"
#include "include/image_manipulation.h"
#include "include/matrices.h"

#define SIZE_BATCH 100

char modifyBit(char n, char p, char b) {
    char mask = 1 << p;
    return (n & ~mask) | ((b << p) & mask);
}

char* build_char_array(const GMatrix* m, size_t* size_p) {
    size_t size = 0;
    char* char_array = malloc(size);

    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            char number = m->numbers[j][i];
            if(size%SIZE_BATCH==0)
            {
                char_array = realloc(char_array, (size + SIZE_BATCH) * sizeof(char));
            }
            char_array[size] = number;
            size += 1;
        }
    }

    *size_p = size;
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
    return image;
}

BMP_Image* hide_matrix(GMatrix* m, char* path, int number_of_bits, char shadow_number) {
    size_t char_array_size = 0;
    char* char_array = build_char_array(m, &char_array_size);

    BMP_Image* image = readBMP(path);

    if(image == NULL)
        return NULL;

    image->shadow = shadow_number;

    if(number_of_bits == 1)
        image = lsb_replacement(char_array, char_array_size, image);
    else
        image = lsb2_replacement(char_array, char_array_size, image);

    if(writeBMP(image, path) == -1)
        return NULL;

    free(char_array);

    return image;
}

char reconstruct_number_from_lsb2(BMP_Image *image, int* image_counter) {
    char number = '0';
    for (int j = 7; j >= 0; --j) {
        int bit = 0 != ((image->data[*image_counter] << 6) & 0x80);
        number = modifyBit(number, j--, bit);
        bit = 0 != ((image->data[*image_counter] << 7) & 0x80);
        number = modifyBit(number, j, bit);
        *image_counter += 1;
    }
    return number;
}

char reconstruct_number_from_lsb(BMP_Image *image, int* image_counter) {
    char number = '0';
    for (int j = 7; j >= 0; --j) {
        int bit = 0 != ((image->data[*image_counter] << 7) & 0x80);
        number = modifyBit(number, j, bit);
        *image_counter += 1;
    }
    return number;
}

GMatrix* recover_from_lsb2(BMP_Image* image) {
    GMatrix* m = Gconstructor(image->width / 8, image->height / 8);

    for (int image_counter = 0, i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            char number = reconstruct_number_from_lsb2(image, &image_counter);
            m->numbers[i][j] = number;
        }
    }

    return m;
}

GMatrix* recover_from_lsb(BMP_Image* image) {
    GMatrix* m = Gconstructor(image->width / 8, image->height / 8);

    for (int image_counter = 0, i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            char number = reconstruct_number_from_lsb(image, &image_counter);
            m->numbers[i][j] = number;
        }
    }
    return m;
}

GMatrix* recover_matrix(char* path, int number_of_bits){
    BMP_Image* image = readBMP(path);
    GMatrix* m;

    if(number_of_bits == 1)
        m = recover_from_lsb(image);
    else
        m = recover_from_lsb2(image);

    destroyBMP(image);
    return m;
}