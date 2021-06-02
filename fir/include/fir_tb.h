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
        wait();
        reset.write(false);
        sample.write(1.0);
        cout << sc_time_stamp << result.read() << endl;

        wait();

        sc_stop();
    }
};

#endif //FIR_TB_H