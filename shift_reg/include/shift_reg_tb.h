/**
 * @file shift_reg_tb.h
 * @brief This file implements the 4-bit shift register testbench.
 * @author Nawab Ali
 */

#ifndef SHIFT_REG_TB_H
#define SHIFT_REG_TB_H

#include <systemc.h>

SC_MODULE (shift_reg_tb) {
    sc_in<bool> clk;
    sc_out<bool> din;

    SC_CTOR (shift_reg_tb) {
        cout << "Constructing shift_reg_tb " << name() << endl;
        SC_THREAD(generate_stimuli);
        sensitive << clk.pos();
    }

    void generate_stimuli() {
        wait();
        cout << "generate_stimuli: begin" << endl;

        din.write(1);
        wait();

        din.write(0);
        wait();

        din.write(1);
        wait();

        din.write(0);
        wait();

        cout << "generate_stimuli: end 1" << endl;
        sc_stop();
        cout << "generate_stimuli: end 2" << endl;
    }
};

#endif //SHIFT_REG_TB_H