/**
 * @file instr_decoder_tb.h
 * @brief This file implements the instruction decoder test bench.
 * @author Nawab Ali
 */

#ifndef INSTR_DECODER_TB
#define INSTR_DECODER_TB

#include <systemc.h>
#include "util.h"
#include "instr_decoder.h"

// Test bench for the instruction decoder module
// instr = [opcode|dest|src2|src1]
SC_MODULE (instr_decoder_tb) {
public:
    sc_out<sc_uint<32>> instr;
    sc_in<sc_uint<8>> opcode, dest, src2, src1;
    
    SC_CTOR (instr_decoder_tb) {
        SC_THREAD(gen_stimuli);
    }

private:
    void gen_stimuli(void) {
        sc_uint<32> mask = 0xFF;
        
        for (int j = 0; j < 5; j++) {
            sc_uint<32> i = random(0, 1000000000);

            instr.write(i);
            wait(1, SC_NS);
            sc_assert(opcode.read() == ((i >> 24) & mask));
            sc_assert(dest.read() == ((i >> 16) & mask));
            sc_assert(src2.read() == ((i >> 8) & mask));
            sc_assert(src1.read() == (i & mask));
        }
        sc_stop();
    }
};

#endif // INSTR_DECODER_TB