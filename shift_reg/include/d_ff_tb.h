/**
 * @file d_ff_tb.h
 * @brief This file implements the D Flip-Flop testbench.
 * @author Nawab Ali
 */

#ifndef D_FF_TB_H
#define D_FF_TB_H

#include <systemc.h>

SC_MODULE (d_ff_tb) {
    sc_in<bool> clk;
    sc_out<bool> din;

    SC_CTOR (d_ff_tb) {
        cout << "Constructing d_ff_tb " << name() << endl;
        SC_THREAD(generate_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void generate_stimuli() {
        wait();
        cout << "generate_stimuli: begin" << endl;

        din.write(1);
        wait(15, SC_NS);

        din.write(0);
        wait(15, SC_NS);

        din.write(0);
        wait(15, SC_NS);

        din.write(1);
        wait(15, SC_NS);

        cout << "generate_stimuli: end 1" << endl;
        sc_stop();
        cout << "generate_stimuli: end 2" << endl;
    }
};

#endif //D_FF_TB_H