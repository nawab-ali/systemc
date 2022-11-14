/**
 * @file memory.h
 * @brief This file implements the memory module.
 * @author Nawab Ali
 */

#ifndef MEMORY
#define MEMORY

#include <vector>
#include <sstream>
#include <systemc.h>

using namespace std;

enum memops{READ, WRITE};

template<typename dtype, uint32_t size = 256, uint32_t addr_bits = 8>
SC_MODULE (memory) {
public:
    sc_in<bool> clk, enable, cmd;
    sc_in<sc_uint<addr_bits>> address;
    sc_in<dtype> data_in;
    sc_out<dtype> data_out;

    SC_CTOR (memory) : data(size, 0) {
        SC_METHOD(process_cmd);
        dont_initialize();
        sensitive << clk.pos();
    }

    ~memory() {
        data.clear();
        data.shrink_to_fit();
    }

private:
    vector<dtype> data;

    // Log operation
    void log(void) {
        stringstream stream;
        sc_uint<addr_bits> addr = address.read();

        stream << name();
        stream << " - cmd:" << cmd.read();
        stream << " address:0x" << hex << addr;
        stream << " data:0x" << hex << data[addr];

        SC_REPORT_INFO("", stream.str().c_str());
    }

    // Process memory command
    void process_cmd(void) {
        if (enable.read()) {
            sc_uint<addr_bits> addr = address.read();
            sc_assert(addr >= 0 && addr < size);

            if (cmd.read() == memops::WRITE) {
                data[addr] = data_in.read();
            } else {
                data_out.write(data[addr]);
            }

            // Log operation
            log();
        }
    }
};

#endif //MEMORY