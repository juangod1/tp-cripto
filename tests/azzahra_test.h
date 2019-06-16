#ifndef TP_CRIPTO_TEST_AZZAHRA_H
#define TP_CRIPTO_TEST_AZZAHRA_H

#include "../include/azzahra.h"
#include "util.h"
#include <stddef.h>

void test_generate_a();
void test_generate_ss();
void given_n();
void given_k();
void when_generating_a();
int then_ss_less_than_255();
int then_a_less_than_255();
int matrix_less_than_255(Matrix * m);
void given_a();
void given_correct_ss();
void when_generating_ss();

void given_ss();
void given_s();
void given_correct_r();
void when_calculating_r();
void test_generate_r();

void test_generate_v_vec();
void given_x_vec();
void given_correct_v_vec();
void when_calculating_v_vec();

#endif //TP_CRIPTO_TEST_AZZAHRA_H
