#ifndef TP_CRIPTO_AZZAHRA_H
#define TP_CRIPTO_AZZAHRA_H

#include "matrices.h"

Matrix * generate_a(int k, Matrix * s);

Matrix * generate_ss(Matrix * a);

Matrix * generate_r(Matrix * s, Matrix *ss);

Matrix ** generate_x_vec(int n, int k);
Matrix * generate_x(int k, int a);
int * generate_c_vec(int n);
Matrix ** generate_v_vec(Matrix ** x_vec, int n, Matrix * a);
Matrix * generate_v(Matrix * x, Matrix * a);
int calculate_g(int t, int i, int j, Matrix * r, int k, const int * c_vec);
Matrix * generate_G(int j, Matrix *r, int * c_vec, int n, int k);
Matrix * generate_rw(Matrix * w, Matrix * ss);
Matrix * generate_sh(Matrix * v, Matrix * G);
Matrix * generate_B(Matrix ** sh_vec, int k);
Matrix * compute_ss(Matrix * B);
Matrix ** compute_G_vec(Matrix ** sh_vec, int k);
Matrix * extract_G_from_sh(Matrix * sh);
Matrix * compute_R_from_G_vec(Matrix ** G_vec, int k, int n, char * shadow_numbers);
Matrix * compute_small_r(Matrix ** G_vec, int x, int y, int k, char * shadow_numbers, int n);
Matrix * compute_s_from_SS_and_R(Matrix * ss, Matrix * r);
Matrix * compute_w_from_SS_and_Rw(Matrix * ss, Matrix * rw);

#endif //TP_CRIPTO_AZZAHRA_H
