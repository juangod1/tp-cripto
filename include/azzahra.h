#ifndef TP_CRIPTO_AZZAHRA_H
#define TP_CRIPTO_AZZAHRA_H

#include "matrices.h"

Matrix * generate_a(int k, int n);

Matrix * generate_ss(Matrix * a);

Matrix * generate_r(Matrix * s, Matrix *ss);

#endif //TP_CRIPTO_AZZAHRA_H
