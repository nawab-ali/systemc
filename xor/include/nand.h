/**
 * @file nand.h
 * @brief This file implements the NAND gate.
 * @author Nawab Ali
 */

#ifndef NAND_H
#define NAND_H

#include <systemc.h>

SC_MODULE (nand) {
	sc_in<bool> input_1;
	sc_in<bool> input_2;
	sc_out<bool> output;

	SC_CTOR (nand) {
		SC_METHOD(compute_nand);
		sensitive << input_1 << input_2;
	}

	void compute_nand(void) {
		output.write(!(input_1.read() && input_2.read()));
	}
};

#endif //NAND_H
