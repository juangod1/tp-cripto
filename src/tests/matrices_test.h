#ifndef TP_CRIPTO_MATRICES_TEST_H
#define TP_CRIPTO_MATRICES_TEST_H

#include "../include/matrices.h"
#include "util.h"
#include <stddef.h>
#include <stdio.h>

void test_inversion_mod();

void given_modulus();
void given_matrix();
void when_calculating_inverse_mod();
void test_remove_column_and_row();
void given_correct_inverse_matrix();
void given_row();
void given_column();
void given_correct_small_matrix();
void when_removing_column_and_row();
void test_matrix_of_cofactors();
void given_correct_cofactor_matrix();
void when_calculating_cofactor_matrix();
void test_inversion_mod_1();
void test_conversion();

void given_m1();
void given_m2();
void given_correct_result_matrix();
void when_multiplying_matrices();
void test_multiplication();

void test_linear_equations();
void given_linear_equations();
void given_correct_linear_equation_result();
void when_solving_linear_equations();

void test_matrix_determinant();

#endif //TP_CRIPTO_MATRICES_TEST_H