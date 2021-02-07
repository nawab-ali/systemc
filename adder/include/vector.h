/**
 * @file vector.h
 * @brief This file implements vector2bits and bits2vector conversions.
 * @author Nawab Ali
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <systemc.h>

SC_MODULE (vector2bits) {
    sc_in<sc_lv<4>> input;
    sc_out<bool> o0, o1, o2, o3;

    SC_CTOR (vector2bits) {
        SC_METHOD(convert);
        sensitive << input;
    }

    void convert() {
        sc_lv<4> temp = input.read();

        o0 = temp[0].to_bool();
        o1 = temp[1].to_bool();
        o2 = temp[2].to_bool();
        o3 = temp[3].to_bool();
    }
};

SC_MODULE (bits2vector) {
    sc_in<bool> i0, i1, i2, i3;
    sc_out<sc_lv<4>> output;

    SC_CTOR (bits2vector) {
        SC_METHOD(convert);
        sensitive << i0 << i1 << i2 << i3;
    }

    void convert() {
        sc_lv<4> temp;

        temp[0] = i0;
        temp[1] = i1;
        temp[2] = i2;
        temp[3] = i3;

        output = temp;
    }
};

#endif //VECTOR_H