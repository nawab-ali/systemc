/**
 * @file main.cpp
 * @brief This file simulates the Systolic Array.
 * @author Nawab Ali
 */

#include <systemc.h>
#include "pe.h"
#include "systolic_array_tb.h"

sc_trace_file* create_vcd_trace(const char* file, sc_clock& clk) {
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, clk, "clk");

    return fp;
}

void simulate_counter() {
    sc_trace_file* fp;
    sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);

    fp = create_vcd_trace("systolic_array", clk);
    sc_start(200, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate_counter();
    return 0;
}