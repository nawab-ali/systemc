/**
 * @file pe_tb.h
 * @brief This file implements the testbench for the PE.
 * @author Nawab Ali
 */

#ifndef PE_TB_H
#define PE_TB_H

#include <systemc.h>

SC_MODULE (pe_tb) {
public:
    sc_in<bool> clk;
    sc_out<int8_t> activation_out;
    sc_out<int32_t> partial_sum_out;

    SC_CTOR (pe_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        wait();
        for (int i = 0; i < 10; ++i) {
            activation_out.write(7);
            partial_sum_out.write(8);
            wait();
        }
        sc_stop();
    }
};

#endif //PE_TB_H