#ifndef TP_CRIPTO_CRYPTO_SERVICE_H
#define TP_CRIPTO_CRYPTO_SERVICE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "matrices.h"
#include "azzahra.h"
#include "image_manipulation.h"
#include "steganography.h"

void encrypt_image(char* secret_image_path, char* watermark_image_path, char** shadows_path, int k, int n);


#endif //TP_CRIPTO_CRYPTO_SERVICE_H
