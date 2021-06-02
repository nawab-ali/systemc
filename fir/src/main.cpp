/**
 * @file main.cpp
 * @brief This file simulates an N-order FIR filter.
 * @author Nawab Ali
 */

#include "fir.h"
#include "fir_tb.h"
#include <systemc.h>

const unsigned int order = 5;
const double coeff[order+1] = {-0.07556556070608, 0.09129209297815, 0.47697917208036,
                               0.47697917208036, 0.09129209297815, -0.07556556070608};

sc_trace_file* create_vcd_trace(const char* file, sc_clock& clk, sc_signal<bool>& reset, sc_signal<double>& sample,
                                sc_signal<double>& result) {
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, clk, "clk");
    sc_trace(fp, reset, "reset");
    sc_trace(fp, sample, "sample");
    sc_trace(fp, result, "result");

    return fp;
}

void simulate_fir() {
    sc_trace_file* fp;
    sc_signal<bool> reset;
    sc_signal<double> sample;
    sc_signal<double> result;
    sc_clock clk("clk", 10, SC_NS, 0.5, 1, SC_NS);

    fir<order, coeff> fir0("fir0");
    fir_tb fir_tb0("fir_tb0");

    fir0.clk(clk);
    fir0.reset(reset);
    fir0.sample(sample);
    fir0.result(result);

    fir_tb0.clk(clk);
    fir_tb0.reset(reset);
    fir_tb0.sample(sample);
    fir_tb0.result(result);

    fp = create_vcd_trace("fir", clk, reset, sample, result);
    sc_start(200, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate_fir();
    return 0;
}