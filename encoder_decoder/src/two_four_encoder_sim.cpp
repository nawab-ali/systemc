/**
 * @file two_four_encoder_sim.cpp
 * @brief This file simulates the 2x4 Encoder.
 * @author Nawab Ali
 */

#include <systemc.h>
#include "two_four_encoder.h"
#include "two_four_encoder_tb.h"

sc_trace_file* create_vcd_trace(const char* file, sc_signal<bool>& enable, sc_signal<sc_uint<4>>& input,
                                sc_signal<sc_uint<2>>& output) {
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, enable, "enable");
    sc_trace(fp, input, "input");
    sc_trace(fp, output, "output");

    return fp;
}

void simulate_two_four_encoder() {
    sc_trace_file* fp;
    sc_signal<bool> enable;
    sc_signal<sc_uint<4>> input;
    sc_signal<sc_uint<2>> output;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    two_four_encoder encoder_2x4("2x4_encoder");
    two_four_encoder_tb encoder_2x4_tb("2x4_encoder_testbench");

    encoder_2x4.enable(enable);
    encoder_2x4.input(input);
    encoder_2x4.output(output);

    encoder_2x4_tb.clk(clk);
    encoder_2x4_tb.enable(enable);
    encoder_2x4_tb.input(input);

    fp = create_vcd_trace("two_four_encoder", enable, input, output);
    sc_start(300, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate_two_four_encoder();
    return 0;
}