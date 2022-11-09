/**
 * @file memory_tb.h
 * @brief This file implements the memory module test bench.
 * @author Nawab Ali
 */

#ifndef MEMORY_TB
#define MEMORY_TB

#include <systemc.h>
#include "util.h"
#include "memory.h"

template<typename dtype, uint32_t size = 256, uint32_t addr_bits = 8>
SC_MODULE (memory_tb) {
public:
    sc_in<bool> clk;
    sc_out<bool> enable, cmd;
    sc_out<sc_uint<addr_bits>> address;
    sc_out<dtype> data_in;
    sc_in<dtype> data_out;

    SC_CTOR (memory_tb) {
        SC_THREAD(gen_stimuli);
        dont_initialize();
        sensitive << clk.pos();
    }

private:
    void gen_stimuli(void) {
        wait();

        for (int i = 0; i < 1000; i++) {
            dtype data = random(0, 1000);
            sc_uint<addr_bits> addr = random(0, pow(2, addr_bits));

            // Write to memory
            enable.write(true);
            cmd.write(WRITE);
            address.write(addr);
            data_in.write(data);
            wait();

            // Read from memory
            enable.write(true);
            cmd.write(READ);
            address.write(addr);

            sc_assert(data == data_out.read());
            wait();
        }

        wait();
        sc_stop();
    }
};

#endif // MEMORY_TB