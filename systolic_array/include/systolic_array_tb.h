/**
 * @file systolic_array_tb.h
 * @brief This file implements the test bench for the Systolic Array.
 * @author Nawab Ali
 */

#ifndef SYSTOLIC_ARRAY_TB_H
#define SYSTOLIC_ARRAY_TB_H

#include "util.h"
#include <iostream>
#include <systemc.h>

using namespace std;

template<uint8_t N>
SC_MODULE (systolic_array_tb) {
public:
    sc_in<bool> clk;
    sc_vector<sc_out<sc_int<8>>> activation_in{"activation_in", N};
    sc_vector<sc_out<sc_int<32>>> partial_sum_in{"partial_sum_in", N};
    sc_vector<sc_in<sc_int<32>>> partial_sum_out{"partial_sum_out", N};

    SC_CTOR (systolic_array_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

private:
    // Generate stimuli for Systolic Array
    void gen_stimuli() {
        wait();

        // Initialize partial_sum_in to 0
        for (auto psum_in : partial_sum_in) {
            psum_in.write(0);
        }

        // Initialize activation_in to random values
        for (auto a_in : activation_in) {
            a_in.write(random(-128, 127));
        }

        wait(N);

        for (auto psum_out : partial_sum_out) {
            cout << psum_out.read() << endl;
        }

        sc_stop();
    }
};

#endif //SYSTOLIC_ARRAY_TB_H