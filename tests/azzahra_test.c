#include "azzahra_test.h"
#include "../include/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Matrix * matrix_ss = NULL;
Matrix * correct_ss = NULL;
Matrix * matrix_a = NULL;
Matrix * matrix_r = NULL;
Matrix * correct_r = NULL;
Matrix * matrix_s = NULL;
int n;
int k;

Matrix ** x_vec = NULL;
Matrix ** correct_v_vec = NULL;
Matrix ** v_vec = NULL;

int t;
int i;
int j;
int * c_vec;

int g;
int correct_g;

Matrix * matrix_G;
Matrix * correct_G;

Matrix * matrix_w;
Matrix * correct_rw;
Matrix * matrix_rw;

void test_generate_a()
{
    given_n();
    given_k();
    when_generating_a();
    assert_not_equal_memory("A is not null",matrix_a,NULL);
    assert_true("A values < 255", then_a_less_than_255());

    destroy_matrix(matrix_a);
}

void test_generate_ss()
{
    given_a();
    given_correct_ss();
    when_generating_ss();
    assert_not_equal_memory("SS is not null", matrix_ss, NULL);
    assert_true("SS values < 255", then_ss_less_than_255());
    printf("matrix_ss\n");
    print(matrix_ss);
    printf("correct_ss\n");
    print(correct_ss);
    assert_true("SS is correct", equals(matrix_ss,correct_ss) == SUCC);

    destroy_matrix(matrix_a);
    destroy_matrix(matrix_ss);
    destroy_matrix(correct_ss);
}

void test_generate_r()
{
    given_ss();
    given_s();
    given_correct_r();

    when_calculating_r();

    printf("correct_r\n");
    print(correct_r);
    printf("matrix_r\n");
    print(matrix_r);

    assert_true("R is correct", equals(matrix_r,correct_r)==SUCC);

    destroy_matrix(matrix_ss);
    destroy_matrix(matrix_s);
    destroy_matrix(matrix_r);
    destroy_matrix(correct_r);
}

void test_generate_v_vec()
{
    given_n();
    given_x_vec();
    given_a();
    given_correct_v_vec();

    when_calculating_v_vec();

    for(int i=0; i<n; i++)
    {
        char * str= malloc(100*sizeof(char));
        sprintf(str,"V[%i] is correct",i);
        printf("v_vec[%i]\n",i);
        print(v_vec[i]);
        printf("correct_v_vec[%i]\n",i);
        print(correct_v_vec[i]);
        assert_true(str, equals(v_vec[i],correct_v_vec[i])==SUCC);
        free(str);
    }
    destroy_matrix_vec(x_vec,n);
    destroy_matrix_vec(v_vec,n);
    destroy_matrix_vec(correct_v_vec,n);
    destroy_matrix(matrix_a);
}

void test_calculate_g()
{
    given_n();
    given_t();
    given_i();
    given_j();
    given_r();
    given_k();
    given_c_vec();
    given_correct_g();

    when_calculating_g();

    assert_equal_int("g is equal to correct_g",correct_g,g);

    destroy_matrix(matrix_r);
    free(c_vec);
}

void test_calculate_G()
{
    given_j();
    given_r();
    given_c_vec();
    given_n();
    given_k();
    given_correct_G();

    when_generating_G();

    printf("matrix_G\n");
    print(matrix_G);
    printf("correct_G\n");
    print(correct_G);

    assert_true("G is equal to correct G", equals(matrix_G, correct_G)==SUCC);

    destroy_matrix(matrix_G);
    destroy_matrix(correct_G);
    destroy_matrix(matrix_r);
    free(c_vec);
}

void test_generate_rw()
{
    given_w();
    given_ss();
    given_correct_rw();

    when_generating_rw();

    printf("matrix_rw\n");
    print(matrix_rw);
    printf("correct_rw\n");
    print(correct_rw);

    assert_true("RW equals correct RW", equals(matrix_rw, correct_rw)==SUCC);

    destroy_matrix(matrix_rw);
    destroy_matrix(correct_rw);
    destroy_matrix(matrix_ss);
    destroy_matrix(matrix_w);
}

void when_generating_rw()
{
    matrix_rw = generate_rw(matrix_w, matrix_ss);
}

void given_w()
{
    matrix_w = constructor(4,4);
    matrix_w->numbers[0][0] =50;
    matrix_w->numbers[1][0] =100;
    matrix_w->numbers[2][0] =21;
    matrix_w->numbers[3][0] =14;

    matrix_w->numbers[0][1] =22;
    matrix_w->numbers[1][1] =76;
    matrix_w->numbers[2][1] =200;
    matrix_w->numbers[3][1] =54;

    matrix_w->numbers[0][2] =1;
    matrix_w->numbers[1][2] =91;
    matrix_w->numbers[2][2] =45;
    matrix_w->numbers[3][2] =7;

    matrix_w->numbers[0][3] =24;
    matrix_w->numbers[1][3] =66;
    matrix_w->numbers[2][3] =96;
    matrix_w->numbers[3][3] =120;
}

