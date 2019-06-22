#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include "include/image_manipulation.h"
#include "include/matrices.h"
#include "include/utils.h"

#define GREY_BMP_OFFSET_NUMBER 1078
#define COLOR_BMP_OFFSET_NUMBER 54

uint8_t color_table[1024] = {0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x02, 0x02, 0x02, 0x00, 0x03, 0x03, 0x03, 0x00, 0x04, 0x04, 0x04, 0x00, 0x05, 0x05, 0x05, 0x00, 0x06, 0x06, 0x06, 0x00, 0x07, 0x07, 0x07, 0x00, 0x08, 0x08, 0x08, 0x00, 0x09, 0x09, 0x09, 0x00, 0x0A, 0x0A, 0x0A, 0x00, 0x0B, 0x0B, 0x0B, 0x00, 0x0C, 0x0C, 0x0C, 0x00, 0x0D, 0x0D, 0x0D, 0x00, 0x0E, 0x0E, 0x0E, 0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x10, 0x10, 0x10, 0x00, 0x11, 0x11, 0x11, 0x00, 0x12, 0x12, 0x12, 0x00, 0x13, 0x13, 0x13, 0x00, 0x14, 0x14, 0x14, 0x00, 0x15, 0x15, 0x15, 0x00, 0x16, 0x16, 0x16, 0x00, 0x17, 0x17, 0x17, 0x00, 0x18, 0x18, 0x18, 0x00, 0x19, 0x19, 0x19, 0x00, 0x1A, 0x1A, 0x1A, 0x00, 0x1B, 0x1B, 0x1B, 0x00, 0x1C, 0x1C, 0x1C, 0x00, 0x1D, 0x1D, 0x1D, 0x00, 0x1E, 0x1E, 0x1E, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x20, 0x20, 0x20, 0x00, 0x21, 0x21, 0x21, 0x00, 0x22, 0x22, 0x22, 0x00, 0x23, 0x23, 0x23, 0x00, 0x24, 0x24, 0x24, 0x00, 0x25, 0x25, 0x25, 0x00, 0x26, 0x26, 0x26, 0x00, 0x27, 0x27, 0x27, 0x00, 0x28, 0x28, 0x28, 0x00, 0x29, 0x29, 0x29, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x2B, 0x2B, 0x2B, 0x00, 0x2C, 0x2C, 0x2C, 0x00, 0x2D, 0x2D, 0x2D, 0x00, 0x2E, 0x2E, 0x2E, 0x00, 0x2F, 0x2F, 0x2F, 0x00, 0x30, 0x30, 0x30, 0x00, 0x31, 0x31, 0x31, 0x00, 0x32, 0x32, 0x32, 0x00, 0x33, 0x33, 0x33, 0x00, 0x34, 0x34, 0x34, 0x00, 0x35, 0x35, 0x35, 0x00, 0x36, 0x36, 0x36, 0x00, 0x37, 0x37, 0x37, 0x00, 0x38, 0x38, 0x38, 0x00, 0x39, 0x39, 0x39, 0x00, 0x3A, 0x3A, 0x3A, 0x00, 0x3B, 0x3B, 0x3B, 0x00, 0x3C, 0x3C, 0x3C, 0x00, 0x3D, 0x3D, 0x3D, 0x00, 0x3E, 0x3E, 0x3E, 0x00, 0x3F, 0x3F, 0x3F, 0x00, 0x40, 0x40, 0x40, 0x00, 0x41, 0x41, 0x41, 0x00, 0x42, 0x42, 0x42, 0x00, 0x43, 0x43, 0x43, 0x00, 0x44, 0x44, 0x44, 0x00, 0x45, 0x45, 0x45, 0x00, 0x46, 0x46, 0x46, 0x00, 0x47, 0x47, 0x47, 0x00, 0x48, 0x48, 0x48, 0x00, 0x49, 0x49, 0x49, 0x00, 0x4A, 0x4A, 0x4A, 0x00, 0x4B, 0x4B, 0x4B, 0x00, 0x4C, 0x4C, 0x4C, 0x00, 0x4D, 0x4D, 0x4D, 0x00, 0x4E, 0x4E, 0x4E, 0x00, 0x4F, 0x4F, 0x4F, 0x00, 0x50, 0x50, 0x50, 0x00, 0x51, 0x51, 0x51, 0x00, 0x52, 0x52, 0x52, 0x00, 0x53, 0x53, 0x53, 0x00, 0x54, 0x54, 0x54, 0x00, 0x55, 0x55, 0x55, 0x00, 0x56, 0x56, 0x56, 0x00, 0x57, 0x57, 0x57, 0x00, 0x58, 0x58, 0x58, 0x00, 0x59, 0x59, 0x59, 0x00, 0x5A, 0x5A, 0x5A, 0x00, 0x5B, 0x5B, 0x5B, 0x00, 0x5C, 0x5C, 0x5C, 0x00, 0x5D, 0x5D, 0x5D, 0x00, 0x5E, 0x5E, 0x5E, 0x00, 0x5F, 0x5F, 0x5F, 0x00, 0x60, 0x60, 0x60, 0x00, 0x61, 0x61, 0x61, 0x00, 0x62, 0x62, 0x62, 0x00, 0x63, 0x63, 0x63, 0x00, 0x64, 0x64, 0x64, 0x00, 0x65, 0x65, 0x65, 0x00, 0x66, 0x66, 0x66, 0x00, 0x67, 0x67, 0x67, 0x00, 0x68, 0x68, 0x68, 0x00, 0x69, 0x69, 0x69, 0x00, 0x6A, 0x6A, 0x6A, 0x00, 0x6B, 0x6B, 0x6B, 0x00, 0x6C, 0x6C, 0x6C, 0x00, 0x6D, 0x6D, 0x6D, 0x00, 0x6E, 0x6E, 0x6E, 0x00, 0x6F, 0x6F, 0x6F, 0x00, 0x70, 0x70, 0x70, 0x00, 0x71, 0x71, 0x71, 0x00, 0x72, 0x72, 0x72, 0x00, 0x73, 0x73, 0x73, 0x00, 0x74, 0x74, 0x74, 0x00, 0x75, 0x75, 0x75, 0x00, 0x76, 0x76, 0x76, 0x00, 0x77, 0x77, 0x77, 0x00, 0x78, 0x78, 0x78, 0x00, 0x79, 0x79, 0x79, 0x00, 0x7A, 0x7A, 0x7A, 0x00, 0x7B, 0x7B, 0x7B, 0x00, 0x7C, 0x7C, 0x7C, 0x00, 0x7D, 0x7D, 0x7D, 0x00, 0x7E, 0x7E, 0x7E, 0x00, 0x7F, 0x7F, 0x7F, 0x00, 0x80, 0x80, 0x80, 0x00, 0x81, 0x81, 0x81, 0x00, 0x82, 0x82, 0x82, 0x00, 0x83, 0x83, 0x83, 0x00, 0x84, 0x84, 0x84, 0x00, 0x85, 0x85, 0x85, 0x00, 0x86, 0x86, 0x86, 0x00, 0x87, 0x87, 0x87, 0x00, 0x88, 0x88, 0x88, 0x00, 0x89, 0x89, 0x89, 0x00, 0x8A, 0x8A, 0x8A, 0x00, 0x8B, 0x8B, 0x8B, 0x00, 0x8C, 0x8C, 0x8C, 0x00, 0x8D, 0x8D, 0x8D, 0x00, 0x8E, 0x8E, 0x8E, 0x00, 0x8F, 0x8F, 0x8F, 0x00, 0x90, 0x90, 0x90, 0x00, 0x91, 0x91, 0x91, 0x00, 0x92, 0x92, 0x92, 0x00, 0x93, 0x93, 0x93, 0x00, 0x94, 0x94, 0x94, 0x00, 0x95, 0x95, 0x95, 0x00, 0x96, 0x96, 0x96, 0x00, 0x97, 0x97, 0x97, 0x00, 0x98, 0x98, 0x98, 0x00, 0x99, 0x99, 0x99, 0x00, 0x9A, 0x9A, 0x9A, 0x00, 0x9B, 0x9B, 0x9B, 0x00, 0x9C, 0x9C, 0x9C, 0x00, 0x9D, 0x9D, 0x9D, 0x00, 0x9E, 0x9E, 0x9E, 0x00, 0x9F, 0x9F, 0x9F, 0x00, 0xA0, 0xA0, 0xA0, 0x00, 0xA1, 0xA1, 0xA1, 0x00, 0xA2, 0xA2, 0xA2, 0x00, 0xA3, 0xA3, 0xA3, 0x00, 0xA4, 0xA4, 0xA4, 0x00, 0xA5, 0xA5, 0xA5, 0x00, 0xA6, 0xA6, 0xA6, 0x00, 0xA7, 0xA7, 0xA7, 0x00, 0xA8, 0xA8, 0xA8, 0x00, 0xA9, 0xA9, 0xA9, 0x00, 0xAA, 0xAA, 0xAA, 0x00, 0xAB, 0xAB, 0xAB, 0x00, 0xAC, 0xAC, 0xAC, 0x00, 0xAD, 0xAD, 0xAD, 0x00, 0xAE, 0xAE, 0xAE, 0x00, 0xAF, 0xAF, 0xAF, 0x00, 0xB0, 0xB0, 0xB0, 0x00, 0xB1, 0xB1, 0xB1, 0x00, 0xB2, 0xB2, 0xB2, 0x00, 0xB3, 0xB3, 0xB3, 0x00, 0xB4, 0xB4, 0xB4, 0x00, 0xB5, 0xB5, 0xB5, 0x00, 0xB6, 0xB6, 0xB6, 0x00, 0xB7, 0xB7, 0xB7, 0x00, 0xB8, 0xB8, 0xB8, 0x00, 0xB9, 0xB9, 0xB9, 0x00, 0xBA, 0xBA, 0xBA, 0x00, 0xBB, 0xBB, 0xBB, 0x00, 0xBC, 0xBC, 0xBC, 0x00, 0xBD, 0xBD, 0xBD, 0x00, 0xBE, 0xBE, 0xBE, 0x00, 0xBF, 0xBF, 0xBF, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0xC1, 0xC1, 0xC1, 0x00, 0xC2, 0xC2, 0xC2, 0x00, 0xC3, 0xC3, 0xC3, 0x00, 0xC4, 0xC4, 0xC4, 0x00, 0xC5, 0xC5, 0xC5, 0x00, 0xC6, 0xC6, 0xC6, 0x00, 0xC7, 0xC7, 0xC7, 0x00, 0xC8, 0xC8, 0xC8, 0x00, 0xC9, 0xC9, 0xC9, 0x00, 0xCA, 0xCA, 0xCA, 0x00, 0xCB, 0xCB, 0xCB, 0x00, 0xCC, 0xCC, 0xCC, 0x00, 0xCD, 0xCD, 0xCD, 0x00, 0xCE, 0xCE, 0xCE, 0x00, 0xCF, 0xCF, 0xCF, 0x00, 0xD0, 0xD0, 0xD0, 0x00, 0xD1, 0xD1, 0xD1, 0x00, 0xD2, 0xD2, 0xD2, 0x00, 0xD3, 0xD3, 0xD3, 0x00, 0xD4, 0xD4, 0xD4, 0x00, 0xD5, 0xD5, 0xD5, 0x00, 0xD6, 0xD6, 0xD6, 0x00, 0xD7, 0xD7, 0xD7, 0x00, 0xD8, 0xD8, 0xD8, 0x00, 0xD9, 0xD9, 0xD9, 0x00, 0xDA, 0xDA, 0xDA, 0x00, 0xDB, 0xDB, 0xDB, 0x00, 0xDC, 0xDC, 0xDC, 0x00, 0xDD, 0xDD, 0xDD, 0x00, 0xDE, 0xDE, 0xDE, 0x00, 0xDF, 0xDF, 0xDF, 0x00, 0xE0, 0xE0, 0xE0, 0x00, 0xE1, 0xE1, 0xE1, 0x00, 0xE2, 0xE2, 0xE2, 0x00, 0xE3, 0xE3, 0xE3, 0x00, 0xE4, 0xE4, 0xE4, 0x00, 0xE5, 0xE5, 0xE5, 0x00, 0xE6, 0xE6, 0xE6, 0x00, 0xE7, 0xE7, 0xE7, 0x00, 0xE8, 0xE8, 0xE8, 0x00, 0xE9, 0xE9, 0xE9, 0x00, 0xEA, 0xEA, 0xEA, 0x00, 0xEB, 0xEB, 0xEB, 0x00, 0xEC, 0xEC, 0xEC, 0x00, 0xED, 0xED, 0xED, 0x00, 0xEE, 0xEE, 0xEE, 0x00, 0xEF, 0xEF, 0xEF, 0x00, 0xF0, 0xF0, 0xF0, 0x00, 0xF1, 0xF1, 0xF1, 0x00, 0xF2, 0xF2, 0xF2, 0x00, 0xF3, 0xF3, 0xF3, 0x00, 0xF4, 0xF4, 0xF4, 0x00, 0xF5, 0xF5, 0xF5, 0x00, 0xF6, 0xF6, 0xF6, 0x00, 0xF7, 0xF7, 0xF7, 0x00, 0xF8, 0xF8, 0xF8, 0x00, 0xF9, 0xF9, 0xF9, 0x00, 0xFA, 0xFA, 0xFA, 0x00, 0xFB, 0xFB, 0xFB, 0x00, 0xFC, 0xFC, 0xFC, 0x00, 0xFD, 0xFD, 0xFD, 0x00, 0xFE, 0xFE, 0xFE, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x3B, 0x36, 0x30, 0x2E, 0x2C, 0x2A, 0x29, 0x25, 0x22, 0x28, 0x32, 0x34, 0x34, 0x33, 0x35, 0x38, 0x37, 0x36};


