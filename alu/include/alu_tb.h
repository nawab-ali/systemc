/**
 * @file alu_tb.h
 * @brief This file implements the testbench for the ALU.
 * @author Nawab Ali
 */

#ifndef ALU_TB_H
#define ALU_TB_H

#include <systemc.h>

SC_MODULE (alu_tb) {
    sc_in<bool> clk;
    sc_out<sc_uint<3>> opcode;
    sc_out<sc_uint<4>> operand1, operand2;

    SC_CTOR (alu_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

    void gen_stimuli() {
        wait();

        for (int i = 0; i < 8; ++i) {
            opcode.write(i);
            operand1.write(3);
            operand2.write(3);
            wait();
        }

        sc_stop();
    }
};

#endif //ALU_TB_H