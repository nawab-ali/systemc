/**
 * @file alu.h
 * @brief This file implements a 4-bit ALU.
 * @author Nawab Ali
 */

#ifndef ALU_H
#define ALU_H

#include <iostream>
#include <systemc.h>

using namespace std;

SC_MODULE (alu) {
    sc_in<sc_uint<3>> opcode;
    sc_in<sc_uint<4>> op1, op2;
    sc_out<sc_uint<4> result;
    sc_out<bool> carry, zero;

    SC_CTOR (alu) {
        SC_METHOD(operate);
        dont_initialize();
        sensitive << op1 << op2 << opcode;
    }

    void operate() {
        sc_uint<5> temp;
        sc_uint<4> data1 = op1.read();
        
        switch (opcode.read()) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                break;
        }

    }
};

#endif //ALU_H