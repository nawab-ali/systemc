/**
 * @file pe.h
 * @brief This file implements the Processing Element of a Systolic Array.
 * @author Nawab Ali
 */

#ifndef PE_H
#define PE_H

#include <systemc.h>

SC_MODULE (pe) {
public:
    sc_in<bool> clk;
    sc_in<sc_int<8>> activation_in;
    sc_in<sc_int<32>> partial_sum_in;
    sc_out<sc_int<8>> activation_out;
    sc_out<sc_int<32>> partial_sum_out;

    sc_int<8> weight;

    pe(sc_module_name nm, sc_int<8> w = 0) : sc_module(nm), weight(w) {
        SC_HAS_PROCESS(pe);
        SC_METHOD(mac);
        dont_initialize();
        sensitive << clk.pos();
    }

    // Multiply-and-Accumulate
    void mac() {
        sc_int<8> activation = activation_in.read();
        sc_int<32> partial_sum = partial_sum_in.read();

        partial_sum += activation * weight;

        activation_out.write(activation);
        partial_sum_out.write(partial_sum);
    }
};

#endif //PE_H