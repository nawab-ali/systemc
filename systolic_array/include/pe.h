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
    sc_in_clk clk;
    sc_in<int8_t> activation_in;
    sc_in<int32_t> partial_sum_in;
    sc_out<int8_t> activation_out;
    sc_out<int32_t> partial_sum_out;

    int8_t weight;

    SC_HAS_PROCESS(pe);

    pe(sc_module_name nm, int8_t w = 0) : sc_module(nm), weight(w) {
        SC_METHOD(mac);
        dont_initialize();
        sensitive << clk.pos();
    }

    // Multiply-and-Accumulate
    void mac() {
        int8_t activation = activation_in.read();
        int32_t partial_sum = partial_sum_in.read();

        partial_sum += activation * weight;

        activation_out.write(activation);
        partial_sum_out.write(partial_sum);
    }
};

#endif //PE_H