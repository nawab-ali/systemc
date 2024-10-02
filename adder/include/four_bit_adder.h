/**
 * @file four_bit_adder.h
 * @brief This file implements a 4-bit Adder.
 * @author Nawab Ali
 */

#ifndef FOUR_BIT_ADDER_H
#define FOUR_BIT_ADDER_H

#include "full_adder.h"
#include <systemc.h>

SC_MODULE(four_bit_adder) {
    sc_in<bool> c_in;
    sc_in<sc_uint<4>> a, b;
    sc_out<bool> c_out;
    sc_out<sc_uint<4>> sum;

    full_adder fa0, fa1, fa2, fa3;
    sc_signal<bool> s_a[4], s_b[4], c[3], s[4];

    SC_CTOR(four_bit_adder) : fa0("full_adder_0"), fa1("full_adder_1"), fa2("full_adder_2"), fa3("full_adder_3") {
        SC_METHOD(read_inputs);
        dont_initialize();
        sensitive << a << b;

        SC_METHOD(generate_sum);
        dont_initialize();
        sensitive << s[0] << s[1] << s[2] << s[3];

        fa0.a(s_a[0]);
        fa0.b(s_b[0]);
        fa0.c_in(c_in);
        fa0.sum(s[0]);
        fa0.c_out(c[0]);

        fa1.a(s_a[1]);
        fa1.b(s_b[1]);
        fa1.c_in(c[0]);
        fa1.sum(s[1]);
        fa1.c_out(c[1]);

        fa2.a(s_a[2]);
        fa2.b(s_b[2]);
        fa2.c_in(c[1]);
        fa2.sum(s[2]);
        fa2.c_out(c[2]);

        fa3.a(s_a[3]);
        fa3.b(s_b[3]);
        fa3.c_in(c[2]);
        fa3.sum(s[3]);
        fa3.c_out(c_out);
    }

    void read_inputs() {
        sc_uint<4> temp_a = a.read();
        sc_uint<4> temp_b = b.read();

        for (int i = 0; i < 4; ++i) {
            s_a[i] = temp_a[i].to_bool();
            s_b[i] = temp_b[i].to_bool();
        }
    }

    void generate_sum() {
        sc_uint<4> temp;

        for (int i = 0; i < 4; ++i) {
            temp[i] = s[i];
        }
        sum.write(temp);
    }
};

#endif // FOUR_BIT_ADDER_H
