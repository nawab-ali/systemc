/**
 * @file four_bit_adder.h
 * @brief This file implements a 4-bit Adder.
 * @author Nawab Ali
 */

#ifndef FOUR_BIT_ADDER_H
#define FOUR_BIT_ADDER_H

#include <systemc.h>
#include "vector.h"
#include "full_adder.h"

SC_MODULE (four_bit_adder) {
    sc_in<bool> c_in;
    sc_in<sc_lv<4>> a, b;
    sc_out<bool> c_out;
    sc_out<sc_lv<4>> sum;

    sc_out<bool> a0, a1, a2, a3;
    sc_out<bool> b0, b1, b2, b3;

    full_adder fa0, fa1, fa2, fa3;
    vector2bits v2b_a, v2b_b;
    bits2vector b2v_sum;

    sc_signal<bool> c1, c2, c3;
    sc_signal<bool> s0, s1, s2, s3;

    SC_CTOR (four_bit_adder) : fa0("full_adder_0"), fa1("full_adder_1"), fa2("full_adder_2"), fa3("full_adder_3"),
                               v2b_a("vector2bits_a"), v2b_b("vector2bits_b"), b2v_sum("bits2vector_sum") {
        SC_METHOD(read_inputs);
        dont_initialize();
        sensitive << a << b;

        SC_METHOD(generate_sum);
        dont_initialize();
        sensitive << s0 << s1 << s2 << s3;

        fa0.a(a0);
        fa0.b(b0);
        fa0.c_in(c_in);
        fa0.sum(s0);
        fa0.c_out(c1);

        fa1.a(a1);
        fa1.b(b1);
        fa1.c_in(c1);
        fa1.sum(s1);
        fa1.c_out(c2);

        fa2.a(a2);
        fa2.b(b2);
        fa2.c_in(c2);
        fa2.sum(s2);
        fa2.c_out(c3);

        fa3.a(a3);
        fa3.b(b3);
        fa3.c_in(c3);
        fa3.sum(s3);
        fa3.c_out(c_out);
    }

    void read_inputs() {
        v2b_a.input(a);
        v2b_a.o0(a0);
        v2b_a.o1(a1);
        v2b_a.o2(a2);
        v2b_a.o3(a3);

        v2b_b.input(b);
        v2b_b.o0(b0);
        v2b_b.o1(b1);
        v2b_b.o2(b2);
        v2b_b.o3(b3);
    }

    void generate_sum() {
        b2v_sum.i0(s0);
        b2v_sum.i1(s1);
        b2v_sum.i2(s2);
        b2v_sum.i3(s3);
        b2v_sum.output(sum);
    }
};

#endif //FOUR_BIT_ADDER_H