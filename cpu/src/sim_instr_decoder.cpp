/**
 * @file sim_instr_decoder.cpp
 * @brief This file simulates the instruction decoder test bench.
 * @author Nawab Ali
 */

#include <ctime>
#include <cstdlib>
#include <systemc.h>
#include "instr_decoder.h"
#include "instr_decoder_tb.h"

void simulate_instr_decoder(void) {
    sc_signal<sc_uint<32>> instr;
    sc_signal<sc_uint<8>> opcode, dest, src2, src1;
    
    instr_decoder id("instr_decoder0");
    id.instr(instr);
    id.opcode(opcode);
    id.dest(dest);
    id.src2(src2);
    id.src1(src1);

    instr_decoder_tb id_tb("instr_decoder_tb0");
    id_tb.instr(instr);
    id_tb.opcode(opcode);
    id_tb.dest(dest);
    id_tb.src2(src2);
    id_tb.src1(src1);

    SC_REPORT_INFO("sc_main", "Simulation starts");
    sc_start(1000, SC_NS);
    SC_REPORT_INFO("sc_main", "Simulation ends");
}

int sc_main(int argc, char** argv) {
    srand(time(nullptr));
    sc_report_handler::set_log_file_name("instr_decoder.log");
    sc_report_handler::set_actions("instr_decoder", SC_INFO, SC_LOG);
    simulate_instr_decoder();
    return 0;
}