/**
 * @file two_four_decoder.h
 * @brief This file implements a 2x4 Decoder.
 * @author Nawab Ali
 */

#ifndef TWO_FOUR_DECODER_H
#define TWO_FOUR_DECODER_H

#include <systemc.h>

SC_MODULE (two_four_decoder) {
    sc_in<bool> enable;
    sc_in<sc_uint<2>> input;
    sc_out<sc_uint<4>> output;

    SC_CTOR (two_four_decoder) {
        SC_METHOD(decode);
        dont_initialize();
        sensitive << input << enable;
    }

    void decode() {
        if (enable.read()) {
            switch (input.read()) {
                case 0:
                    output.write(1);
                    break;
                case 1:
                    output.write(2);
                    break;
                case 2:
                    output.write(4);
                    break;
                case 3:
                    output.write(8);
                    break;
                default:
                    output.write(0);
            }
        } else {
            output.write(0);
        }
    }
};

#endif //TWO_FOUR_DECODER_H