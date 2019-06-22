#include "include/main.h"
#include "include/matrices.h"
#include "include/crypto_service.h"
#include "tests/main_test.h"
#include "include/random.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <time.h>

#define MAX_FILE_LENGTH 1024

int validate_params(int mode, char* secret_image_path, char* watermark_image_path, char* directory, int k, int n) {
    int error = 0;

    if(mode==-1) {
        fprintf(stderr, "Must set mode (-d or -r).\n");
        error = 1;
    }

    if(!strcmp(secret_image_path,"")) {
        fprintf(stderr, "Must set secret image path (-s).\n");
        error = 1;
    }

    if(!strcmp(watermark_image_path,"")) {
        fprintf(stderr, "Must set watermark image path (-m).\n");
        error = 1;
    }

    if(!strcmp(directory,"")) {
        fprintf(stderr, "Must set directory path (--dir).\n");
        error = 1;
    }

    if(k != 2 && k != 4) {
        fprintf(stderr, "K must be 2 or 4.\n");
        error = 1;
    }

    if(n != 4 && n != 8) {
        fprintf(stderr, "N must be 4 or 8.\n");
        error = 1;
    }

    if((k == 2 && n != 4) || (k == 4 && n != 8)) {
        fprintf(stderr, "Allowed schemes are (2,4) and (4,8) only.\n");
        error = 1;
    }

    return error;
}

int main(int argc, char *argv[]){
    int opt;
    enum Mode mode = -1;
    struct option longopts[] = {
            {"distribute", no_argument, NULL, 'd'},
            {"recover", no_argument, NULL, 'r'},
            {"test", no_argument, NULL, 't'},
            {"secret_image", required_argument, NULL, 's'},
            {"watermark_image", required_argument, NULL, 'm'},
            {"k", required_argument, NULL, 'k'},
            {"n", required_argument, NULL, 'n'},
            {"dir", required_argument, NULL, 'f'},
    };

    char* secret_image_path = "";
    char* watermark_image_path = "";
    char* directory = "";
    int k = 0, n = 0;

    while ((opt = getopt_long(argc, argv, ":drts:m:k:n:f:", longopts, NULL)) != -1) {
        switch (opt) {
            case 'd':
                mode = ENCRYPTION;
                break;
            case 'r':
                mode = DECRYPTION;
                break;
            case 's':
                secret_image_path = optarg;
                break;
            case 'm':
                watermark_image_path = optarg;
                break;
            case 'k':
                k = atoi(optarg);
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case 'f':
                directory = optarg;
                break;
            case 't':
                main_test();
                return EXIT_SUCCESS;
            case ':':
                /* missing option argument */

                fprintf(stderr, "%s: option '-%c' requires an argument\n",
                        argv[0], optopt);
                exit(EXIT_FAILURE);
            case '?':
            default:
                /* invalid option */

                fprintf(stderr, "%s: option '-%c' is invalid: ignored\n",
                        argv[0], optopt);
                exit(EXIT_FAILURE);
        }
    }

    if(validate_params(mode, secret_image_path, watermark_image_path, directory, k, n) == 1)
        exit(EXIT_FAILURE);

    run_service(mode, secret_image_path, watermark_image_path, k, n, directory);
    return EXIT_SUCCESS;
}

char ** getShadowsFromPath(const char * directory, int shadow_amount)
{
    size_t dir_length = strlen(directory);
    char ** arr = malloc(shadow_amount * sizeof(char *));
    int finishes_in_dash = directory[dir_length-1]=='/';

    for(int i = 0; i < shadow_amount; i++) {
        arr[i] = calloc(1, MAX_FILE_LENGTH);
        memccpy(arr[i], directory, 1, dir_length);
        if(!finishes_in_dash)
            *(arr[i]+dir_length)='/';
    }

    if(!finishes_in_dash)
        dir_length++;

    DIR* dirFile = opendir(directory);
    int count = 0;
    int bmp_counter = 0;
    if (dirFile){
        struct dirent* hFile;
        while((hFile = readdir(dirFile)) != NULL){

            if (!strcmp( hFile->d_name, "."))
                continue;
            if (!strcmp( hFile->d_name, ".."))
                continue;
            if (hFile->d_name[0] == '.')
                continue;
            if (strstr(hFile->d_name, ".bmp")) {
                bmp_counter++;
                if(bmp_counter > shadow_amount) {
                    fprintf(stderr, "Incorrect shadow amount. Must be %d.", shadow_amount);
                    exit(EXIT_FAILURE);
                }

                memcpy(arr[count++] + dir_length, hFile->d_name, MAX_FILE_LENGTH - dir_length);
            }
        }
        closedir(dirFile);

        if(bmp_counter != shadow_amount) {
            fprintf(stderr, "Incorrect shadow amount. Must be %d.", shadow_amount);
            exit(EXIT_FAILURE);
        }
    }
    return arr;
}

int check_image_formats(enum Mode mode, char * secret_img_path, char * watermark_img_path, char** shadows_path, int shadow_amount, int n) {
    BMP_Image* watermark_image = readBMP(watermark_img_path);
    int has_errors = 0;

    if(mode == ENCRYPTION) {
        BMP_Image* secret_image = readBMP(secret_img_path);

        if (secret_image->bpp != 8) {
            printf("Secret image has '%d' bpp. Must be 8 bpp.\n", secret_image->bpp);
            has_errors = 1;
        }

        int pixel_amount = secret_image->height * secret_image->width;

        if (pixel_amount % (n * n) != 0) {
            fprintf(stderr, "Secret image has '%d' PIXELS. Not divisible by n*n.\n", pixel_amount);
            has_errors = 1;
        }

        if(secret_image->width != watermark_image->width || secret_image->height != watermark_image->height) {
            fprintf(stderr, "Secret image must be same size as watermark image.\n");
            has_errors = 1;
        }

        destroyBMP(secret_image);
    }

    for (int i = 0; i < shadow_amount; ++i) {
        BMP_Image* shadow = readBMP(shadows_path[i]);

        if(shadow->bpp != 24) {
            fprintf(stderr, "Secret image has '%d' bpp. Must be 24.\n", shadow->bpp);
            has_errors = 1;
        }

        if(shadow->height != watermark_image->height || shadow->width != watermark_image->width) {
            fprintf(stderr, "Shadow image must be same size as secret and watermark image.\n");
            has_errors = 1;
        }

        destroyBMP(shadow);
    }

    destroyBMP(watermark_image);

    return has_errors;
}

void run_service(enum Mode mode, char * secret_img_path, char * watermark_img_path, int k, int n, char * directory){
    srand((unsigned int)time(0));
    setSeed(rand());
    int shadow_amount = mode == ENCRYPTION ? n : k;
    char ** arr = getShadowsFromPath(directory, shadow_amount);
    int has_errors = check_image_formats(mode, secret_img_path, watermark_img_path, arr, shadow_amount, n);

    if(has_errors)
        exit(EXIT_FAILURE);

    printf("Mode: %s\n", mode == ENCRYPTION ? "Encryption" : "Decryption");
    printf("Secret image: %s\n", secret_img_path);
    printf("Watermark image: %s\n", watermark_img_path);
    printf("K: %d\n", k);
    printf("N: %d\n", n);
    printf("Directory: %s\n", directory);

    switch(mode){
        case 0:
            encrypt_loop(secret_img_path, watermark_img_path,arr,k,n);
            break;
        case 1:
            decrypt_loop(k,n,arr,watermark_img_path,secret_img_path);
            break;
        default:
            exit(EXIT_FAILURE);
    }

    for(int i=0;i<shadow_amount;i++) free(arr[i]);
    free(arr);
}