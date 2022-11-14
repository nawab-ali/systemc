/**
 * @file alu.h
 * @brief This file implements a 32-bit ALU.
 * @author Nawab Ali
 */

#ifndef ALU_H
#define ALU_H

#include <sstream>
#include <systemc.h>

using namespace std;

enum ops{AND, OR, XOR, NOT, CMP, ADD, SUB};

SC_MODULE (alu) {
public:
    sc_in<bool> reset;
    sc_in<sc_uint<4>> opcode;
    sc_in<sc_int<32>> operand1, operand2;
    sc_out<sc_int<32>> result;
    sc_out<bool> carry, zero;

    SC_CTOR (alu) {
        SC_METHOD(compute);
        dont_initialize();
        sensitive << operand1 << operand2 << opcode << reset;
    }

private:
    // Log ALU operation
    void log() {
        stringstream stream;

        stream << name();
        stream << " - opcode:0x" << hex << opcode.read();
        stream << " operand1:0x" << hex << operand1.read();
        stream << " operand2:0x" << hex << operand2.read();
        stream << " result:0x" << hex << result.read();
        stream << " carry:0x" << hex << carry.read();
        stream << " zero:0x" << hex << zero.read();
        stream << " reset:0x" << hex << reset.read();

        SC_REPORT_INFO("", stream.str().c_str());
    }

    // Compute ALU operations
    void compute() {
        sc_int<33> r = 0;
        sc_int<32> data1 = operand1.read();
        sc_int<32> data2 = operand2.read();

        // Reset carry and zero flags
        if (reset.read()) {
            zero.write(false);
            carry.write(false);
        }

        // ALU operations
        switch (opcode.read()) {
            case ops::AND:
                r = data1 & data2;
                break;
            case ops::OR:
                r = data1 | data2;
                break;
            case ops::XOR:
                r = data1 ^ data2;
                break;
            case ops::NOT:
                r = ~data1;
                break;
            case ops::CMP:
                if (data1 == data2) {
                    zero.write(true);
                    carry.write(false);
                } else if (data1 < data2) {
                    zero.write(false);
                    carry.write(true);
                } else {
                    zero.write(false);
                    carry.write(false);
                }
                break;
            case ops::ADD:
                r = data1 + data2;
                break;
            case ops::SUB:
                r = data1 - data2;
                break;
            default:
                throw invalid_argument("ERROR: Invalid operation");
                return;
        }

        result.write(r.range(31, 0));
        if (opcode.read() != ops::CMP) {
            if (!r) {
                zero.write(true);
            } else {
                zero.write(false);
            }
            carry.write(r[32]);
        }

        // Log operation
        log();
    }
};

#endif //ALU_H