/**
 * @file main.cpp
 * @brief This file simulates the ALU.
 * @author Nawab Ali
 */

#include <systemc.h>
#include "counter.h"
#include "counter_tb.h"

sc_trace_file* create_vcd_trace(const char* file, sc_clock& clk, sc_signal<bool>& reset, sc_signal<bool>& enable,
                                sc_signal<sc_uint<4>>& out) {
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, clk, "clk");
    sc_trace(fp, reset, "reset");
    sc_trace(fp, enable, "enable");
    sc_trace(fp, out, "counter");

    return fp;
}

void simulate_counter() {
    sc_trace_file* fp;
    sc_signal<bool> reset;
    sc_signal<bool> enable;
    sc_signal<sc_uint<4>> out;
    sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);

    counter c("counter");
    c.clk(clk);
    c.reset(reset);
    c.enable(enable);
    c.out(out);

    counter_tb c_tb("counter_testbench");
    c_tb.clk(clk);
    c_tb.reset(reset);
    c_tb.enable(enable);

    fp = create_vcd_trace("counter", clk, reset, enable, out);
    sc_start(200, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate_counter();
    return 0;
}