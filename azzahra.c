#include "include/azzahra.h"

Matrix * generate_a(int k, int n)
{
    Matrix * m = rand_matrix_mod(n,k,256);
    return m;
}


Matrix * generate_ss(Matrix * a)
{
    Matrix * a_trans = transpose(a);
    Matrix * prod_0 = multiply(a_trans,a);
    Matrix * prod_0_inv = inversion_mod(prod_0,251);
    Matrix * prod_1 = multiply(a,prod_0_inv);
    Matrix * ret = multiply(prod_1,a_trans);

    apply_modulus(ret,256);

    destroy_matrix(prod_1);
    destroy_matrix(prod_0_inv);
    destroy_matrix(prod_0);
    destroy_matrix(a_trans);

    return ret;
}