/**
 * @file d_ff_sim.cpp
 * @brief This file simulates the D Flip-Flop.
 * @author Nawab Ali
 */

#include "d_ff.h"
#include "d_ff_tb.h"
#include <systemc.h>

sc_trace_file* create_vcd_trace(const char* file, sc_clock& clk, sc_signal<bool>& din, sc_signal<bool>& dout) {
    sc_trace_file *fp;

    fp = sc_create_vcd_trace_file(file);
    fp->set_time_unit(1, SC_NS);
    sc_trace(fp, clk, "clk");
    sc_trace(fp, din, "din");
    sc_trace(fp, dout, "dout");

    return fp;
}

void simulate() {
    sc_trace_file *fp;
    sc_signal<bool> din;
    sc_signal<bool> dout;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    d_ff d_ff_1("d_ff_1");
    d_ff_1.clk(clk);
    d_ff_1.din(din);
    d_ff_1.dout(dout);

    d_ff_tb d_ff_tb("d_ff_tb");
    d_ff_tb.clk(clk);
    d_ff_tb.din(din);

    fp = create_vcd_trace("d_ff", clk, din, dout);
    sc_start(500, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate();
    return 0;
}