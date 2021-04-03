/**
 * @file three_eight_decoder_tb.h
 * @brief This file implements the testbench for the 3x8 Decoder.
 * @author Nawab Ali
 */

#ifndef THREE_EIGHT_DECODER_TB_H
#define THREE_EIGHT_DECODER_TB_H

#include <systemc.h>

SC_MODULE (three_eight_decoder_tb) {
    sc_in<bool> clk;
    sc_out<bool> enable;
    sc_out<sc_uint<3>> input;

    SC_CTOR (three_eight_decoder_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        wait();

        enable.write(1);
        for (int i = 0; i < 8; ++i) {
            input.write(i);
            wait();
        }

        enable.write(0);
        for (int i = 0; i < 8; ++i) {
            input.write(i);
            wait();
        }

        sc_stop();
    }
};

#endif //THREE_EIGHT_DECODER_TB_H