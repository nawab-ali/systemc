/**
 * @file alu_tb.h
 * @brief This file implements the testbench for the ALU.
 * @author Nawab Ali
 */

#ifndef ALU_TB_H
#define ALU_TB_H

#include <systemc.h>

SC_MODULE (alu_tb) {

    SC_CTOR (alu_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        wait();

        reset = 1;
        wait();

        reset = 0;
        enable = 1;
        for (int i = 0; i < 5; ++i) {
            wait();
        }

        reset = 1;
        wait();

        sc_stop();
    }
};

#endif //ALU_TB_H