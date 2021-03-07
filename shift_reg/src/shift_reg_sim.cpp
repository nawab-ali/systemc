/**
 * @file shift_reg_sim.cpp
 * @brief This file simulates the 4-bit shift register.
 * @author Nawab Ali
 */

#include "shift_reg.h"
#include "shift_reg_tb.h"

sc_trace_file* create_vcd_trace(const char* file, sc_signal<bool>& clk, sc_signal<bool>& din, sc_signal<bool>& r0,
                                sc_signal<bool>& r1, sc_signal<bool>& r2, sc_signal<bool>& r3) {
    cout << "create_vcd_trace: begin" << endl;

    sc_trace_file* fp = sc_create_vcd_trace_file(file);
    fp->set_time_unit(1, SC_NS);

    sc_trace(fp, clk, "clk");
    sc_trace(fp, din, "din");
    sc_trace(fp, r0, "r0");
    sc_trace(fp, r1, "r1");
    sc_trace(fp, r2, "r2");
    sc_trace(fp, r3, "r3");

    cout << "create_vcd_trace: end" << endl;
    return fp;
}

void simulate_shift_reg() {
    sc_trace_file* fp;
    sc_signal<bool> din;
    sc_signal<bool> r0, r1, r2, r3;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    cout << "simulate_shift_reg: begin" << endl;

    shift_reg sr("shift_register");
    shift_reg_tb sr_tb("shift_register_testbench");

    sr.clk(clk);
    sr.din(din);
    sr.r0(r0);
    sr.r1(r1);
    sr.r2(r2);
    sr.r3(r3);

    sr_tb.clk(clk);
    sr_tb.din(din);

    cout << "simulate_shift_reg: end 1" << endl;
    fp = create_vcd_trace("shift_reg", clk, din, r0, r1, r2, r3);
    sc_start(200, SC_NS);
    sc_close_vcd_trace_file(fp);

    cout << "simulate_shift_reg: end" << endl;
}

int sc_main(int argc, char** argv) {
    simulate_shift_reg();
    return 0;
}