//
// Created by Juan Godfrid on 2019-06-03.
//

#ifndef TP_CRIPTO_UTIL_H
#define TP_CRIPTO_UTIL_H

void run_test(char * testname, void (*test)());
void fail();
void success();
int assert_generic(char * assertion, int boolean);
void assert_true(char * assertion, int boolean);
void assert_false(char * assertion, int boolean);
void assert_equal(char * assertion, void * expected, void * found);
void assert_not_equal(char * assertion, void * expected, void * found);
#endif //TP_CRIPTO_UTIL_H
