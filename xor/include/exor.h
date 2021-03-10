/**
 * @file exor.h
 * @brief This file implements the XOR gate using 4 NAND gates.
 * @author Nawab Ali
 */

#ifndef EXOR_H
#define EXOR_H

#include "nand.h"
#include <systemc.h>

SC_MODULE (exor) {
	sc_in<bool> input_1;
	sc_in<bool> input_2;
	sc_out<bool> output;

	nand n1, n2, n3, n4;
	sc_signal<bool> s1, s2, s3;

	SC_CTOR (exor): n1("NAND1"), n2("NAND2"), n3("NAND3"), n4("NAND4") {
		n1.input_1(input_1);
		n1.input_2(input_2);
		n1.output(s1);

		n2.input_1(input_1);
		n2.input_2(s1);
		n2.output(s2);

		n3.input_1(s1);
		n3.input_2(input_2);
		n3.output(s3);

		n4.input_1(s2);
		n4.input_2(s3);
		n4.output(output);
	}
};

#endif //EXOR_H
