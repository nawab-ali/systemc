/**
 * @file three_eight_decoder.h
 * @brief This file implements a 3x8 Decoder.
 * @author Nawab Ali
 */

#ifndef THREE_EIGHT_DECODER_H
#define THREE_EIGHT_DECODER_H

#include <systemc.h>
#include "two_four_decoder.h"

SC_MODULE (three_eight_decoder) {
    sc_in<bool> enable;
    sc_in<sc_uint<3>> input;
    sc_out<sc_uint<8>> output;

    SC_CTOR (three_eight_decoder) {
        SC_METHOD(decode);
        dont_initialize();
        sensitive << input << enable;
    }

    void decode() {

    }
};

#endif //THREE_EIGHT_DECODER_H