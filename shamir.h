#ifndef TP_CRIPTO_SHAMIR_H
#define TP_CRIPTO_SHAMIR_H

int** generate_a(int k, int n);

int** generate_double_s(int** a);

int** generate_r(int** s, int** double_s);

int check_elements_greater_251(int** matrix);

int** generate_x_array(int k, int n);

int* generate_c_array(int n);

int** generate_v_array(int** a, int** x_array);

int*** generate_g_array(int** r, int k, int n, int* c_array);

int*** generate_sh_array(int** v_array, int*** g_array);

int** generate_rw(int** w, int** double_s);

#endif //TP_CRIPTO_SHAMIR_H
