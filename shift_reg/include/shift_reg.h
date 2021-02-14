/**
 * @file shift_reg.h
 * @brief This file implements a 4-bit shift register.
 * @author Nawab Ali
 */

#ifndef SHIFT_REG_H
#define SHIFT_REG_H

#include "d_ff.h"
#include <systemc.h>

SC_MODULE (shift_reg) {
    sc_in<bool> clk, din;
    sc_out<bool> r0, r1, r2, r3;
    d_ff dff0, dff1, dff2, dff3;
    sc_signal<bool> s0, s1, s2, s3;

    SC_CTOR (shift_reg) : dff0("dff0"), dff1("dff1"), dff2("dff2"), dff3("dff3") {
        SC_METHOD(shift);
        sensitive << clk.pos();
    }

    void shift() {
        cout << "shift: begin" << endl;
        dff0.clk(clk);
        dff0.din(din);
        dff0.dout(s0);

        dff1.clk(clk);
        dff1.din(s0);
        dff1.dout(s1);

        dff2.clk(clk);
        dff2.din(s1);
        dff2.dout(s2);

        dff3.clk(clk);
        dff3.din(s2);
        dff3.dout(s3);

        r0 = s0;
        r1 = s1;
        r2 = s2;
        r3 = s3;
        cout << "shift: end" << endl;
    }
};

#endif //SHIFT_REG_H