/*
 * DOESENT WORK IF WIDTH OR HEIGHT ARE SMALLER THAN 80
 */
void createBMP(char * path, int width, int height, int bpp) {
    if(width<80||height<80)
        exit(-1);

    int data_size = width*height*(bpp/8);
    int file_size=0;

    switch(bpp){
        case 8:
            file_size = data_size + GREY_BMP_OFFSET_NUMBER;
            break;
        case 24:
            file_size = data_size + COLOR_BMP_OFFSET_NUMBER;
            break;
        default:
            exit(EXIT_FAILURE);
    }


    FILE *f = fopen(path, "a+");
    if(f==NULL){
        perror("fopen error, check that the directory exists.");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<file_size;i++){
        fwrite("\0",1,1,f);
    }

    fclose(f);

    BMP_Image *img = calloc(1, sizeof(BMP_Image));

    img->file_size = file_size;

    switch(bpp){
        case 8:
            img->offset = GREY_BMP_OFFSET_NUMBER;
            break;
        case 24:
            img->offset = COLOR_BMP_OFFSET_NUMBER;
            break;
        default:
            exit(EXIT_FAILURE);
    }

    img->width = width;
    img->height = height;
    img->bpp = bpp;
    img->data_size = data_size;
    img->data = calloc(1,data_size);

    writeBMP(img,path);
    destroyBMP(img);
}

