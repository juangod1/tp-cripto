//
// Created by Juan Godfrid on 2019-06-01.
//

#ifndef matrices_h
#define matrices_h

#define BMP_OFFSET_POSITION 0x0A
#define BMP_SIZE_POSITION 0x02
#define BMP_METADATA_POSITION 0x06
#define BMP_HEIGHT_POSITION 0x12
#define BMP_WIDTH_POSITION 0x16
#define BMP_BPP_POSITION 0x1C

typedef struct {
    void * data;
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

#endif