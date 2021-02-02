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
    sc_in<sc_uint<4>> a, b;
    sc_out<bool> c_out;
    sc_out<sc_uint<4>> sum;

    full_adder fa0, fa1, fa2, fa3;
    sc_signal<bool> c1, c2, c3;
    sc_signal<bool> s0, s1, s2, s3;

    SC_CTOR (four_bit_adder) : fa0("full_adder_0"), fa1("full_adder_1"), fa2("full_adder_2"), fa3("full_adder_3") {
        fa0.a(a[0]);
        fa0.b(b[0]);
        fa0.c_in(c_in);
        fa0.sum(s0);
        fa0.c_out(c1);

        fa1.a(a[1]);
        fa1.b(b[1]);
        fa1.c_in(c1);
        fa1.sum(s1);
        fa1.c_out(c2);

        fa2.a(a[2]);
        fa2.b(b[2]);
        fa2.c_in(c2);
        fa2.sum(s2);
        fa2.c_out(c3);

        fa3.a(a[3]);
        fa3.b(b[3]);
        fa3.c_in(c3);
        fa3.sum(s3);
        fa3.c_out(c_out);

        sum[0] = s0;
        sum[1] = s1;
        sum[2] = s2;
        sum[3] = s3;
    }
};

#endif //FOUR_BIT_ADDER_H