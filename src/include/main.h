//
// Created by Juan Godfrid on 2019-06-01.
//

#ifndef TP_CRIPTO_MAIN_H
#define TP_CRIPTO_MAIN_H

void run_service(int mode, char * secret_img_path, char * watermark_img_path, int k, int n, char * directory);
char ** getShadowsFromPath(const char * directory);

#endif //TP_CRIPTO_MAIN_H
