/**
 * @file sim_memory.cpp
 * @brief This file simulates the memory module test bench.
 * @author Nawab Ali
 */

#include <ctime>
#include <cstdlib>
#include <systemc.h>
#include "memory.h"
#include "memory_tb.h"

void simulate_memory(void) {
    sc_signal<bool> enable, cmd;
    sc_signal<sc_uint<10>> address;
    sc_signal<sc_uint<32>> data_in;
    sc_signal<sc_uint<32>> data_out;
    sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);
    
    memory<sc_uint<32>, 1024, 10> mem("memory0");
    mem.clk(clk);
    mem.enable(enable);
    mem.cmd(cmd);
    mem.address(address);
    mem.data_in(data_in);
    mem.data_out(data_out);

    memory_tb<sc_uint<32>, 1024, 10> mem_tb("memory_tb0");
    mem_tb.clk(clk);
    mem_tb.enable(enable);
    mem_tb.cmd(cmd);
    mem_tb.address(address);
    mem_tb.data_in(data_in);
    mem_tb.data_out(data_out);

    SC_REPORT_INFO("sc_main", "Simulation starts");
    sc_start(10000, SC_NS);
    SC_REPORT_INFO("sc_main", "Simulation ends");
}

int sc_main(int argc, char** argv) {
    srand(time(nullptr));
    sc_report_handler::set_log_file_name("memory.log");
    sc_report_handler::set_actions("memory", SC_INFO, SC_LOG);
    simulate_memory();
    return 0;
}