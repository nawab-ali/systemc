/**
 * @file alu_tb.h
 * @brief This file implements the testbench for the ALU.
 * @author Nawab Ali
 */

#ifndef ALU_TB_H
#define ALU_TB_H

#include "util.h"
#include <systemc.h>

SC_MODULE (alu_tb) {
public:
    sc_out<bool> reset;
    sc_out<sc_uint<4>> opcode;
    sc_out<sc_int<32>> operand1, operand2;
    sc_in<sc_int<32>> result;
    sc_in<bool> clk, carry, zero;

    SC_CTOR (alu_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

private:
    void gen_stimuli() {
        wait();

        // Test ALU ops
        for (int i = 0; i < 10; ++i) {
            sc_int<32> op1 = random(-100000, 100000);
            sc_int<32> op2 = random(-100000, 100000);

            reset.write(true);
            operand1.write(op1);
            operand2.write(op2);
            opcode.write(ops::AND);
            wait();
            sc_assert(result.read() == (op1 & op2));
        }

        sc_stop();
    }
};

#endif //ALU_TB_H