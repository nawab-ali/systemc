/**
 * @file pe_tb.h
 * @brief This file implements the test bench for the PE.
 * @author Nawab Ali
 */

#ifndef PE_TB_H
#define PE_TB_H

#include "util.h"
#include <systemc.h>
#include <vector>

using namespace std;

template <uint32_t N> SC_MODULE(pe_tb) {
  public:
    sc_in<bool> clk;
    sc_in<sc_int<8>> activation_in;
    sc_in<sc_int<32>> partial_sum_in;
    sc_out<sc_int<8>> activation_out;
    sc_out<sc_int<32>> partial_sum_out;

    SC_CTOR(pe_tb)
        : weight(0), activations(N, 0), activations_out_observed(N, 0), partial_sums(N, 0), partial_sums_observed(N, 0),
          partial_sums_expected(N, 0) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
        init_data();
    }

    void set_weight(const sc_int<8> &w) { weight = w; }

    sc_int<8> get_weight() { return weight; }

  private:
    sc_int<8> weight;
    vector<sc_int<8>> activations;
    vector<sc_int<8>> activations_out_observed;
    vector<sc_int<32>> partial_sums;
    vector<sc_int<32>> partial_sums_observed;
    vector<sc_int<32>> partial_sums_expected;

    // Generate stimuli for PE
    void gen_stimuli() {
        wait();

        for (int i = 0; i < N; ++i) {
            activation_out.write(activations[i]);
            partial_sum_out.write(partial_sums[i]);
            wait();
            partial_sums_observed[i] = partial_sum_in.read();
            activations_out_observed[i] = activation_in.read();
        }

        wait();
        validate_results();
        sc_stop();
    }

    // Initialize activations and partial sums to random values
    void init_data() {
        for (int i = 0; i < N; ++i) {
            activations[i] = random(-128, 127);
            partial_sums[i] = random(0, 1000);
            partial_sums_expected[i] = partial_sums[i] + activations[i] * weight;
        }
    }

    // Validate PE results
    void validate_results() {
        for (int i = 1; i < N; ++i) {
            sc_assert(partial_sums_observed[i] == partial_sums_expected[i - 1]);
            sc_assert(activations_out_observed[i] == activations[i - 1]);
        }
    }
};

#endif // PE_TB_H
