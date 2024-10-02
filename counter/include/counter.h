/**
 * @file counter.h
 * @brief This file implements a 4-bit up-counter with synchronous active high
 * reset and active high enable signal.
 * @author Nawab Ali
 */

#ifndef COUNTER_H
#define COUNTER_H

#include <iostream>
#include <systemc.h>

using namespace std;

SC_MODULE(counter) {
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_in<bool> enable;
    sc_out<sc_uint<4>> out;

    sc_uint<4> count;

    SC_CTOR(counter) {
        SC_METHOD(incr_count);
        dont_initialize();
        sensitive << clk.pos() << reset;

        SC_METHOD(monitor);
        dont_initialize();
        sensitive << out;
    }

    void incr_count() {
        if (reset.read()) {
            count = 0;
        } else if (enable.read()) {
            count++;
        }
        out.write(count);
    }

    void monitor() { cout << "Timestamp: " << sc_time_stamp() << " Counter: " << out.read() << endl; }
};

#endif // COUNTER_H
