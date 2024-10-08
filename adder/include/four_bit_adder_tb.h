/**
 * @file four_bit_adder_tb.h
 * @brief This file implements the testbench for the 4-bit Adder.
 * @author Nawab Ali
 */

#ifndef FOUR_BIT_ADDER_TB_H
#define FOUR_BIT_ADDER_TB_H

#include "four_bit_adder.h"
#include <systemc.h>

SC_MODULE(four_bit_adder_tb) {
    sc_in<bool> clk;
    sc_out<bool> c_in;
    sc_out<sc_uint<4>> a, b;

    SC_CTOR(four_bit_adder_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        wait();

        c_in = 1;
        a = 0;
        b = 0;

        wait(11, SC_NS);

        c_in = 0;
        a = 15;
        b = 15;

        wait(11, SC_NS);

        sc_stop();
    }
};

#endif // FOUR_BIT_ADDER_TB_H
