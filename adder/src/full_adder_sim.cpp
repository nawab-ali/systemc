/**
 * @file full_adder_sim.cpp
 * @brief This file simulates the Full-Adder.
 * @author Nawab Ali
 */

#include "full_adder.h"
#include "full_adder_tb.h"
#include <systemc.h>

sc_trace_file *create_vcd_trace(const char *file, sc_signal<bool> &a, sc_signal<bool> &b, sc_signal<bool> &c_in,
                                sc_signal<bool> &sum, sc_signal<bool> &c_out) {
    sc_trace_file *fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, a, "a");
    sc_trace(fp, b, "b");
    sc_trace(fp, c_in, "c_in");
    sc_trace(fp, sum, "sum");
    sc_trace(fp, c_out, "c_out");

    return fp;
}

void simulate_full_adder() {
    sc_trace_file *fp;
    sc_signal<bool> a, b, c_in;
    sc_signal<bool> sum, c_out;

    full_adder fa("full_adder");
    fa.a(a);
    fa.b(b);
    fa.c_in(c_in);
    fa.sum(sum);
    fa.c_out(c_out);

    full_adder_tb fa_tb("full_adder_testbench");
    fa_tb.a(a);
    fa_tb.b(b);
    fa_tb.c_in(c_in);

    fp = create_vcd_trace("full_adder", a, b, c_in, sum, c_out);
    sc_start(10, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char **argv) {
    simulate_full_adder();
    return 0;
}
