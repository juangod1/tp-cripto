#include "include/azzahra.h"
#include "include/random.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define CONST_P 251

Matrix * generate_a(int k, Matrix * s)
{
    Matrix * m = constructor(s->rows,k);
    Matrix * aux;


//    int count = 0;
    do {

        char random = my_mod(nextChar(), 240);

        for(int i=0; i < k; i++) {
            Matrix* vector = generate_x(s->rows, i);

            for (int j = 0; j < m->rows; ++j) {
                m->numbers[i][j] = vector->numbers[0][j];
            }

            destroy_matrix(vector);
        }

        aux = multiply(transpose(m), m);
        if(my_mod(my_determinant(aux), CONST_P)== 0)
            print(m);
//        count++;
    } while (my_mod(my_determinant(aux), CONST_P) == 0);

//    if(count > 1)
        print(m);
    
    return m;
}


Matrix * generate_ss(Matrix * a)
{
    Matrix * a_trans = transpose(a);
    Matrix * prod_0 = multiply(a_trans,a);
    apply_modulus(prod_0,CONST_P);
    Matrix * prod_0_inv = inversion_mod(prod_0,CONST_P);
    Matrix * prod_1 = multiply(a,prod_0_inv);
    apply_modulus(prod_1,CONST_P);
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
        ret[i] = generate_x(k,i+1);
    }
    return ret;
}

Matrix * generate_x(int k, int a)
{
    Matrix * x = constructor(k,1);
    for(int i=0;i<k;i++)
    {
        int num = my_mod(pow(a,i),CONST_P);
        x->numbers[0][i]=num;
    }
    return x;
}
int * generate_c_vec(int n)
{
    int * ret = malloc(n* sizeof(int));
    for(int i=0; i<n;i++)
    {
        ret[i] = i+1;
    }
    return ret;
}

Matrix ** generate_v_vec(Matrix ** x_vec, int n, Matrix * a)
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
    int rows = r->rows;
    int cols = r->columns/k;
    if(rows%k!=0)
    {
        printf("WARNING: M is not divisible by K. Something bad may happen\n");
    }
    Matrix * G = constructor(rows, cols);
    for(int row_c=0; row_c<rows;row_c++)
    {
        for(int col_c=0; col_c<cols; col_c++)
        {
            G->numbers[col_c][row_c] = calculate_g(col_c+1,row_c+1,j,r,k,c_vec);
        }
    }
    return G;
}


int calculate_g(int t, int i, int j, Matrix * r, int k, const int * c_vec)
{
    i-=1;
    t-=1;
    j-=1;
    int ret = 0;
    for( int counter=0; counter<k; counter++)
    {
        int column_index = t*k + counter;
        int num = (int)r->numbers[column_index][i];
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

Matrix * generate_sh(Matrix * v, Matrix * G)
{
    if(v->rows!=G->rows) return NULL;

    Matrix * sh = constructor(v->rows,v->columns+G->columns);
    for(int i=0; i<v->rows;i++)
    {
        for(int j=0; j<v->columns;j++)
        {
            sh->numbers[j][i]=v->numbers[j][i];
        }
    }
    for(int i=0; i<v->rows;i++)
    {
        for(int j=0; j<G->columns;j++)
        {
            int column_index = j+v->columns;
            sh->numbers[column_index][i]=G->numbers[j][i];
        }
    }
    return sh;
}

Matrix * generate_B(Matrix ** sh_vec, int k)
{
    int rows = sh_vec[0]->rows;
    Matrix * B = constructor(rows,k);
    for(int i=0;i<rows;i++)
    {
        for(int j=0; j<k;j++)
        {
            Matrix * sh = sh_vec[j];
            B->numbers[j][i] = sh->numbers[0][i];
        }
    }

    if(my_mod(my_determinant(B), CONST_P) == 0)
        printf("El det es 0000");
    return B;
}

Matrix * compute_ss(Matrix * B)
{
    Matrix * B_trans = transpose(B);
    Matrix * prod_0 = multiply(B_trans,B);
    apply_modulus(prod_0,CONST_P);
    Matrix * prod_0_inv = inversion_mod(prod_0,CONST_P);
    Matrix * prod_1 = multiply(B,prod_0_inv);
    apply_modulus(prod_1,CONST_P);
    Matrix * ret = multiply(prod_1,B_trans);

    apply_modulus(ret,CONST_P);

    destroy_matrix(prod_1);
    destroy_matrix(prod_0_inv);
    destroy_matrix(prod_0);
    destroy_matrix(B_trans);

    return ret;
}

Matrix ** compute_G_vec(Matrix ** sh_vec, int k)
{
    Matrix ** G_vec = malloc(k*sizeof(Matrix *));
    for(int i=0; i<k;i++)
    {
        Matrix * sh = sh_vec[i];
        G_vec[i]=extract_G_from_sh(sh);
    }
    return G_vec;
}

Matrix * extract_G_from_sh(Matrix * sh)
{
    Matrix * G = constructor(sh->rows,sh->columns-1);

    for(int i=0; i<G->rows;i++)
    {
        for(int j=0; j<G->columns; j++)
        {
            G->numbers[j][i]=sh->numbers[j+1][i];
        }
    }
    return G;
}

Matrix * compute_R_from_G_vec(Matrix ** G_vec, int k, int n)
{
    int rows = G_vec[0]->rows;
    int columns = rows/k;
    if(rows%k!=0)
    {
        printf("WARNING: M is not divisible by K. Something bad may happen\n");
    }

    Matrix * ret = constructor(rows,k*columns);

    for(int x=0; x<rows;x++)
    {
        for(int y=0; y<columns; y++)
        {
            Matrix * small_r = compute_small_r(G_vec,x,y, k);
            for(int i=0; i<k;i++)
            {
                int column_index = i+(k*y);
                int row_index = x;
                ret->numbers[column_index][row_index] = small_r->numbers[i][0];
            }
            destroy_matrix(small_r);
        }
    }
    apply_modulus(ret,CONST_P);
    return ret;
}

Matrix * compute_small_r(Matrix ** G_vec, int x, int y, int k)
{
    Matrix * aux = constructor(k,3); //TODO: a chequear el tamaño de small_r para distintos k
    int * c_vec = generate_c_vec(k);

    for(int i=0; i<aux->rows;i++)
    {
        aux->numbers[0][i]=1;
        aux->numbers[1][i]=c_vec[i];
        aux->numbers[2][i]=G_vec[i]->numbers[y][x];
    }
    free(c_vec);

    solve_linear_equations(aux);

    Matrix * ret = constructor(1,k);
    for(int i=0; i<k;i++)
    {
        ret->numbers[i][0]=aux->numbers[2][i];
    }
    destroy_matrix(aux);
    return ret;
}

Matrix * compute_s_from_SS_and_R(Matrix * ss, Matrix * r)
{
    Matrix * ret = clonemx(ss);
    add(ret,r);
    apply_modulus(ret,CONST_P);

    return ret;
}

Matrix * compute_w_from_SS_and_Rw(Matrix * ss, Matrix * rw)
{
    Matrix * ret = clonemx(ss);
    add(ret,rw);
    apply_modulus(ret,CONST_P);

    return ret;
}