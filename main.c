#include "include/main.h"
#include "include/matrices.h"
#include "include/crypto_service.h"
#include "tests/main_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int validate_params(int mode, char* secret_image_path, char* watermark_image_path, char* directory, int k, int n) {
    int error = 0;

    if(mode==-1) {
        printf("Must set mode (-d or -r).\n");
        error = 1;
    }

    if(!strcmp(secret_image_path,"")) {
        printf("Must set secret image path (-s).\n");
        error = 1;
    }

    if(!strcmp(watermark_image_path,"")) {
        printf("Must set watermark image path (-m).\n");
        error = 1;
    }

    if(!strcmp(directory,"")) {
        printf("Must set directory path (--dir).\n");
        error = 1;
    }

    if(k != 2 && k != 4) {
        printf("K must be 2 or 4.\n");
        error = 1;
    }

    if(n != 4 && n != 8) {
        printf("N must be 4 or 8.\n");
        error = 1;
    }

    if((k == 2 && n != 4) || (k == 4 && n != 8)) {
        printf("Allowed schemes are (2,4) and (4,8) only.\n");
        error = 1;
    }

    return error;
}

int main(int argc, char *argv[]){
    int opt;
    enum { ENCRYPTION, DECRYPTION } mode = -1;
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

    printf("Mode: %s\n", mode == ENCRYPTION ? "Encryption" : "Decryption");
    printf("Secret image: %s\n", secret_image_path);
    printf("Watermark image: %s\n", watermark_image_path);
    printf("K: %d\n", k);
    printf("N: %d\n", n);
    printf("Directory: %s\n", directory);

    run_service(mode, secret_image_path, watermark_image_path, k, n, directory);
    return EXIT_SUCCESS;
}

void run_service(int mode, char * secret_img_path, char * watermark_img_path, int k, int n, char * directory){
    char ** arr = malloc(8*sizeof(char *));
    arr[0] = "image/shard1.bmp";
    arr[1] = "image/shard2.bmp";
    arr[2] = "image/shard3.bmp";
    arr[3] = "image/shard4.bmp";
    arr[4] = "image/shard5.bmp";
    arr[5] = "image/shard6.bmp";
    arr[6] = "image/shard7.bmp";
    arr[7] = "image/shard8.bmp";

    switch(mode){
        case 0:
            encrypt_image(secret_img_path, watermark_img_path,arr,k,n);
            break;
        case 1:
            decrypt_image(k,n,arr,watermark_img_path,secret_img_path);
            break;
    }

    free(arr);
}