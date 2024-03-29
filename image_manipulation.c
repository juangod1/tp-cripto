#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include "include/image_manipulation.h"
#include "include/matrices.h"

#define DEFAULT_BMP_OFFSET_NUMBER 54

/*
 * DOESENT WORK IF WIDTH OR HEIGHT ARE SMALLER THAN 80
 */
void createBMP(char * path, int width, int height, int bpp) {
    if(width<80||height<80)
        exit(-1);

    int data_size = width*height*(bpp/8);
    int file_size = data_size + DEFAULT_BMP_OFFSET_NUMBER;

    FILE *f = fopen(path, "a+");

    for(int i=0;i<file_size;i++){
        fwrite("\0",1,1,f);
    }

    fclose(f);

    BMP_Image *img = calloc(1, sizeof(BMP_Image));

    img->file_size = file_size;
    img->offset = DEFAULT_BMP_OFFSET_NUMBER;
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
            m->numbers[i][j] = image->data[i + j];
        }
    }
    return m;
}