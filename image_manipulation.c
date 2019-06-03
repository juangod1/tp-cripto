//
// Created by Juan Godfrid on 2019-06-01.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "include/image_manipulation.h"

void destroyBMP(BMP_Image * bmp){
    free(bmp->data);
    free(bmp);
}

int writeBMP(BMP_Image * img, char * path){
    FILE * f = fopen(path,"r+");

    if(f==NULL){
        perror("Error");
        return -1;
    }

    fseek(f,BMP_METADATA_POSITION,SEEK_SET);
    if(fwrite(&(img->shadow),1,1,f)!=1){
        perror("Error");
        return -1;
    }

    fseek(f,img->offset,SEEK_SET);
    if(fwrite(img->data,img->data_size,1,f)!=1){
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
        perror("Error");
        return NULL;
    }

    char header_type[2]={};
    if(fread(header_type,1,2,f)!=2){
        perror("Error");
        return NULL;
    }

    if(strcmp(header_type,"BM")){
        printf("INCOMPATIBLE BITMAP FORMAT, EXPECTED BM HEADER\n");
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