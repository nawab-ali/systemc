/**
 * @file counter_tb.h
 * @brief This file implements the testbench for the Counter.
 * @author Nawab Ali
 */

#ifndef COUNTER_TB_H
#define COUNTER_TB_H

#include <systemc.h>

SC_MODULE (counter_tb) {
    sc_in<bool> clk;
    sc_out<bool> reset, enable;

    SC_CTOR (counter_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        for (int i = 0; i < 5; ++i) {
            wait();
            reset = 0;
            enable = 1;
        }

        wait();
        reset = 1;
        enable = 1;

        wait();

        sc_stop();
    }
};

#endif //COUNTER_TB_H