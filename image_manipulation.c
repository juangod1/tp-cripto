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
    perror("Error: ");
    return NULL;
}

BMP_Image * openBMP(char * path, int bpp){
    FILE * f = fopen(path,"r");

    if(f<0) return error();

    lseek(f,BMP_SIZE_POSITION,SEEK_SET);
    int size;
    if(read(f,&size,4)!=4) return error();

    lseek(f,BMP_OFFSET_POSITION,SEEK_SET);
    int offset;
    if(read(f,&offset,4)) return error();


    BMP_Image * img = calloc(sizeof(BMP_Image),0);
    img->data_size = size - offset;
    img->data = calloc(img->data_size,0);
    lseek(f,offset,SEEK_SET);
    if(read(f,img->data,img->data_size)) return error();

    return img;
}