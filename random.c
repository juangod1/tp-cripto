//
// Created by Juan Godfrid on 2019-06-01.
//

#include <stdint.h>
#include "include/random.h"

int64_t seed;

void setSeed(int64_t s) {
    seed = (s ^ 0x5DEECE66DL) & ((1LL << 48) - 1);
}

uint8_t nextChar(void){
    seed = (seed * 0x5DEECE66DL + 0xBL) & ((1LL << 48) - 1);
    return (uint8_t)(seed>>40);
}