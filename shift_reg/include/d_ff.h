/**
 * @file d_ff.h
 * @brief This file implements a D Flip-Flop.
 * @author Nawab Ali
 */

#ifndef D_FF_H
#define D_FF_H

#include <systemc.h>

SC_MODULE (d_ff) {
    sc_in<bool> clk;
    sc_in<bool> din;
    sc_out<bool> dout;

    SC_CTOR (d_ff) {
        SC_METHOD(assign);
        dont_initialize();
        sensitive << clk.pos();
    }

    void assign() {
        dout.write(din.read());
    }
};

#endif //D_FF_H

