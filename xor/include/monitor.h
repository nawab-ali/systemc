/**
 * @file monitor.h
 * @brief This file implements the Monitor module.
 * @author Nawab Ali
 */

#ifndef MONITOR_H
#define MONITOR_H

#include <iomanip>
#include <iostream>
#include <systemc.h>

using namespace std;

SC_MODULE (monitor) {
	sc_in<bool> clk;
	sc_in<bool> input_1;
	sc_in<bool> input_2;
	sc_in<bool> input_3;

	SC_CTOR (monitor) {
		SC_THREAD(monitor_dut);
		sensitive << clk.pos();
	}

	void monitor_dut(void) {
		cout << setw(10) << "Time\t";
	 	cout << setw(2) << "input_1\t";
		cout << setw(2) << "input_2\t";
	 	cout << setw(2) << "output" << endl;

		while (true) {
			cout << setw(10) << sc_time_stamp() << "\t";
		 	cout << setw(2) << input_1.read() << "\t";
			cout << setw(2) << input_2.read() << "\t";
		 	cout << setw(2) << input_3.read() << endl;
			wait();
		}
	}
};

#endif //MONITOR_H
