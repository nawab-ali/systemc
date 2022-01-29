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
    sc_out<sc_int<8>> activation_in[N];
    sc_out<sc_int<32>> partial_sum_in[N];
    sc_in<sc_int<8>> activation_out[N];
    sc_in<sc_int<32>> partial_sum_out[N];

    SC_CTOR (systolic_array_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

private:
    // Generate stimuli for Systolic Array
    void gen_stimuli() {
        wait();

        // Initialize activations and partial sums
        for (int i = 0; i < N; ++i) {
            partial_sum_in[i].write(0);
            activation_in[i].write(random(-128, 127));
        }

        wait(N);

        for (int i = 0; i < N; ++i) {
            cout << partial_sum_out[i].read() << " ";
        }
        cout << endl;

        sc_stop();
    }
};

#endif //SYSTOLIC_ARRAY_TB_H