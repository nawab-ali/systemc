/**
 * @file sim_systolic_array.cpp
 * @brief This file simulates the Systolic Array.
 * @author Nawab Ali
 */

#include <ctime>
#include <cstdlib>
#include <systemc.h>
#include "systolic_array.h"
#include "systolic_array_tb.h"

sc_trace_file* create_vcd_trace(const char* file, sc_clock& clk) {
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, clk, "clk");

    return fp;
}

void simulate_systolic_array() {
    const uint8_t N = 3;
    sc_trace_file* fp;
    sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);

    sc_vector<sc_signal<sc_int<8>>> activation_in{"activation_in", N};
    sc_vector<sc_signal<sc_int<32>>> partial_sum_in{"partial_sum_in", N};
    sc_vector<sc_signal<sc_int<8>>> activation_out{"activation_out", N};
    sc_vector<sc_signal<sc_int<32>>> partial_sum_out{"partial_sum_out", N};

    systolic_array<N> sa("systolic_array");
    systolic_array_tb<N> sa_tb("systolic_array_tb");

    sa.clk(clk);
    sa_tb.clk(clk);

    // Link the systolic array with the test bench
    sa.activation_in(activation_in);
    sa.partial_sum_in(partial_sum_in);
    sa.activation_out(activation_out);
    sa.partial_sum_out(partial_sum_out);

    sa_tb.activation_in(activation_in);
    sa_tb.partial_sum_in(partial_sum_in);
    sa_tb.activation_out(activation_out);
    sa_tb.partial_sum_out(partial_sum_out);

    fp = create_vcd_trace("systolic_array", clk);
    sc_start(200, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    srand(time(nullptr));
    simulate_systolic_array();
    return 0;
}