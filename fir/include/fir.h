/**
 * @file fir.h
 * @brief This file implements an N-order Finite Impulse Response (FIR) filter.
 * @author Nawab Ali
 */

#ifndef FIR_H
#define FIR_H

#include <iostream>
#include <systemc.h>

using namespace std;

template<unsigned int order, const double* coeff>
SC_MODULE (fir) {
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_in<double> sample;
    sc_out<double> result;

    double delay[order+1];

    SC_CTOR (fir) {
        SC_METHOD(process_signal);
        dont_initialize();
        sensitive << clk.pos();

        SC_METHOD(monitor);
        dont_initialize();
        sensitive << clk.pos();

        for (int i = 0; i <= order; ++i) {
            delay[i] = 0.0;
        }
    }

    void process_signal() {
        double sum = 0.0;
        delay[0] = sample.read();

        if (reset.read()) {
            sum = 0.0;
            for (int i = 0; i <= order; ++i) {
                delay[i] = 0.0;
            }
        } else {
            // Create a weighted sum of delay and coeff
            for (int i = 0; i <= order; ++i) {
                sum += delay[i] * coeff[i];
            }

            // Shift the delays to the right
            for (int i = order-1; i >= 0; --i) {
                delay[i+1] = delay[i];
            }
        }

        result.write(sum);
    }

    void monitor() {
        cout << "Timestamp:  " << sc_time_stamp() << "\tsample: " << sample.read() << "\tresult: " << result.read()
        << endl;
    }
};

#endif //FIR_H