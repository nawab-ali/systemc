/**
 * @file systolic_array.h
 * @brief This file implements a Weight-stationary Systolic Array.
 * @author Nawab Ali
 */

#ifndef SYSTOLIC_ARRAY_H
#define SYSTOLIC_ARRAY_H

#include "pe.h"
#include <systemc.h>

template<uint8_t N>
SC_MODULE (systolic_array) {
public:
    sc_in<bool> clk;
    pe pe_array[N][N];
    sc_uint<8> weights[N][N];

    SC_CTOR (systolic_array) {
        SC_METHOD(matmul);
        dont_initialize();
        sensitive << clk.pos();
    }

    void matmul() {

    }

private:
    void init_weights() {

    }
};

#endif //SYSTOLIC_ARRAY_H