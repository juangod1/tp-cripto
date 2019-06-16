#include "include/azzahra.h"
#include <stdlib.h>

#define CONST_P 251

Matrix * generate_a(int k, int n)
{
    Matrix * m = rand_matrix_mod(n,k,CONST_P);
    return m;
}


Matrix * generate_ss(Matrix * a)
{
    print(a);
    Matrix * a_trans = transpose(a);
    Matrix * prod_0 = multiply(a_trans,a);
    Matrix * prod_0_inv = inversion_mod(prod_0,CONST_P);
    Matrix * prod_1 = multiply(a,prod_0_inv);
    Matrix * ret = multiply(prod_1,a_trans);

    apply_modulus(ret,CONST_P);

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
    apply_modulus(r,CONST_P);
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
        x->numbers[1][i] = rand()%CONST_P;
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
    apply_modulus(ret, CONST_P);
    return ret;
}

Matrix * generate_G(int j, Matrix *r, int * c_vec, int n, int k)
{
    Matrix * G = constructor(n, k);
    for(int row_c=0; row_c<n;row_c++)
    {
        for(int col_c=0; col_c<k; col_c++)
        {
            G->numbers[col_c][row_c] = calculate_g(col_c+1,row_c+1,j,r,k,c_vec);
        }
    }
    return G;
}


int calculate_g(int t, int i, int j, Matrix * r, int k, int * c_vec)
{
    i-=1;
    t-=1;
    j-=1;
    int ret = 0;
    for( int counter=0; counter<k; counter++)
    {
        int column_index = t*k+counter;
        int num = r->numbers[column_index][i];
        if(counter!=0)
        {
            num*= c_vec[j];
        }
        ret+=num;
    }
    return my_mod(ret,CONST_P);
}

Matrix * generate_rw(Matrix * w, Matrix * ss)
{
    Matrix * rw = clonemx(w);
    subtract(rw,ss);
    apply_modulus(rw,CONST_P);
    return rw;
}