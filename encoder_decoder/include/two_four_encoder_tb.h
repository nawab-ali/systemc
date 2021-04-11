/**
 * @file two_four_encoder_tb.h
 * @brief This file implements the testbench for the 2x4 Encoder.
 * @author Nawab Ali
 */

#ifndef TWO_FOUR_ENCODER_TB_H
#define TWO_FOUR_ENCODER_TB_H

#include <systemc.h>

SC_MODULE (two_four_encoder_tb) {
    sc_in<bool> clk;
    sc_out<bool> enable;
    sc_out<sc_uint<4>> input;

    SC_CTOR (two_four_encoder_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        wait();

        enable.write(1);
        for (int i = 0; i < 4; ++i) {
            input.write(1 << i);
            wait();
        }

        enable.write(0);
        for (int i = 0; i < 4; ++i) {
            input.write(1 << i);
            wait();
        }

        sc_stop();
    }
};

#endif //TWO_FOUR_ENCODER_TB_H