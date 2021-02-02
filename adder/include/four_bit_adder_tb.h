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
    sc_out<bool> c_in;
    sc_out<sc_uint<4>> a, b;

    SC_CTOR (four_bit_adder_tb) {
        SC_THREAD(stimulate);
    }

    void stimulate() {
        c_in = 0;
        sc_uint<4> input = 0;

        while (input <= 15) {
            a = b = input;
            wait(1, SC_NS);
            input++;
        }

        sc_stop();
    }
};

#endif //FOUR_BIT_ADDER_TB_H