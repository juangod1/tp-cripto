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

void * error(){
    perror("Error");
    return NULL;
}

void destroyBMP(BMP_Image * bmp){
    free(bmp->data);
    free(bmp);
}

BMP_Image * openBMP(char * path){
    FILE * f = fopen(path,"r");

    if(f==NULL) return error();

    lseek(f->_file,BMP_SIZE_POSITION,SEEK_SET);
    int size;
    if(read(f->_file,&size,4)!=4) return error();

    lseek(f->_file,BMP_OFFSET_POSITION,SEEK_SET);
    int offset;
    if(read(f->_file,&offset,4)!=4) return error();


    BMP_Image * img = calloc(1, sizeof(BMP_Image));
    img->data_size = size - offset;
    img->data = calloc(1, img->data_size);
    lseek(f->_file,offset,SEEK_SET);
    if(read(f->_file,img->data,img->data_size)!=img->data_size) return error();

    fclose(f);

    return img;
}