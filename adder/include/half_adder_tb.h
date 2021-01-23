/**
 * @file half_adder_tb.h
 * @brief This file implements the testbench for the Half-Adder.
 * @author Nawab Ali
 */

#ifndef HALF_ADDER_TB_H
#define HALF_ADDER_TB_H

#include <systemc.h>

SC_MODULE (half_adder_tb) {
    sc_out<bool> a, b;

    SC_CTOR (half_adder_tb) {
        SC_THREAD(stimulate);
    }

    void stimulate() {
        sc_uint<2> input = 0;

        while (input <= 3) {
            a = input[0];
            b = input[1];

            wait(1, SC_NS);
            input++;
        }

        sc_stop();
    }
};

#endif //HALF_ADDER_TB_H