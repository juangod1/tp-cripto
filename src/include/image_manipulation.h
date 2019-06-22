#ifndef IMAGE_MANIPULATION_H
#define IMAGE_MANIPULATION_H

#define BMP_COLOR_PLANES_POSITION 0x1A
#define BMP_HEADER_SIZE_POSITION 0x0E
#define BMP_OFFSET_POSITION 0x0A
#define BMP_SIZE_POSITION 0x02
#define BMP_METADATA_POSITION 0x06
#define BMP_HEIGHT_POSITION 0x16
#define BMP_WIDTH_POSITION 0x12
#define BMP_BPP_POSITION 0x1C

#include <stdlib.h>
#include "matrices.h"

typedef struct {
    uint8_t * data;
    int data_size;
    int file_size;
    int offset;
    int width;
    int height;
    char shadow;
    char bpp;
} BMP_Image;

BMP_Image * readBMP(char * path);
int writeBMP(BMP_Image * img, char * path);
void destroyBMP(BMP_Image * bmp);
Matrix* image_to_matrix_conversion(BMP_Image* image);
void createBMP(char * path, int width, int height, int bpp);
void createImageFromMatrices(Matrix ** m, char * path, int amount, int width, int height);
Matrix ** createMatricesFromImage(char * path, int * amount_p, int n);

#endif //IMAGE_MANIPULATION_H