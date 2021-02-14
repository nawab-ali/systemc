/**
 * @file shift_reg_tb.h
 * @brief This file implements the 4-bit shift register testbench.
 * @author Nawab Ali
 */

#ifndef SHIFT_REG_TB_H
#define SHIFT_REG_TB_H

#include <systemc.h>

SC_MODULE (shift_reg_tb) {
    sc_out<bool> clk, din;

    SC_CTOR (shift_reg_tb) {
        SC_THREAD(generate_stimuli);
    }

    void generate_stimuli() {
        for (int i = 0; i < 5; ++i) {
            din = 1;
            wait(10, SC_NS);
        }

        sc_stop();
    }
};

#endif //SHIFT_REG_TB_H