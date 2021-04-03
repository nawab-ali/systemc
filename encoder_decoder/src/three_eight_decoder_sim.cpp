/**
 * @file three_eight_decoder_sim.cpp
 * @brief This file simulates the 3x8 Decoder.
 * @author Nawab Ali
 */

#include <systemc.h>
#include "three_eight_decoder.h"
#include "three_eight_decoder_tb.h"

sc_trace_file* create_vcd_trace(const char* file, sc_signal<bool>& enable, sc_signal<sc_uint<3>>& input,
                                sc_signal<sc_uint<8>>& output) {
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, enable, "enable");
    sc_trace(fp, input, "input");
    sc_trace(fp, output, "output");

    return fp;
}

void simulate_three_eight_decoder() {
    sc_trace_file* fp;
    sc_signal<bool> enable;
    sc_signal<sc_uint<3>> input;
    sc_signal<sc_uint<8>> output;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    three_eight_decoder decoder_3x8("3x8_decoder");
    three_eight_decoder_tb decoder_3x8_tb("3x8_decoder_testbench");

    decoder_3x8.enable(enable);
    decoder_3x8.input(input);
    decoder_3x8.output(output);

    decoder_3x8_tb.clk(clk);
    decoder_3x8_tb.enable(enable);
    decoder_3x8_tb.input(input);

    fp = create_vcd_trace("three_eight_decoder", enable, input, output);
    sc_start(300, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate_three_eight_decoder();
    return 0;
}