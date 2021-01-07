/**
 * @file main.h
 * @brief This file implements the main thread of execution.
 * @author Nawab Ali
 */

#include "and.h"
#include "monitor.h"
#include "stimulus.h"
#include <systemc.h>

int sc_main(int argc, char** argv) {
    sc_signal<bool> input_signal_1;
    sc_signal<bool> input_signal_2;
    sc_signal<bool> output_signal;
    sc_clock clk("Clock", 10, SC_NS, 0.5, 1, SC_NS);

    stimulus stim("Stimulus");
    stim.clk(clk);
    stim.output_1(input_signal_1);
    stim.output_2(input_signal_2);

    and2 DUT("and");
    DUT.input_1(input_signal_1);
    DUT.input_2(input_signal_2);
    DUT.output(output_signal);

    monitor mon("Monitor");
    mon.clk(clk);
    mon.input_1(input_signal_1);
    mon.input_2(input_signal_2);
    mon.input_3(output_signal);

    sc_start();

    return 0;
}