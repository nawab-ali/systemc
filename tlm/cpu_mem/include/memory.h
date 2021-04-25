/**
 * @file memory.h
 * @brief This file implements a TLM target (memory).
 * @author Nawab Ali
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <tlm.h>
#include <systemc.h>
#include <tlm_utils/simple_target_socket.h>

enum {SIZE = 256};

SC_MODULE (Memory) {
    int mem[SIZE];
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<Memory> socket;
    
    SC_CTOR (Memory) : socket("socket") {
        // Register callback for incoming b_transport interface method call
        socket.register_b_transport(this, &Memory::b_transport);

        // Initialize memory with random data
        for (int i = 0; i < SIZE; ++i) {
            mem[i] = 0xAA000000 | (rand() % SIZE);
        }
    }

    // TLM-2 blocking transport method
    virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {
        tlm::tlm_command cmd = trans.get_command();
        sc_dt::uint64 addr = trans.get_address() / 4;
        unsigned char* ptr = trans.get_data_ptr();
        unsigned int len = trans.get_data_length();
        unsigned char* byte = trans.get_byte_enable_ptr();
        unsigned int width = trans.get_streaming_width();

        if (addr >= sc_dt::uint64(SIZE) || byte != 0 || len > 4 || width < len) {
            SC_REPORT_ERROR("TLM-2", "Memory does not support given generic payload transaction");
        }

        if (cmd == tlm::TLM_READ_COMMAND) {
            memcpy(ptr, &mem[addr], len);
        } else if (cmd == tlm::TLM_WRITE_COMMAND) {
            memcpy(&mem[addr], ptr, len);
        } else {
            SC_REPORT_ERROR("TLM-2", "Memory does not support given command");
        }

        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }
};

#endif //MEMORY_H