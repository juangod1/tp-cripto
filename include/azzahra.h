#ifndef TP_CRIPTO_AZZAHRA_H
#define TP_CRIPTO_AZZAHRA_H

#include "matrices.h"

Matrix * generate_a(int k, int n);

Matrix * generate_ss(Matrix * a);

Matrix * generate_r(Matrix * s, Matrix *ss);

Matrix ** generate_x_vec(int n, int k);
Matrix * generate_x(int k);
int * generate_c_vec(int n);
Matrix * generate_v_vec(Matrix ** x_vec, int n, Matrix * a);
Matrix * generate_v(Matrix * x, Matrix * a);
int calculate_g(int t, int i, int j, Matrix * r, int k, int * c_vec);
Matrix * generate_G(int j, Matrix *r, int * c_vec, int n, int k);
Matrix * generate_rw(Matrix * w, Matrix * ss);
Matrix * generate_sh(Matrix * v, Matrix * G);

#endif //TP_CRIPTO_AZZAHRA_H
