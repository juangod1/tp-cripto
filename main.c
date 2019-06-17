#include "include/main.h"
#include "include/matrices.h"
#include "tests/main_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int validate_params(char* secret_image_path, char* watermark_image_path, char* directory, int k, int n) {
    int error = 0;
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

// TODO: seguir validando
int main(int argc, char *argv[]){
//    main_test();
    int opt;
    enum { ENCRYPTION, DECRYPTION } mode = ENCRYPTION;
    struct option longopts[] = {
            {"distribute", no_argument, NULL, 'd'},
            {"recover", no_argument, NULL, 'r'},
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

    while ((opt = getopt_long(argc, argv, ":drs:m:k:n:f:", longopts, NULL)) != -1) {
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

    if(validate_params(secret_image_path, watermark_image_path, directory, k, n) == 1)
        exit(EXIT_FAILURE);

    printf("Mode: %s\n", mode == ENCRYPTION ? "Encryption" : "Decryption");
    printf("Secret image: %s\n", secret_image_path);
    printf("Watermark image: %s\n", watermark_image_path);
    printf("K: %d\n", k);
    printf("N: %d\n", n);
    printf("Directory: %s\n", directory);
}