/**
 * @file alu.h
 * @brief This file implements a 4-bit ALU.
 * @author Nawab Ali
 */

#ifndef ALU_H
#define ALU_H

#include <systemc.h>

enum Ops{ADD, SUBTRACT, INCR, DECR, AND, OR, NAND, XOR};

SC_MODULE (alu) {
    sc_in<sc_uint<3>> opcode;
    sc_in<sc_uint<4>> operand1, operand2;
    sc_out<sc_uint<4>> result;
    sc_out<bool> carry, zero;

    SC_CTOR (alu) {
        SC_METHOD(operate);
        dont_initialize();
        sensitive << operand1 << operand2 << opcode;
    }

    void operate() {
        sc_uint<5> r;
        sc_uint<4> data1 = operand1.read();
        sc_uint<4> data2 = operand2.read();

        zero.write(false);

        switch (opcode.read()) {
            case Ops::ADD:
                r = data1 + data2;
                break;
            case Ops::SUBTRACT:
                r = data1 - data2;
                break;
            case Ops::INCR:
                r = data1 + 1;
                break;
            case Ops::DECR:
                r = data1 - 1;
                break;
            case Ops::AND:
                r = data1 & data2;
                break;
            case Ops::OR:
                r = data1 | data2;
                break;
            case Ops::NAND:
                r = ~(data1 & data2);
                break;
            case Ops::XOR:
                r = data1 ^ data2;
                break;
            default:
                break;
        }

        result.write(r.range(3, 0));
        carry.write(r[4]);

        if (!r) {
            zero.write(true);
        }
    }
};

#endif //ALU_H