void destroyBMP(BMP_Image * bmp){
    free(bmp->data);
    bmp->data=NULL;
    free(bmp);
}

int writeBMP(BMP_Image * img, char * path){
    FILE * f = fopen(path,"r+");

    if(f==NULL){
        perror("Error");
        return -1;
    }

    if(fwrite("BM",1,2,f)!=2){
        perror("Error");
        return -1;
    }

    int b = 1;
    fseek(f,BMP_COLOR_PLANES_POSITION,SEEK_SET);
    if(fwrite(&b,2,1,f)!=1){
        perror("Error");
        return -1;
    }

    int a = 40;
    fseek(f,BMP_HEADER_SIZE_POSITION,SEEK_SET);
    if(fwrite(&a,4,1,f)!=1){
        perror("Error");
        return -1;
    }

    fseek(f,BMP_SIZE_POSITION,SEEK_SET);
    if(fwrite(&(img->file_size),4,1,f)!=1){
        perror("Error");
        return -1;
    }

    fseek(f,BMP_WIDTH_POSITION,SEEK_SET);
    if(fwrite(&(img->width),4,1,f)!=1){
        perror("Error");
        return -1;
    }

    fseek(f,BMP_HEIGHT_POSITION,SEEK_SET);
    if(fwrite(&(img->height),4,1,f)!=1){
        perror("Error");
        return -1;
    }

    fseek(f,BMP_BPP_POSITION,SEEK_SET);
    if(fwrite(&(img->bpp),2,1,f)!=1){
        perror("Error");
        return -1;
    }

    fseek(f,BMP_OFFSET_POSITION,SEEK_SET);
    if(fwrite(&(img->offset),4,1,f)!=1){
        perror("Error");
        return -1;
    }

    fseek(f,BMP_METADATA_POSITION,SEEK_SET);
    if(fwrite(&(img->shadow),1,1,f)!=1){
        perror("Error");
        return -1;
    }

    fseek(f,img->offset,SEEK_SET);
    if(fwrite(img->data,(size_t)img->data_size,1,f)!=1){
        perror("Error");
        return -1;
    }

    if(img->bpp == 8){
        fseek(f,BMP_HEADERS_END,SEEK_SET);
        if(fwrite(color_table,1024,1,f)!=1){
            perror("Error");
            return -1;
        }
    }

    fclose(f);

    return 0;
}

