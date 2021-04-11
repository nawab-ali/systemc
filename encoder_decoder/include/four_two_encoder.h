/**
 * @file four_two_encoder.h
 * @brief This file implements a 4x2 Encoder.
 * @author Nawab Ali
 */

#ifndef FOUR_TWO_ENCODER_H
#define FOUR_TWO_ENCODER_H

#include <systemc.h>

SC_MODULE (four_two_encoder) {
    sc_in<bool> enable;
    sc_in<sc_uint<4>> input;
    sc_out<sc_uint<2>> output;

    SC_CTOR (four_two_encoder) {
        SC_METHOD(encode);
        dont_initialize();
        sensitive << input << enable;
    }

    void encode() {
        if (enable.read()) {
            switch (input.read()) {
                case 1:
                    output.write(0);
                    break;
                case 2:
                    output.write(1);
                    break;
                case 4:
                    output.write(2);
                    break;
                case 8:
                    output.write(3);
                    break;
                default:
                    output.write(NAN);
            }
        } else {
            output.write(NAN);
        }
    }
};

#endif //FOUR_TWO_ENCODER_H