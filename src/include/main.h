//
// Created by Juan Godfrid on 2019-06-01.
//

#ifndef TP_CRIPTO_MAIN_H
#define TP_CRIPTO_MAIN_H

enum Mode { ENCRYPTION, DECRYPTION };

void run_service(enum Mode mode, char * secret_img_path, char * watermark_img_path, int k, int n, char * directory);
char ** getShadowsFromPath(const char * directory, enum Mode mode, int k, int n);

#endif //TP_CRIPTO_MAIN_H
