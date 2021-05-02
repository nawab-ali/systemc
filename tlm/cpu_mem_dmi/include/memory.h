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
    const sc_time latency;

    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<Memory> socket;
    
    SC_CTOR (Memory) : socket("socket"), latency(10, SC_NS) {
        // Register callbacks for incoming interface method calls
        socket.register_b_transport(this, &Memory::b_transport);
        socket.register_get_direct_mem_ptr(this, &Memory::get_direct_mem_ptr);

        // Initialize memory with random data
        for (int i = 0; i < SIZE; ++i) {
            mem[i] = 0xAA000000 | (rand() % SIZE);
        }

        SC_THREAD(invalidate_dmi_ptr);
    }

    // TLM-2 blocking transport method
    virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {
        tlm::tlm_response_status resp_status;
        tlm::tlm_command cmd = trans.get_command();
        sc_dt::uint64 addr = trans.get_address() / 4;
        unsigned char* ptr = trans.get_data_ptr();
        unsigned int len = trans.get_data_length();
        unsigned char* byte = trans.get_byte_enable_ptr();
        unsigned int width = trans.get_streaming_width();

        // Check transaction for errors
        resp_status = check_trans_error(addr, byte, len, width);
        trans.set_response_status(resp_status);
        if (resp_status != tlm::TLM_INCOMPLETE_RESPONSE) {
            return;
        }

        if (cmd == tlm::TLM_READ_COMMAND) {
            memcpy(ptr, &mem[addr], len);
        } else if (cmd == tlm::TLM_WRITE_COMMAND) {
            memcpy(&mem[addr], ptr, len);
        } else {
            SC_REPORT_ERROR("TLM-2", "Memory does not support given command");
        }

        // b_transport may block
        wait(delay);
        delay = SC_ZERO_TIME;

        trans.set_dmi_allowed(true);
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }

    // TLM-2 forward DMI method
    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data) {
        dmi_data.allow_read_write();
        dmi_data.set_dmi_ptr(reinterpret_cast<unsigned char*>(&mem[0]));
        dmi_data.set_start_address(0);
        dmi_data.set_end_address(SIZE*4 - 1);
        dmi_data.set_read_latency(latency);
        dmi_data.set_write_latency(latency);

        return true;
    }

    // Invalidate DMI pointers periodically
    void invalidate_dmi_ptr() {
        for (int i = 0; i < 4; ++i) {
            wait(latency * 8);
            socket->invalidate_direct_mem_ptr(0, SIZE-1);
        }
    }

    tlm::tlm_response_status check_trans_error(sc_dt::uint64& addr, unsigned char* byte, unsigned int& len,
                                               unsigned int& width) {
        if (addr >= sc_dt::uint64(SIZE)) {
            return tlm::TLM_ADDRESS_ERROR_RESPONSE;
        } else if (byte != 0) {
            return tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE;
        } else if (len > 4 || width < len) {
            return tlm::TLM_BURST_ERROR_RESPONSE;
        } else {
            return tlm::TLM_INCOMPLETE_RESPONSE;
        }
    }
};

#endif //MEMORY_H