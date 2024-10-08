/**
 * @file three_eight_decoder.h
 * @brief This file implements a 3x8 Decoder.
 * @author Nawab Ali
 */

#ifndef THREE_EIGHT_DECODER_H
#define THREE_EIGHT_DECODER_H

#include "two_four_decoder.h"
#include <systemc.h>

SC_MODULE(three_eight_decoder) {
    sc_in<bool> enable;
    sc_in<sc_uint<3>> input;
    sc_out<sc_uint<8>> output;

    two_four_decoder decoder_2x4_1, decoder_2x4_2;
    sc_signal<bool> e1, e2;
    sc_signal<sc_uint<2>> i;
    sc_signal<sc_uint<4>> o1, o2;

    SC_CTOR(three_eight_decoder) : decoder_2x4_1("decoder_2x4_1"), decoder_2x4_2("decoder_2x4_2") {
        SC_METHOD(process_input);
        dont_initialize();
        sensitive << input;

        SC_METHOD(process_output);
        dont_initialize();
        sensitive << o1 << o2;

        decoder_2x4_1.enable(e1);
        decoder_2x4_1.input(i);
        decoder_2x4_1.output(o1);

        decoder_2x4_2.enable(e2);
        decoder_2x4_2.input(i);
        decoder_2x4_2.output(o2);
    }

    void process_input() {
        sc_uint<3> temp = input.read();

        e1.write(temp[2]);
        e2.write(~temp[2]);
        i.write(temp.range(1, 0));
    }

    void process_output() {
        sc_uint<8> temp;

        temp.range(3, 0) = o1;
        temp.range(7, 4) = o2;

        if (enable.read()) {
            output.write(temp);
        } else {
            output.write(0);
        }
    }
};

#endif // THREE_EIGHT_DECODER_H
