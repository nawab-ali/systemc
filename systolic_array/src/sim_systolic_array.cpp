/**
 * @file sim_systolic_array.cpp
 * @brief This file simulates the Systolic Array.
 * @author Nawab Ali
 */

#include "systolic_array.h"
#include "systolic_array_tb.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <systemc.h>

const uint8_t N = 4;

sc_trace_file *create_vcd_trace(const char *file, sc_clock &clk, sc_vector<sc_signal<sc_int<8>>> &activation_in,
                                sc_vector<sc_signal<sc_int<32>>> &partial_sum_in,
                                sc_vector<sc_signal<sc_int<8>>> &activation_out,
                                sc_vector<sc_signal<sc_int<32>>> &partial_sum_out) {
    string name;
    sc_trace_file *fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, clk, "clk");

    for (int i = 0; i < N; ++i) {
        name = "activation_in_" + to_string(i);
        sc_trace(fp, activation_in[i], name.c_str());
        name = "partial_sum_in_" + to_string(i);
        sc_trace(fp, partial_sum_in[i], name.c_str());
        name = "activation_out_" + to_string(i);
        sc_trace(fp, activation_out[i], name.c_str());
        name = "partial_sum_out_" + to_string(i);
        sc_trace(fp, partial_sum_out[i], name.c_str());
    }

    return fp;
}

void simulate_systolic_array(const char *file) {
    sc_trace_file *fp;
    sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);

    sc_vector<sc_signal<sc_int<8>>> activation_in{"activation_in", N};
    sc_vector<sc_signal<sc_int<32>>> partial_sum_in{"partial_sum_in", N};
    sc_vector<sc_signal<sc_int<8>>> activation_out{"activation_out", N};
    sc_vector<sc_signal<sc_int<32>>> partial_sum_out{"partial_sum_out", N};

    systolic_array<N> sa("systolic_array");
    systolic_array_tb<N> sa_tb("systolic_array_tb");

    sa.clk(clk);
    sa_tb.clk(clk);

    // Link the Systolic Array with the test bench
    sa.activation_in(activation_in);
    sa.partial_sum_in(partial_sum_in);
    sa.activation_out(activation_out);
    sa.partial_sum_out(partial_sum_out);

    sa_tb.activation_in(activation_in);
    sa_tb.partial_sum_in(partial_sum_in);
    sa_tb.activation_out(activation_out);
    sa_tb.partial_sum_out(partial_sum_out);

    fp = create_vcd_trace(file, clk, activation_in, partial_sum_in, activation_out, partial_sum_out);

    SC_REPORT_INFO("sc_main", "Simulation starts");
    sc_start(1000, SC_NS);
    sc_close_vcd_trace_file(fp);
    SC_REPORT_INFO("sc_main", "Simulation ends");
}

int sc_main(int argc, char **argv) {
    const char *vcd_file = "systolic_array";
    const char *log_file = "systolic_array.log";

    srand(time(nullptr));
    sc_report_handler::set_log_file_name(log_file);
    sc_report_handler::set_actions("pe", SC_INFO, SC_LOG);
    sc_report_handler::set_actions("systolic_array", SC_INFO, SC_LOG);
    sc_report_handler::set_actions("systolic_array_tb", SC_INFO, SC_LOG);

    simulate_systolic_array(vcd_file);
    return 0;
}
