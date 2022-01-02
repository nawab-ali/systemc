/**
 * @file pe_tb.h
 * @brief This file implements the testbench for the PE.
 * @author Nawab Ali
 */

#ifndef PE_TB_H
#define PE_TB_H

#include <systemc.h>

SC_MODULE (pe_tb) {
public:
    sc_in<bool> clk;
    sc_in<sc_int<8>> activation_in;
    sc_in<sc_int<32>> partial_sum_in;
    sc_out<sc_int<8>> activation_out;
    sc_out<sc_int<32>> partial_sum_out;

    SC_CTOR (pe_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        const int num_samples = 10;
        const sc_int<8> weight = 4;
        sc_int<8> activations_out_observed[num_samples];
        sc_int<32> partial_sums_observed[num_samples], partial_sums_expected[num_samples];
        sc_int<8> activations[num_samples] = {0, 1, -127, 127, 4, 5, 6, 7, 8, 9};
        sc_int<32> partial_sums[num_samples] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        wait();
        for (int i = 0; i < num_samples; ++i) {
            activation_out.write(activations[i]);
            partial_sum_out.write(partial_sums[i]);
            wait();
            partial_sums_observed[i] = partial_sum_in.read();
            activations_out_observed[i] = activation_in.read();
        }

        // Calculate expected partial sums
        for (int i = 0; i < num_samples; ++i) {
            partial_sums_expected[i] = partial_sums[i] + activations[i] * weight;
        }

        // Validate PE results
        for (int i = 1; i < num_samples; ++i) {
            sc_assert(partial_sums_observed[i] == partial_sums_expected[i-1]);
            sc_assert(activations_out_observed[i] == activations[i-1]);
        }

        sc_stop();
    }
};

#endif //PE_TB_H