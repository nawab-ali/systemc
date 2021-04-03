/**
 * @file main.cpp
 * @brief This file implements the main thread of execution.
 * @author Nawab Ali
 */

#include "exor.h"
#include "monitor.h"
#include "stimulus.h"
#include <systemc.h>

int sc_main(int argc, char** argv) {
	sc_signal<bool> input_1;
	sc_signal<bool> input_2;
	sc_signal<bool> output;
	sc_clock clk("Clock", 10, SC_NS, 0.5, 1, SC_NS);

	stimulus stim("Stimulus");
	stim.clk(clk);
	stim.output_1(input_1);
	stim.output_2(input_2);

	exor DUT("Exor");
	DUT.input_1(input_1);
	DUT.input_2(input_2);
	DUT.output(output);

	monitor mon("Monitor");
	mon.clk(clk);
	mon.input_1(input_1);
	mon.input_2(input_2);
	mon.input_3(output);

	sc_start();

	return 0;
}
