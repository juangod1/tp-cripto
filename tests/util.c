//
// Created by Juan Godfrid on 2019-06-03.
//

#include "util.h"
#include <stdio.h>
#include <stdlib.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KCYN  "\x1B[36m"
#define KYEL  "\x1B[33m"

void run_test(char * testname, void (*test)()){
    printf("%sRunning %s... \n",KCYN,testname);
    test();
}

void assert(char * assertion, int boolean){
    printf("%sAsserting %s: ",KYEL,assertion);
    if(boolean)
        success();
    else
        fail();
}

void fail(){
    printf("%sFail\n",KRED);
    exit(-1);
}

void success(){
    printf("%sSuccess\n",KGRN);
}