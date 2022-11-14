/**
 * @file main.cpp
 * @brief This file simulates the ALU.
 * @author Nawab Ali
 */

#include <ctime>
#include <cstdlib>
#include <systemc.h>
#include "alu.h"
#include "alu_tb.h"

void simulate_alu() {
    sc_signal<sc_uint<4>> opcode;
    sc_signal<sc_int<32>> operand1, operand2, result;
    sc_signal<bool> carry, zero, reset;

    sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);

    alu a("alu");
    a.opcode(opcode);
    a.operand1(operand1);
    a.operand2(operand2);
    a.result(result);
    a.carry(carry);
    a.zero(zero);
    a.reset(reset);

    alu_tb a_tb("alu_testbench");
    a_tb.clk(clk);
    a_tb.opcode(opcode);
    a_tb.operand1(operand1);
    a_tb.operand2(operand2);
    a_tb.result(result);
    a_tb.carry(carry);
    a_tb.zero(zero);
    a_tb.reset(reset);

    sc_start(300, SC_NS);
}

int sc_main(int argc, char** argv) {
    srand(time(nullptr));
    sc_report_handler::set_log_file_name("alu.log");
    sc_report_handler::set_actions("alu", SC_INFO, SC_LOG);
    simulate_alu();
    return 0;
}