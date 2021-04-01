/**
 * @file two_four_decoder_sim.cpp
 * @brief This file simulates the 2x4 Decoder.
 * @author Nawab Ali
 */

#include <systemc.h>
#include "two_four_decoder.h"
#include "two_four_decoder_tb.h"

sc_trace_file* create_vcd_trace(const char* file, sc_signal<bool>& enable, sc_signal<sc_uint<2>>& input,
                                sc_signal<sc_uint<4>>& output) {
    sc_trace_file* fp = sc_create_vcd_trace_file(file);

    sc_trace(fp, enable, "enable");
    sc_trace(fp, input, "input");
    sc_trace(fp, output, "output");

    return fp;
}

void simulate_two_four_decoder() {
    sc_trace_file* fp;
    sc_signal<bool> enable;
    sc_signal<sc_uint<2>> input;
    sc_signal<sc_uint<4>> output;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    two_four_decoder decoder_2x4("2x4_decoder");
    two_four_decoder_tb decoder_2x4_tb("2x4_decoder_testbench");

    decoder_2x4.enable(enable);
    decoder_2x4.input(input);
    decoder_2x4.output(output);

    decoder_2x4_tb.clk(clk);
    decoder_2x4_tb.enable(enable);
    decoder_2x4_tb.input(input);

    fp = create_vcd_trace("two_four_decoder", enable, input, output);
    sc_start(300, SC_NS);
    sc_close_vcd_trace_file(fp);
}

int sc_main(int argc, char** argv) {
    simulate_two_four_decoder();
    return 0;
}