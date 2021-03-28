/**
 * @file four_bit_adder_sim.cpp
 * @brief This file simulates the 4-bit Adder.
 * @author Nawab Ali
 */

#include <systemc.h>
#include "four_bit_adder.h"
#include "four_bit_adder_tb.h"

sc_trace_file* create_vcd_trace(const char* file, sc_signal<bool>& c_in, sc_signal<sc_uint<4>>& a,
                                sc_signal<sc_uint<4>>& b, sc_signal<sc_uint<4>>& sum, sc_signal<bool>& c_out) {
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, c_in, "c_in");
    sc_trace(fp, a, "a");
    sc_trace(fp, b, "b");
    sc_trace(fp, sum, "sum");
    sc_trace(fp, c_out, "c_out");

    return fp;
}

void simulate_four_bit_adder() {
    sc_trace_file* fp;
    sc_signal<bool> c_in, c_out;
    sc_signal<sc_uint<4>> a, b, sum;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    four_bit_adder fb_adder("four_bit_adder");
    fb_adder.c_in(c_in);
    fb_adder.a(a);
    fb_adder.b(b);
    fb_adder.sum(sum);
    fb_adder.c_out(c_out);

    four_bit_adder_tb fb_adder_tb("four_bit_adder_testbench");
    fb_adder_tb.clk(clk);
    fb_adder_tb.c_in(c_in);
    fb_adder_tb.a(a);
    fb_adder_tb.b(b);

    fp = create_vcd_trace("four_bit_adder", c_in, a, b, sum, c_out);
    sc_start(300, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate_four_bit_adder();
    return 0;
}