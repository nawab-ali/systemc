/**
 * @file half_adder.h
 * @brief This file implements a Half-Adder.
 * @author Nawab Ali
 */

#ifndef HALF_ADDER_H
#define HALF_ADDER_H

#include <systemc.h>

SC_MODULE (half_adder) {
    sc_in<bool> a, b;
    sc_out<bool> sum, carry;

    SC_CTOR (half_adder) {
        SC_METHOD(add);
        dont_initialize();
        sensitive << a << b;
    }

    void add() {
        sum = a ^ b;
        carry = a & b;
    }
};

#endif //HALF_ADDER_H