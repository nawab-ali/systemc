/**
 * @file four_two_encoder_sim.cpp
 * @brief This file simulates the 4x2 Encoder.
 * @author Nawab Ali
 */

#include "four_two_encoder.h"
#include "four_two_encoder_tb.h"
#include <systemc.h>

sc_trace_file *create_vcd_trace(const char *file, sc_signal<bool> &enable, sc_signal<sc_uint<4>> &input,
                                sc_signal<sc_uint<2>> &output) {
    sc_trace_file *fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, enable, "enable");
    sc_trace(fp, input, "input");
    sc_trace(fp, output, "output");

    return fp;
}

void simulate_four_two_encoder() {
    sc_trace_file *fp;
    sc_signal<bool> enable;
    sc_signal<sc_uint<4>> input;
    sc_signal<sc_uint<2>> output;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    four_two_encoder encoder_4x2("4x2_encoder");
    four_two_encoder_tb encoder_4x2_tb("4x2_encoder_testbench");

    encoder_4x2.enable(enable);
    encoder_4x2.input(input);
    encoder_4x2.output(output);

    encoder_4x2_tb.clk(clk);
    encoder_4x2_tb.enable(enable);
    encoder_4x2_tb.input(input);

    fp = create_vcd_trace("four_two_encoder", enable, input, output);
    sc_start(300, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char **argv) {
    simulate_four_two_encoder();
    return 0;
}