BMP_Image * readBMP(char * path){
    FILE * f = fopen(path,"r");
    BMP_Image * img = calloc(1, sizeof(BMP_Image));

    if(f==NULL){
        perror("Can't open file");
        return NULL;
    }

    char header_type[3]={0};
    if(fread(header_type,1,2,f)!=2){
        perror("Error");
        return NULL;
    }

    if(strcmp(header_type,"BM")){
        printf("INCOMPATIBLE BITMAP FORMAT, EXPECTED BM HEADER, FOUND '%s', HEADER\n",header_type);
        return NULL;
    }

    fseek(f,BMP_WIDTH_POSITION,SEEK_SET);
    if(fread(&(img->width),4,1,f)!=1){
        perror("Error");
        return NULL;
    }

    fseek(f,BMP_HEIGHT_POSITION,SEEK_SET);
    if(fread(&(img->height),4,1,f)!=1){
        perror("Error");
        return NULL;
    }

    fseek(f,BMP_BPP_POSITION,SEEK_SET);
    if(fread(&(img->bpp),2,1,f)!=1){
        perror("Error");
        return NULL;
    }

    fseek(f,BMP_METADATA_POSITION,SEEK_SET);
    if(fread(&(img->shadow),1,1,f)!=1){
        perror("Error");
        return NULL;
    }

    fseek(f,BMP_SIZE_POSITION,SEEK_SET);
    if(fread(&(img->file_size),4,1,f)!=1){
        perror("Error");
        return NULL;
    }

    fseek(f,BMP_OFFSET_POSITION,SEEK_SET);
    if(fread(&(img->offset),4,1,f)!=1){
        perror("Error");
        return NULL;
    }

    img->data_size = img->file_size - img->offset;
    img->data = calloc(1, img->data_size);
    fseek(f,img->offset,SEEK_SET);
    if(fread(img->data,img->data_size,1,f)!=1){
        perror("Error");
        return NULL;
    }

    fclose(f);

    return img;
}

