/**
 * @file main.cpp
 * @brief This file simulates the ALU.
 * @author Nawab Ali
 */

#include "alu.h"
#include "alu_tb.h"
#include <systemc.h>

sc_trace_file *create_vcd_trace(const char *file, sc_clock &clk, sc_signal<sc_uint<3>> &opcode,
                                sc_signal<sc_uint<4>> &operand1, sc_signal<sc_uint<4>> &operand2,
                                sc_signal<sc_uint<4>> &result, sc_signal<bool> &carry, sc_signal<bool> &zero) {
    sc_trace_file *fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, clk, "clk");
    sc_trace(fp, opcode, "opcode");
    sc_trace(fp, operand1, "operand1");
    sc_trace(fp, operand2, "operand2");
    sc_trace(fp, result, "result");
    sc_trace(fp, carry, "carry");
    sc_trace(fp, zero, "zero");

    return fp;
}

void simulate_alu() {
    sc_trace_file *fp;
    sc_signal<sc_uint<3>> opcode;
    sc_signal<sc_uint<4>> operand1, operand2;
    sc_signal<sc_uint<4>> result;
    sc_signal<bool> carry, zero;

    sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);

    alu a("alu");
    a.opcode(opcode);
    a.operand1(operand1);
    a.operand2(operand2);
    a.result(result);
    a.carry(carry);
    a.zero(zero);

    alu_tb a_tb("alu_testbench");
    a_tb.clk(clk);
    a_tb.opcode(opcode);
    a_tb.operand1(operand1);
    a_tb.operand2(operand2);

    fp = create_vcd_trace("alu", clk, opcode, operand1, operand2, result, carry, zero);
    sc_start(300, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char **argv) {
    simulate_alu();
    return 0;
}
