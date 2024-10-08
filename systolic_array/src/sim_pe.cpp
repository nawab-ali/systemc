/**
 * @file sim_pe.cpp
 * @brief This file simulates the PE.
 * @author Nawab Ali
 */

#include "pe.h"
#include "pe_tb.h"
#include <cstdlib>
#include <ctime>
#include <systemc.h>

sc_trace_file *create_vcd_trace(const char *file, sc_clock &clk, sc_signal<sc_int<8>> &activation_in,
                                sc_signal<sc_int<32>> &partial_sum_in, sc_signal<sc_int<8>> &activation_out,
                                sc_signal<sc_int<32>> &partial_sum_out) {
    sc_trace_file *fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, clk, "clk");
    sc_trace(fp, activation_in, "activation_in");
    sc_trace(fp, partial_sum_in, "partial_sum_in");
    sc_trace(fp, activation_out, "activation_out");
    sc_trace(fp, partial_sum_out, "partial_sum_out");

    return fp;
}

void simulate_pe(const sc_int<8> &weight, const char *file) {
    sc_trace_file *fp;
    sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);

    sc_signal<sc_int<8>> activation_in;
    sc_signal<sc_int<32>> partial_sum_in;
    sc_signal<sc_int<8>> activation_out;
    sc_signal<sc_int<32>> partial_sum_out;

    pe pe0("PE0");
    pe0.clk(clk);
    pe0.activation_in(activation_in);
    pe0.partial_sum_in(partial_sum_in);
    pe0.activation_out(activation_out);
    pe0.partial_sum_out(partial_sum_out);
    pe0.set_weight(weight);

    pe_tb<100> pe_tb0("PE_TB0");
    pe_tb0.clk(clk);
    pe_tb0.activation_out(activation_in);
    pe_tb0.partial_sum_out(partial_sum_in);
    pe_tb0.activation_in(activation_out);
    pe_tb0.partial_sum_in(partial_sum_out);
    pe_tb0.set_weight(weight);

    fp = create_vcd_trace(file, clk, activation_in, partial_sum_in, activation_out, partial_sum_out);

    SC_REPORT_INFO("sc_main", "Simulation starts");
    sc_start(200, SC_NS);
    sc_close_vcd_trace_file(fp);
    SC_REPORT_INFO("sc_main", "Simulation ends");
}

int sc_main(int argc, char **argv) {
    const sc_int<8> weight = 4;
    const char *vcd_file = "pe";
    const char *log_file = "pe.log";

    srand(time(nullptr));
    sc_report_handler::set_log_file_name(log_file);
    sc_report_handler::set_actions("pe", SC_INFO, SC_LOG);

    simulate_pe(weight, vcd_file);
    return 0;
}
