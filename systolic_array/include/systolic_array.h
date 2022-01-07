/**
 * @file systolic_array.h
 * @brief This file implements a Weight-stationary Systolic Array.
 * @author Nawab Ali
 */

#ifndef SYSTOLIC_ARRAY_H
#define SYSTOLIC_ARRAY_H

#include "pe.h"
#include "util.h"
#include <systemc.h>

template<uint8_t N>
SC_MODULE (systolic_array) {
public:
    sc_in<bool> clk;
    sc_in<sc_int<8>> activation_in[N];
    sc_in<sc_int<32>> partial_sum_in[N];
    sc_out<sc_int<8>> activation_out[N];
    sc_out<sc_int<32>> partial_sum_out[N];

    sc_signal<sc_int<8>> activation_in_s[N];
    sc_signal<sc_int<32>> partial_sum_in_s[N];
    sc_signal<sc_int<8>> activation_out_s[N];

    pe pe_array[N][N];
    sc_int<8> weights[N][N];

    SC_CTOR (systolic_array) {
        SC_METHOD(matmul);
        dont_initialize();
        sensitive << clk.pos();

        // Initialize weights to random values
        init_weights();

        // Create the PE array
        init_pe_array();
    }

    void matmul() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                pe_array[i][j].clk(clk);
                if (i == 0) {
                    pe_array[i][j].partial_sum_in(partial_sum_in[j]);
                } else if (j == 0) {
                    pe_array[i][j].activation_in(activation_in[i]);
                } else {
                    pe_array[i][j].partial_sum_in(partial_sum_in_s[i-1]);
                    pe_array[i][j].activation_in(activation_in_s[i-1]);
                    pe_array[i][j].activation_out(activation_out_s[i-1]);
                    pe_array[i][j].partial_sum_out(partial_sum_out[i-1]);
                }
            }
        }
    }

private:
    void init_weights() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                weights[i][j] = random(-128, 127);
            }
        }
    }

    void init_pe_array() {
        char name[16];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                snprintf(name, 16, "PE_%d_%d", i, j);
                pe_array[i][j] = pe(name, weights[i][j]);
            }
        }
    }
};

#endif //SYSTOLIC_ARRAY_H