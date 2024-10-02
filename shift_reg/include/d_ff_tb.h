/**
 * @file d_ff_tb.h
 * @brief This file implements the D Flip-Flop testbench.
 * @author Nawab Ali
 */

#ifndef D_FF_TB_H
#define D_FF_TB_H

#include <systemc.h>

SC_MODULE(d_ff_tb) {
    sc_in<bool> clk;
    sc_out<bool> din;

    SC_CTOR(d_ff_tb) {
        SC_THREAD(generate_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void generate_stimuli() {
        wait(11, SC_NS);

        din.write(0);
        wait(15, SC_NS);

        din.write(1);
        wait(15, SC_NS);

        din.write(0);
        wait(15, SC_NS);

        din.write(1);
        wait(15, SC_NS);

        sc_stop();
    }
};

#endif // D_FF_TB_H
