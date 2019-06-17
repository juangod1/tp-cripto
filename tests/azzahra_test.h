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


void test_calculate_g();
void given_t();
void given_i();
void given_j();
void given_r();
void given_c_vec();
void given_correct_g();
void when_calculating_g();

void test_calculate_G();
void given_correct_G();
void when_generating_G();


void test_generate_rw();
void when_generating_rw();
void given_w();
void given_correct_rw();


void test_generate_sh();
void given_v();
void given_G();
void given_correct_sh();
void when_generating_sh();


void test_generate_B();
void given_sh_vec();
void given_correct_B();
void when_calculating_B();

void test_compute_ss();
void given_B();
void when_computing_ss();

void test_compute_G_vec();
void given_correct_G_vec();
void when_computing_G_vec();

void test_compute_small_r();
void given_G_vec();
void given_correct_small_r();
void when_computing_small_r();

void test_compute_R();
void when_computing_R();

void test_compute_s_from_SS_and_R();
void given_correct_s();
void when_computing_s_from_SS_and_R();

void test_compute_w_from_SS_and_Rw();
void when_computing_w_from_SS_and_Rw();
void given_correct_w();
void given_rw();

#endif //TP_CRIPTO_TEST_AZZAHRA_H
