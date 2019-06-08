#ifndef TP_CRIPTO_MATRICES_TEST_H
#define TP_CRIPTO_MATRICES_TEST_H

#include "../include/matrices.h"
#include "util.h"
#include <stddef.h>

void test_inversion_mod();

void given_modulus();
void given_matrix();
void when_calculating_inverse_mod();
void test_remove_column_and_row();
void given_row();
void given_column();
void given_correct_small_matrix();
void when_removing_column_and_row();

#endif //TP_CRIPTO_MATRICES_TEST_H
