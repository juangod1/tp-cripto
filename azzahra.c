#include "include/azzahra.h"
#include <stdlib.h>

Matrix * generate_a(int k, int n)
{
    Matrix * m = rand_matrix_mod(n,k,256);
    return m;
}


Matrix * generate_ss(Matrix * a)
{
    print(a);
    Matrix * a_trans = transpose(a);
    Matrix * prod_0 = multiply(a_trans,a);
    Matrix * prod_0_inv = inversion_mod(prod_0,251);
    Matrix * prod_1 = multiply(a,prod_0_inv);
    Matrix * ret = multiply(prod_1,a_trans);

    apply_modulus(ret,251);

    destroy_matrix(prod_1);
    destroy_matrix(prod_0_inv);
    destroy_matrix(prod_0);
    destroy_matrix(a_trans);

    return ret;
}

Matrix * generate_r(Matrix * s, Matrix *ss)
{
    Matrix * r = clonemx(s);
    subtract(r,ss);
    apply_modulus(r,251);
    return r;
}

Matrix ** generate_x_vec(int n, int k)
{
    Matrix ** ret = malloc(n* sizeof(Matrix *));
    for(int i=0; i<n;i++)
    {
        ret[i] = generate_x(k);
    }
    return ret;
}

Matrix * generate_x(int k)
{
    Matrix * x = constructor(k,1);
    for(int i=0; i<k; i++)
    {
        x->numbers[1][i] = rand()%251;
    }
    return x;
}
int * generate_c_vec(int n)
{
    int * ret = malloc(n* sizeof(int));
    for(int i=0; i<n;i++)
    {
        ret[i] = i;
    }
    return ret;
}

Matrix * generate_v_vec(Matrix ** x_vec, int n, Matrix * a)
{
    Matrix ** ret = malloc(n* sizeof(Matrix *));
    for(int i=0; i<n;i++)
    {
        ret[i] = generate_v(x_vec[i],a);
    }
    return ret;
}

Matrix * generate_v(Matrix * x, Matrix * a)
{
    Matrix * ret = multiply(a,x);
    apply_modulus(ret, 251);
    return ret;
}