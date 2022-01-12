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
    sc_out<sc_int<32>> partial_sum_out[N];

    SC_CTOR (systolic_array) {
        SC_METHOD(matmul);
        dont_initialize();
        sensitive << clk.pos();

        init_weights();
        create_pe_array();
    }

private:
    pe pe_array[N][N];
    sc_int<8> weights[N][N];

    // Define signals for PE->PE data transfer
    sc_signal<sc_int<8>> activation_in_s[N][N-1];
    sc_signal<sc_int<32>> partial_sum_in_s[N-1][N];
    sc_signal<sc_int<8>> activation_out_s[N][N-1];
    sc_signal<sc_int<32>> partial_sum_out_s[N-1][N];

    // Multiply activations with stationary weights every cycle. Activations move left->right. Partial sums move
    // top->bottom.
    void matmul() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                // Set inputs/outputs for each PE
                pe_array[i][j].clk(clk);

                // Corner cases
                if (i == 0 && j == 0) {
                    pe_array[i][j].activation_in(activation_in[i]);
                    pe_array[i][j].partial_sum_in(partial_sum_in[j]);
                    pe_array[i][j].activation_out(activation_out_s[i][j]);
                    pe_array[i][j].partial_sum_out(partial_sum_out_s[i][j]);
                } else if (i == 0 && j == N-1) {
                    pe_array[i][j].activation_in(activation_in_s[i][j-1]);
                    pe_array[i][j].partial_sum_in(partial_sum_in[j]);
                    pe_array[i][j].partial_sum_out(partial_sum_out_s[i][j]);
                } else if (i == N-1 && j == 0) {
                    pe_array[i][j].activation_in(activation_in[i]);
                    pe_array[i][j].partial_sum_in(partial_sum_in_s[i-1][j]);
                    pe_array[i][j].activation_out(activation_out_s[i][j]);
                    pe_array[i][j].partial_sum_out(partial_sum_out[j]);
                } else if (i == N-1 && j == N-1) {
                    pe_array[i][j].activation_in(activation_in_s[i][j-1]);
                    pe_array[i][j].partial_sum_in(partial_sum_in_s[i-1][j]);
                    pe_array[i][j].partial_sum_out(partial_sum_out[j]);
                } else if (i == 0) {
                    pe_array[i][j].activation_in(activation_in_s[i][j-1]);
                    pe_array[i][j].partial_sum_in(partial_sum_in[j]);
                    pe_array[i][j].activation_out(activation_out_s[i][j-1]);
                    pe_array[i][j].partial_sum_out(partial_sum_out_s[i][j-1]);
                } else if (j == 0) {
                    pe_array[i][j].activation_in(activation_in[i]);
                    pe_array[i][j].partial_sum_in(partial_sum_in_s[i-1][j]);
                    pe_array[i][j].activation_out(activation_out_s[i][j]);
                    pe_array[i][j].partial_sum_out(partial_sum_out_s[i-1][j]);
                } else if (i == N-1) {
                    pe_array[i][j].activation_in(activation_in_s[i][j-1]);
                    pe_array[i][j].partial_sum_in(partial_sum_in_s[i-1][j]);
                    pe_array[i][j].activation_out(activation_out_s[i][j-1]);
                    pe_array[i][j].partial_sum_out(partial_sum_out[j]);
                } else if (j == N-1) {
                    pe_array[i][j].activation_in(activation_in_s[i][j-1]);
                    pe_array[i][j].partial_sum_in(partial_sum_in_s[i-1][j]);
                    pe_array[i][j].partial_sum_out(partial_sum_out_s[i-1][j]);
                } else {
                    pe_array[i][j].activation_in(activation_in_s[i][j-1]);
                    pe_array[i][j].partial_sum_in(partial_sum_in_s[i-1][j]);
                    pe_array[i][j].activation_out(activation_out_s[i][j-1]);
                    pe_array[i][j].partial_sum_out(partial_sum_out_s[i-1][j]);
                }
            }
        }
    }

    // Initialize weights to random values
    void init_weights() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                weights[i][j] = random(-128, 127);
            }
        }
    }

    // Create the PE array
    void create_pe_array() {
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