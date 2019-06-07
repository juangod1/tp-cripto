#include "../include/azzahra.h"
#include "azzahra_test.h"

Matrix * matrix_a = NULL;
int n;
int k;

void test_generate_a()
{
    given_n();
    given_k();
    when_generating_a();
    assert(matrix_a!=NULL);

    destroy_matrix(matrix_a);
}

void given_n()
{
    n=4;
}

void given_k()
{
    k=2;
}

void when_generating_a()
{
    matrix_a = generate_a(k,n);
}