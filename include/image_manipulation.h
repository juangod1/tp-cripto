//
// Created by Juan Godfrid on 2019-06-01.
//

#ifndef matrices_h
#define matrices_h

#define BMP_OFFSET_POSITION 0x0A
#define BMP_SIZE_POSITION 0x02

typedef struct {
    char * data;
    int data_size;
    char shadow;
    char bpp;
} BMP_Image;

BMP_Image * openBMP(char * path);
void destroyBMP(BMP_Image * bmp);

#endif