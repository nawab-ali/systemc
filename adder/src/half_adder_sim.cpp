/**
 * @file half_adder_sim.cpp
 * @brief This file simulates the Half-Adder.
 * @author Nawab Ali
 */

#include <systemc.h>
#include "half_adder.h"
#include "half_adder_tb.h"

sc_trace_file* create_half_adder_vcd_trace(const char* file, sc_signal<bool>& a, sc_signal<bool>& b, sc_signal<bool>& sum, sc_signal<bool>& carry) {
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, a, "a");
    sc_trace(fp, b, "b");
    sc_trace(fp, sum, "sum");
    sc_trace(fp, carry, "carry");

    return fp;
}

void simulate_half_adder() {
    sc_trace_file* fp;
    sc_signal<bool> a, b;
    sc_signal<bool> sum, carry;

    half_adder ha("half_adder");
    ha.a(a);
    ha.b(b);
    ha.sum(sum);
    ha.carry(carry);

    half_adder_tb ha_tb("half_adder_testbench");
    ha_tb.a(a);
    ha_tb.b(b);

    fp = create_half_adder_vcd_trace("half_adder", a, b, sum, carry);
    sc_start(5, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate_half_adder();
    return 0;
}