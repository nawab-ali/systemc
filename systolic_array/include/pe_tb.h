/**
 * @file pe_tb.h
 * @brief This file implements the test bench for the PE.
 * @author Nawab Ali
 */

#ifndef PE_TB_H
#define PE_TB_H

#include "util.h"
#include <systemc.h>

const sc_int<8> weight = 4;
const int num_samples = 100;

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

private:
    sc_int<8> activations[num_samples];
    sc_int<8> activations_out_observed[num_samples];
    sc_int<32> partial_sums[num_samples];
    sc_int<32> partial_sums_observed[num_samples];
    sc_int<32> partial_sums_expected[num_samples];

    // Generate stimuli for PE
    void gen_stimuli() {
        init_data();
        wait();

        for (int i = 0; i < num_samples; ++i) {
            activation_out.write(activations[i]);
            partial_sum_out.write(partial_sums[i]);
            wait();
            partial_sums_observed[i] = partial_sum_in.read();
            activations_out_observed[i] = activation_in.read();
        }

        validate_results();
        sc_stop();
    }

    // Initialize activations and partial_sums to random numbers
    void init_data() {
        for (int i = 0; i < num_samples; ++i) {
            activations[i] = random(-127, 127);
            partial_sums[i] = random(0, 1000);
            partial_sums_expected[i] = partial_sums[i] + activations[i] * weight;
        }
    }

    // Validate PE results
    void validate_results() {
        for (int i = 1; i < num_samples; ++i) {
            sc_assert(partial_sums_observed[i] == partial_sums_expected[i-1]);
            sc_assert(activations_out_observed[i] == activations[i-1]);
        }
    }
};

#endif //PE_TB_H