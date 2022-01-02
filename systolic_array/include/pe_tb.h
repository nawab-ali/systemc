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
        const int num_samples = 10;
        int8_t activations[num_samples] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int32_t partial_sums[num_samples] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        wait();
        for (int i = 0; i < num_samples; ++i) {
            activation_out.write(activations[i]);
            partial_sum_out.write(partial_sums[i]);
            wait();
        }
        sc_stop();
    }
};

#endif //PE_TB_H