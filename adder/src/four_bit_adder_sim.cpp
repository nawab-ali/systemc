/**
 * @file four_bit_adder_sim.cpp
 * @brief This file simulates the 4-bit Adder.
 * @author Nawab Ali
 */

#include <systemc.h>
#include "four_bit_adder.h"
#include "four_bit_adder_tb.h"


sc_trace_file* create_vcd_trace(const char* file, sc_signal<bool> a[4], sc_signal<bool> b[4],
                                sc_signal<bool>& c_in, sc_signal<bool> sum[4], sc_signal<bool>& c_out) {
    char name[8];
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, c_in, "c_in");
    sc_trace(fp, c_out, "c_out");

    for (int i = 0; i < 4; ++i) {
        snprintf(name, 8, "%s%d", "a", i);
        sc_trace(fp, a[i], name);
        snprintf(name, 8, "%s%d", "b", i);
        sc_trace(fp, b[i], name);
        snprintf(name, 8, "%s%d", "sum", i);
        sc_trace(fp, sum[i], name);
    }

    return fp;
}

void simulate_four_bit_adder() {
    sc_trace_file* fp;
    sc_signal<bool> c_in, c_out;
    sc_signal<bool> a[4], b[4], sum[4];
    sc_clock clk("clk", 10, SC_NS, 0.5);

    four_bit_adder fb_adder("four_bit_adder");
    fb_adder.c_in(c_in);
    fb_adder.c_out(c_out);

    for (int i = 0; i < 4; ++i) {
        fb_adder.a[i](a[i]);
        fb_adder.b[i](b[i]);
        fb_adder.sum[i](sum[i]);
    }

    four_bit_adder_tb fb_adder_tb("four_bit_adder_testbench");
    fb_adder_tb.clk(clk);
    fb_adder_tb.c_in(c_in);

    for (int i = 0; i < 4; ++i) {
        fb_adder_tb.a[i](a[i]);
        fb_adder_tb.b[i](b[i]);
    }

    fp = create_vcd_trace("four_bit_adder", a, b, c_in, sum, c_out);
    sc_start(300, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate_four_bit_adder();
    return 0;
}