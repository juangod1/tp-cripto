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

uint8_t * get_dimensions(GMatrix * sh)
{
    int rows = sh->rows;
    int cols = sh->columns;

    char * ret = malloc(8*sizeof(char));
    sprintf(ret,"%03dx%03d",rows,cols);
    return (uint8_t *) ret;
}

void mock_save_sh(GMatrix * sh, char * path)
{
    size_t size = 0;
    uint8_t * bytes = (uint8_t *) build_char_array(sh,&size);
    uint8_t * dimensions = get_dimensions(sh);

    FILE * file = fopen(path,"w+");

    fwrite(dimensions,7* sizeof(char),1,file);
    fwrite(bytes,size,1,file);
    fclose(file);

    free(dimensions);
    free(bytes);
}

int get_rows(uint8_t * result)
{
    char * row = malloc(4*sizeof(char));
    for(int i=0; i<3;i++)
    {
        row[i]=result[i];
    }
    row[3]=0;
    return atoi(row);
}
int get_cols(uint8_t * result)
{
    char * col = malloc(4*sizeof(char));
    int offset = 4;
    for(int i=0; i<3;i++)
    {
        col[i]=result[i+offset];
    }
    col[3]=0;
    return atoi(col);

}

int get_number(uint8_t * data_start, int row, int column, int row_size)
{
    uint8_t * data_ptr = data_start+(row*row_size)+column;
    return (int) *data_ptr;
}

Matrix * mock_recover_sh(char * path)
{
    size_t size = 270000;
    FILE * file = fopen(path,"r");

    uint8_t * result = malloc(size);

    fread(result,size,1,file);
    fclose(file);
    int rows = get_rows(result);
    int cols = get_cols(result);

    Matrix * ret = constructor(rows,cols);

    uint8_t * data_start = result+7;

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            ret->numbers[j][i]=get_number(data_start,i,j,cols);
        }
    }
    free(result);
    return ret;
}