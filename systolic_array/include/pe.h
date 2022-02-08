/**
 * @file pe.h
 * @brief This file implements the Processing Element of a Systolic Array.
 * @author Nawab Ali
 */

#ifndef PE_H
#define PE_H

#include <string>
#include <systemc.h>

using namespace std;

SC_MODULE (pe) {
public:
    sc_in<bool> clk;
    sc_in<sc_int<8>> activation_in;
    sc_in<sc_int<32>> partial_sum_in;
    sc_out<sc_int<8>> activation_out;
    sc_out<sc_int<32>> partial_sum_out;

    SC_CTOR (pe) : weight(0) {
        SC_METHOD(mac);
        dont_initialize();
        sensitive << clk.pos();
    }

    void set_weight(const sc_int<8>& w) {
        weight = w;
    }

    sc_int<8> get_weight() {
        return weight;
    }

private:
    sc_int<8> weight;

    // Multiply-and-Accumulate
    void mac() {
        sc_int<8> activation = activation_in.read();
        sc_int<32> partial_sum = partial_sum_in.read();
        string log = string(name()) + " a_in:" + to_string(activation) + " p_in:" + to_string(partial_sum)
                     + " w:" + to_string(weight);

        partial_sum += activation * weight;
        activation_out.write(activation);
        partial_sum_out.write(partial_sum);

        log += " p_out:" + to_string(partial_sum);
        SC_REPORT_INFO("pe", log.c_str());
    }
};

#endif //PE_H