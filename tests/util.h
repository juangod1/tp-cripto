//
// Created by Juan Godfrid on 2019-06-03.
//

#ifndef TP_CRIPTO_UTIL_H
#define TP_CRIPTO_UTIL_H

void run_test(char * testname, void (*test)());
void fail();
void success();
void assert(char * assertion, int boolean);

#endif //TP_CRIPTO_UTIL_H
