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

    SC_CTOR (shift_reg) : dff0("dff0"), dff1("dff1"), dff2("dff2"), dff3("dff3") {
        SC_METHOD(shift);
        sensitive << clk.pos();
    }

    void shift() {
        dff0.clk(clk);
        dff0.din(din);
        dff0.dout(r0);

        dff1.clk(clk);
        dff1.din(dff0.dout);
        dff1.dout(r1);

        dff2.clk(clk);
        dff2.din(dff1.dout);
        dff2.dout(r2);

        dff3.clk(clk);
        dff3.din(dff2.dout);
        dff3.dout(r3);
    }
};

#endif //SHIFT_REG_H