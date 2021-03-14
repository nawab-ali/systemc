/**
 * @file four_bit_adder.h
 * @brief This file implements a 4-bit Adder.
 * @author Nawab Ali
 */

#ifndef FOUR_BIT_ADDER_H
#define FOUR_BIT_ADDER_H

#include <systemc.h>
#include "full_adder.h"

SC_MODULE (four_bit_adder) {
    sc_in<bool> c_in;
    sc_in<bool> a[4], b[4];
    sc_out<bool> c_out;
    sc_out<bool> sum[4];

    full_adder fa0, fa1, fa2, fa3;
    sc_signal<bool> c[3], s[4];

    SC_CTOR (four_bit_adder) : fa0("full_adder_0"), fa1("full_adder_1"), fa2("full_adder_2"), fa3("full_adder_3") {
        SC_METHOD(generate_sum);
        dont_initialize();
        sensitive << s[0] << s[1] << s[2] << s[3];

        fa0.a(a[0]);
        fa0.b(b[0]);
        fa0.c_in(c_in);
        fa0.sum(s[0]);
        fa0.c_out(c[0]);

        fa1.a(a[1]);
        fa1.b(b[1]);
        fa1.c_in(c[0]);
        fa1.sum(s[1]);
        fa1.c_out(c[1]);

        fa2.a(a[2]);
        fa2.b(b[2]);
        fa2.c_in(c[1]);
        fa2.sum(s[2]);
        fa2.c_out(c[2]);

        fa3.a(a[3]);
        fa3.b(b[3]);
        fa3.c_in(c[2]);
        fa3.sum(s[3]);
        fa3.c_out(c_out);
    }

    void generate_sum() {
        for (int i = 0; i < 4; ++i) {
            sum[i].write(s[i]);
        }
    }
};

#endif //FOUR_BIT_ADDER_H