/**
 * @file fir_tb.h
 * @brief This file implements the testbench for the FIR filter.
 * @author Nawab Ali
 */

#ifndef FIR_TB_H
#define FIR_TB_H

#include <iostream>
#include <systemc.h>

using namespace std;

SC_MODULE (fir_tb) {
    sc_in<bool> clk;
    sc_in<double> result;
    sc_out<bool> reset;
    sc_out<double> sample;

    SC_CTOR (fir_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        const int num_samples = 16;
        double samples[num_samples] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
        double results[num_samples] = {0.0, -0.07556556070608, 0.09129209297815, 0.47697917208036, 0.47697917208036,
                                       0.09129209297815, -0.07556556070608, 0.0, 0.0, -0.07556556070608,
                                       0.01572653227208, 0.49270570435244, 0.96968487643279, 1.06097696941095,
                                       0.98541140870487, 0.98541140870487};

        wait();
        reset.write(true);
        sample.write(1.0);

        wait();
        for (int i = 0; i < num_samples; ++i) {
            reset.write(false);
            sample.write(samples[i]);
            wait();
        }

        sc_stop();
    }
};

#endif //FIR_TB_H