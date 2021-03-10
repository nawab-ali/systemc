/**
 * @file and.h
 * @brief This file implements the AND gate.
 * @author Nawab Ali
 */

#ifndef AND_H
#define AND_H

#include <systemc.h>

SC_MODULE (and2) {
    sc_in<bool> input_1;
    sc_in<bool> input_2;
    sc_out<bool> output;

    SC_CTOR (and2) {
        SC_METHOD(compute_and);
        sensitive << input_1 << input_2;
    }

    void compute_and() {
        output.write(input_1.read() && input_2.read());
    }
};

#endif //AND_H
