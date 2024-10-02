/**
 * @file systolic_array_tb.h
 * @brief This file implements the test bench for the Systolic Array.
 * @author Nawab Ali
 */

#ifndef SYSTOLIC_ARRAY_TB_H
#define SYSTOLIC_ARRAY_TB_H

#include "util.h"
#include <systemc.h>

template <uint8_t N> SC_MODULE(systolic_array_tb) {
  public:
    sc_in<bool> clk;
    sc_vector<sc_out<sc_int<8>>> activation_in{"activation_in", N};
    sc_vector<sc_out<sc_int<32>>> partial_sum_in{"partial_sum_in", N};
    sc_vector<sc_in<sc_int<8>>> activation_out{"activation_out", N};
    sc_vector<sc_in<sc_int<32>>> partial_sum_out{"partial_sum_out", N};

    SC_CTOR(systolic_array_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();

        SC_METHOD(monitor);
        dont_initialize();
        sensitive << clk.pos();
    }

  private:
    // Generate stimuli for Systolic Array
    void gen_stimuli() {
        vector<vector<int8_t>> activations = {{1, 0, 0, 0},   {2, 5, 0, 0},   {3, 6, 9, 0}, {4, 7, 10, 13},
                                              {0, 8, 11, 14}, {0, 0, 12, 15}, {0, 0, 0, 16}};

        wait();

        // Initialize activations and partial sums
        for (auto &a : activations) {
            for (int i = 0; i < N; ++i) {
                partial_sum_in[i].write(0);
                activation_in[i].write(a[i]);
            }
            wait();
        }

        // Wait 2N-1 cycles for the matrix multiplication to complete. We've already waited 1 cycle in the above for
        // loop.
        wait(2 * N - 2);
        sc_stop();
    }

    // Monitor the partial_sum_out and activation_out values every cycle
    void monitor() {
        string log = "partial_sum_out: ";

        for (auto &psum : partial_sum_out) {
            log += to_string(psum.read()) + " ";
        }
        SC_REPORT_INFO("systolic_array_tb", log.c_str());

        log = "activation_out: ";
        for (auto &a : activation_out) {
            log += to_string(static_cast<int32_t>(a.read())) + " ";
        }
        SC_REPORT_INFO("systolic_array_tb", log.c_str());
    }
};

#endif // SYSTOLIC_ARRAY_TB_H
