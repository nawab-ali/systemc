/**
 * @file full_adder.h
 * @brief This file implements a Full-Adder.
 * @author Nawab Ali
 */

#ifndef FULL_ADDER_H
#define FULL_ADDER_H

#include <systemc.h>
#include "half_adder.h"

SC_MODULE (full_adder) {
    sc_in<bool> a, b, c_in;
    sc_out<bool> sum, c_out;

    half_adder ha_1, ha_2;
    sc_signal<bool> s1, s2, s3;

    SC_CTOR (full_adder) : ha_1("half_adder_1"), ha_2("half_adder_2") {
        ha_1.a(a);
        ha_1.b(b);
        ha_1.sum(s1);
        ha_1.carry(s2);

        ha_2.a(s1);
        ha_2.b(c_in);
        ha_2.sum(sum);
        ha_2.carry(s3);

        SC_METHOD(func_or);
        dont_initialize();
        sensitive << s2 << s3;
    }

    void func_or() {
        c_out = s2 | s3;
    }
};

#endif //FULL_ADDER_H