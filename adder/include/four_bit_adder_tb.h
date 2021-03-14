/**
 * @file four_bit_adder_tb.h
 * @brief This file implements the testbench for the 4-bit Adder.
 * @author Nawab Ali
 */

#ifndef FOUR_BIT_ADDER_TB_H
#define FOUR_BIT_ADDER_TB_H

#include <systemc.h>
#include "four_bit_adder.h"

SC_MODULE (four_bit_adder_tb) {
    sc_in<bool> clk;
    sc_out<bool> c_in;
    sc_out<bool> a[4], b[4];

    SC_CTOR (four_bit_adder_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        wait();
        c_in = 0;

        a[0] = 0;
        a[1] = 0;
        a[2] = 0;
        a[3] = 1;

        b[0] = 0;
        b[1] = 0;
        b[2] = 0;
        b[3] = 0;
        wait(11, SC_NS);

        sc_stop();
    }
};

#endif //FOUR_BIT_ADDER_TB_H