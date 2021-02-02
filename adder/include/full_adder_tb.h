/**
 * @file full_adder_tb.h
 * @brief This file implements the testbench for the Full-Adder.
 * @author Nawab Ali
 */

#ifndef FULL_ADDER_TB_H
#define FULL_ADDER_TB_H

#include <systemc.h>
#include "full_adder.h"

SC_MODULE (full_adder_tb) {
    sc_out<bool> a, b, c_in;

    SC_CTOR (full_adder_tb) {
        SC_THREAD(stimulate);
    }

    void stimulate() {
        sc_uint<3> input = 0;

        while (input <= 7) {
            a = input[0];
            b = input[1];
            c_in = input[2];

            wait(1, SC_NS);
            input++;
        }

        sc_stop();
    }
};

#endif //FULL_ADDER_TB_H