Matrix* image_to_matrix_conversion(BMP_Image* image) {
    Matrix* m = constructor(image->height, image->width);
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            m->numbers[j][i] = image->data[i + j];
        }
    }
    return m;
}

void createImageFromMatrices(Matrix ** m, char * path, int amount, int width, int height){
    BitArray * aux1;
    BitArray * aux2;
    BitArray * ans;

    ans = build_bit_array_from_matrix(m[0]);

    for(int i=1;i<amount;i++){
        aux1 = build_bit_array_from_matrix(m[i]);
        aux2 = ans;
        ans = concatenate_bit_array(aux2, aux1);
        free(aux1);
        free(aux2);
    }

    createBMP(path, width, height, 8);
    BMP_Image * bmp = readBMP(path);
    bmp->data = ans->numbers;
    writeBMP(bmp,path);
    free(ans);
}

Matrix ** createMatricesFromImage(char * path, int * amount_p, int n){
    BMP_Image * bmp = readBMP(path);
    *amount_p = (bmp->height*bmp->width)/(n*n);

    Matrix ** matrices = malloc((*amount_p) * sizeof(Matrix*));

    for(int i=0; i < *amount_p ; i++){
        matrices[i] = malloc(n*n * sizeof(double));
        for(int j=0; j < n ; j++){
            for(int k=0; k < n ; k++){
                matrices[i]->numbers[j][k] = bmp->data[i*n*n + j*n + k];
            }
        }
    }

    destroyBMP(bmp);
    return matrices;
}