#include "azzahra_test.h"
#include <stdbool.h>
Matrix * matrix_ss = NULL;
Matrix * correct_ss = NULL;
Matrix * matrix_a = NULL;
int n;
int k;

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
    assert_not_equal_memory("SS is not null",matrix_ss,NULL);
    assert_true("SS values < 255", then_ss_less_than_255());
    printf("matrix_ss\n");
    print(matrix_ss);
    printf("correct_ss\n");
    print(correct_ss);
    assert_true("SS is correct", equals(matrix_ss,correct_ss)==SUCC);

    destroy_matrix(matrix_a);
    destroy_matrix(matrix_ss);
    destroy_matrix(correct_ss);
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
    correct_ss->numbers[0][2] =101;
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