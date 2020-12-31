/**
 * @file stimulus.h
 * @brief This file implements the stimuli to test the XOR gate.
 * @author Nawab Ali
 */

#ifndef STIMULUS_H
#define STIMULUS_H

#include <systemc.h>

SC_MODULE (stimulus) {
	sc_in<bool> clk;
	sc_out<bool> output_1;
	sc_out<bool> output_2;

	SC_CTOR (stimulus) {
		SC_THREAD(generate_stimuli);
		sensitive << clk.pos();
	}

	void generate_stimuli(void) {
		output_1.write(false);
		output_2.write(false);
		wait();

		output_1.write(false);
		output_2.write(true);
		wait();

		output_1.write(true);
		output_2.write(false);
		wait();

		output_1.write(true);
		output_2.write(true);
		wait();

		sc_stop();
	}
};

#endif //STIMULUS_H
