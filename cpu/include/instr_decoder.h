/**
 * @file instr_decoder.h
 * @brief This file implements the instruction decoder.
 * @author Nawab Ali
 */

#ifndef INSTR_DECODER
#define INSTR_DECODER

#include <sstream>
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
        stringstream stream;
        sc_uint<32> mask = 0xFF;

        sc_uint<32> i = instr.read();
        src1.write(i & mask);
        src2.write((i >> 8) & mask);
        dest.write((i >> 16) & mask);
        opcode.write((i >> 24) & mask);

        stream << name();
        stream << " - instr:0x" << hex << i;
        stream << " opcode:0x" << hex << static_cast<sc_uint<8>>((i >> 24) & mask);
        stream << " dest:0x" << hex << static_cast<sc_uint<8>>((i >> 16) & mask);
        stream << " src2:0x" << hex << static_cast<sc_uint<8>>((i >> 8) & mask);
        stream << " src1:0x" << hex << static_cast<sc_uint<8>>(i & mask);

        SC_REPORT_INFO("", stream.str().c_str());
    }
};

#endif // INSTR_DECODER