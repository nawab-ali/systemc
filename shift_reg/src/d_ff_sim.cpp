/**
 * @file d_ff_sim.cpp
 * @brief This file simulates the D Flip-Flop.
 * @author Nawab Ali
 */

#include "d_ff.h"
#include <iostream>
#include <systemc.h>

using namespace std;

sc_trace_file* create_vcd_trace(const char* file, sc_signal<bool>& clk, sc_signal<bool>& din, sc_signal<bool>& dout) {
    sc_trace_file *fp;

    fp = sc_create_vcd_trace_file(file);
    fp->set_time_unit(1, SC_NS);
    sc_trace(fp, clk, "clk");
    sc_trace(fp, din, "din");
    sc_trace(fp, dout, "dout");

    return fp;
}

void simulate(sc_signal<bool>& din) {
    din = false;
    sc_start(31, SC_NS);
    cout << "din = " << din << " time = " << sc_time_stamp() << endl;

    din = true;
    sc_start(31, SC_NS);
    cout << "din = " << din << " time = " << sc_time_stamp() << endl;

    din = false;
    sc_start(31, SC_NS);
    cout << "din = " << din << " time = " << sc_time_stamp() << endl;
}

int sc_main(int argc, char** argv) {
    sc_trace_file *fp;
    sc_signal<bool> din;
    sc_signal<bool> dout;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    d_ff d_ff_1("d_ff_1");
    d_ff_1.clk(clk);
    d_ff_1.din(din);
    d_ff_1.dout(dout);

    fp = create_vcd_trace("d_ff", clk, din, dout);
    simulate(din);

    sc_stop();
    sc_close_vcd_trace_file(fp);

    return 0;
}