//
// Created by Juan Godfrid on 2019-06-03.
//

#ifndef TP_CRIPTO_UTIL_H
#define TP_CRIPTO_UTIL_H

#include <ntsid.h>

void run_test(char * testname, void (*test)());
void fail();
void success();
int assert_generic(char * assertion, int boolean);
void assert_true(char * assertion, int boolean);
void assert_false(char * assertion, int boolean);
void assert_equal(char * assertion, void * expected, void * found);
void assert_not_equal(char * assertion, void * expected, void * found);
void print_binary_array(const char *char_array, size_t char_array_size);
void print_hexa_array(const char* char_array, size_t char_array_size);
#endif //TP_CRIPTO_UTIL_H