void given_correct_rw()
{
    correct_rw = constructor(4,4);
    correct_rw->numbers[0][0] = 49;
    correct_rw->numbers[1][0] = 130;
    correct_rw->numbers[2][0] = 71;
    correct_rw->numbers[3][0] = 51;

    correct_rw->numbers[0][1] = 52;
    correct_rw->numbers[1][1] = 138;
    correct_rw->numbers[2][1] = 14;
    correct_rw->numbers[3][1] = 38;

    correct_rw->numbers[0][2] = 51;
    correct_rw->numbers[1][2] = 156;
    correct_rw->numbers[2][2] = 2;
    correct_rw->numbers[3][2] = 182;

    correct_rw->numbers[0][3] = 61;
    correct_rw->numbers[1][3] = 50;
    correct_rw->numbers[2][3] = 20;
    correct_rw->numbers[3][3] = 100;
}


void given_correct_G()
{
    correct_G = constructor(n,k);
    correct_G->numbers[0][0]=36;
    correct_G->numbers[1][0]=92;

    correct_G->numbers[0][1]=101;
    correct_G->numbers[1][1]=58;

    correct_G->numbers[0][2]=126;
    correct_G->numbers[1][2]=142;

    correct_G->numbers[0][3]=26;
    correct_G->numbers[1][3]=163;
}

void when_generating_G()
{
    matrix_G = generate_G(j,matrix_r,c_vec,n,k);
}

void given_correct_g()
{
    correct_g = 142;
}

void given_t()
{
    t=2;
}
void given_i()
{
    i=3;
}
void given_j()
{
    j=1;
}
void given_r()
{
    matrix_r = constructor(4,4);
    matrix_r->numbers[0][0] =1;
    matrix_r->numbers[1][0] =35;
    matrix_r->numbers[2][0] =52;
    matrix_r->numbers[3][0] =40;
    matrix_r->numbers[0][1] =33;
    matrix_r->numbers[1][1] =68;
    matrix_r->numbers[2][1] =69;
    matrix_r->numbers[3][1] =240;
    matrix_r->numbers[0][2] =54;
    matrix_r->numbers[1][2] =72;
    matrix_r->numbers[2][2] =212;
    matrix_r->numbers[3][2] =181;
    matrix_r->numbers[0][3] =38;
    matrix_r->numbers[1][3] =239;
    matrix_r->numbers[2][3] =176;
    matrix_r->numbers[3][3] =238;

}
void given_c_vec()
{
    c_vec = malloc(n* sizeof(int));
    c_vec[0]=1;
    c_vec[1]=2;
    c_vec[2]=3;
    c_vec[3]=4;
}

void when_calculating_g()
{
    g = calculate_g(t,i,j,matrix_r,k,c_vec);
}


void given_x_vec()
{
    x_vec = malloc(n* sizeof(Matrix *));
    for(int i=0;i<n;i++)
    {
        x_vec[i]=constructor(2,1);
    }
    x_vec[0]->numbers[0][0] =9;
    x_vec[0]->numbers[0][1] =5;

    x_vec[1]->numbers[0][0] =4;
    x_vec[1]->numbers[0][1] =4;

    x_vec[2]->numbers[0][0] =9;
    x_vec[2]->numbers[0][1] =8;

    x_vec[3]->numbers[0][0] =3;
    x_vec[3]->numbers[0][1] =2;
}

void given_correct_v_vec()
{
    correct_v_vec = malloc(n* sizeof(Matrix *));
    for(int i=0; i<n; i++)
    {
        correct_v_vec[i]=constructor(4,1);
    }
    correct_v_vec[0]->numbers[0][0] = 62;
    correct_v_vec[0]->numbers[0][1] = 59;
    correct_v_vec[0]->numbers[0][2] = 43;
    correct_v_vec[0]->numbers[0][3] = 84;

    correct_v_vec[1]->numbers[0][0] = 40;
    correct_v_vec[1]->numbers[0][1] = 28;
    correct_v_vec[1]->numbers[0][2] = 28;
    correct_v_vec[1]->numbers[0][3] = 48;

    correct_v_vec[2]->numbers[0][0] = 83;
    correct_v_vec[2]->numbers[0][1] = 62;
    correct_v_vec[2]->numbers[0][2] = 58;
    correct_v_vec[2]->numbers[0][3] = 102;

    correct_v_vec[3]->numbers[0][0] = 23;
    correct_v_vec[3]->numbers[0][1] = 20;
    correct_v_vec[3]->numbers[0][2] = 16;
    correct_v_vec[3]->numbers[0][3] = 30;
}

