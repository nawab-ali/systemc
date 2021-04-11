/**
 * @file four_two_encoder_tb.h
 * @brief This file implements the testbench for the 4x2 Encoder.
 * @author Nawab Ali
 */

#ifndef FOUR_TWO_ENCODER_TB_H
#define FOUR_TWO_ENCODER_TB_H

#include <systemc.h>

SC_MODULE (four_two_encoder_tb) {
    sc_in<bool> clk;
    sc_out<bool> enable;
    sc_out<sc_uint<4>> input;

    SC_CTOR (four_two_encoder_tb) {
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

        enable.write(1);
        input.write(5);
        wait();

        sc_stop();
    }
};

#endif //FOUR_TWO_ENCODER_TB_H