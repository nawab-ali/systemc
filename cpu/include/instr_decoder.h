/**
 * @file instr_decoder.h
 * @brief This file implements the instruction decoder.
 * @author Nawab Ali
 */

#ifndef INSTR_DECODER
#define INSTR_DECODER

#include <string>
#include <systemc.h>

using namespace std;

// Decode a 32-bit instruction and return the opcode, src, and destination registers
// instr = [opcode|dest|src2|src1]
SC_MODULE (instr_decoder) {
public:
    sc_in<sc_uint<32>> instr;
    sc_out<sc_uint<8>> opcode, dest, src2, src1;
    
    SC_CTOR (instr_decoder) {
        SC_METHOD(decode);
        dont_initialize();
        sensitive << instr;
    }

private:
    void decode(void) {
        sc_uint<32> mask = 0xFF;

        sc_uint<32> i = instr.read();
        src1.write(i & mask);
        src2.write((i >> 8) & mask);
        dest.write((i >> 16) & mask);
        opcode.write((i >> 24) & mask);
        
        string log = string(name()) +
                     " - instr:" + to_string(i) +
                     " opcode:" + to_string(static_cast<sc_uint<8>>((i >> 24) & mask)) +
                     " dest:" + to_string(static_cast<sc_uint<8>>((i >> 16) & mask)) +
                     " src2:" + to_string(static_cast<sc_uint<8>>((i >> 8) & mask)) +
                     " src1:" + to_string(static_cast<sc_uint<8>>(i & mask));
        SC_REPORT_INFO("", log.c_str());
    }
};

#endif // INSTR_DECODER