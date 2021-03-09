/**
 * @file shift_reg_tb.h
 * @brief This file implements the 4-bit shift register testbench.
 * @author Nawab Ali
 */

#ifndef SHIFT_REG_TB_H
#define SHIFT_REG_TB_H

#include <systemc.h>

SC_MODULE (shift_reg_tb) {
    sc_in<bool> clk;
    sc_out<bool> din;

    SC_CTOR (shift_reg_tb) {
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

#endif //SHIFT_REG_TB_H