void when_calculating_v_vec()
{
    v_vec = generate_v_vec(x_vec,n,matrix_a);
}


void given_ss()
{
    matrix_ss = constructor(4,4);
    matrix_ss->numbers[0][0] =1;
    matrix_ss->numbers[1][0] =221;
    matrix_ss->numbers[2][0] =201;
    matrix_ss->numbers[3][0] =214;
    matrix_ss->numbers[0][1] =221;
    matrix_ss->numbers[1][1] =189;
    matrix_ss->numbers[2][1] =186;
    matrix_ss->numbers[3][1] =16;
    matrix_ss->numbers[0][2] =201;
    matrix_ss->numbers[1][2] =186;
    matrix_ss->numbers[2][2] =43;
    matrix_ss->numbers[3][2] =76;
    matrix_ss->numbers[0][3] =214;
    matrix_ss->numbers[1][3] =16;
    matrix_ss->numbers[2][3] =76;
    matrix_ss->numbers[3][3] =20;
}

void given_s()
{
    matrix_s = constructor(4,4);
    matrix_s->numbers[0][0] =2;
    matrix_s->numbers[1][0] =5;
    matrix_s->numbers[2][0] =2;
    matrix_s->numbers[3][0] =3;
    matrix_s->numbers[0][1] =3;
    matrix_s->numbers[1][1] =6;
    matrix_s->numbers[2][1] =4;
    matrix_s->numbers[3][1] =5;
    matrix_s->numbers[0][2] =4;
    matrix_s->numbers[1][2] =7;
    matrix_s->numbers[2][2] =4;
    matrix_s->numbers[3][2] =6;
    matrix_s->numbers[0][3] =1;
    matrix_s->numbers[1][3] =4;
    matrix_s->numbers[2][3] =1;
    matrix_s->numbers[3][3] =7;
}

void given_correct_r()
{
    correct_r = constructor(4,4);
    correct_r->numbers[0][0] =1;
    correct_r->numbers[1][0] =35;
    correct_r->numbers[2][0] =52;
    correct_r->numbers[3][0] =40;
    correct_r->numbers[0][1] =33;
    correct_r->numbers[1][1] =68;
    correct_r->numbers[2][1] =69;
    correct_r->numbers[3][1] =240;
    correct_r->numbers[0][2] =54;
    correct_r->numbers[1][2] =72;
    correct_r->numbers[2][2] =212;
    correct_r->numbers[3][2] =181;
    correct_r->numbers[0][3] =38;
    correct_r->numbers[1][3] =239;
    correct_r->numbers[2][3] =176;
    correct_r->numbers[3][3] =238;
}

void when_calculating_r()
{
    matrix_r = generate_r(matrix_s,matrix_ss);
}


void given_correct_ss()
{
    correct_ss = constructor(4,4);
    correct_ss->numbers[0][0] =1;
    correct_ss->numbers[1][0] =221;
    correct_ss->numbers[2][0] =201;
    correct_ss->numbers[3][0] =214;
    correct_ss->numbers[0][1] =221;
    correct_ss->numbers[1][1] =189;
    correct_ss->numbers[2][1] =186;
    correct_ss->numbers[3][1] =16;
    correct_ss->numbers[0][2] =201;
    correct_ss->numbers[1][2] =186;
    correct_ss->numbers[2][2] =43;
    correct_ss->numbers[3][2] =76;
    correct_ss->numbers[0][3] =214;
    correct_ss->numbers[1][3] =16;
    correct_ss->numbers[2][3] =76;
    correct_ss->numbers[3][3] =20;
}
void given_a()
{
    matrix_a = constructor(4,2);
    matrix_a->numbers[0][0] = 3;
    matrix_a->numbers[1][0] = 7;
    matrix_a->numbers[0][1] = 6;
    matrix_a->numbers[1][1] = 1;
    matrix_a->numbers[0][2] = 2;
    matrix_a->numbers[1][2] = 5;
    matrix_a->numbers[0][3] = 6;
    matrix_a->numbers[1][3] = 6;
}

void given_n()
{
    n=4;
}

void given_k()
{
    k=2;
}

void when_generating_ss()
{
    matrix_ss = generate_ss(matrix_a);
}

void when_generating_a()
{
    matrix_a = generate_a(k,n);
}

int then_ss_less_than_255()
{
    return  matrix_less_than_255(matrix_ss);
}

int then_a_less_than_255()
{
    return  matrix_less_than_255(matrix_a);
}

int matrix_less_than_255(Matrix * m)
{
    if(m==NULL){
        return true;
    }
    for (int i=0; i<m->rows;i++)
    {
        for(int j=0; j<m->columns;j++)
        {
            int cur = m->numbers[j][i];
            if(cur>255 || cur<0)
            {
                return false;
            }
        }
    }
    return true;
}