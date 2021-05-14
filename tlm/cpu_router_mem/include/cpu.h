/**
 * @file cpu.h
 * @brief This file implements a TLM initiator (CPU).
 * @author Nawab Ali
 */

#ifndef CPU_H
#define CPU_H

#include <tlm.h>
#include <iostream>
#include <systemc.h>
#include <tlm_utils/simple_initiator_socket.h>

using namespace std;

SC_MODULE (Cpu) {
    int data;
    bool dmi_ptr_valid;
    tlm::tlm_dmi dmi_data;
    tlm::tlm_generic_payload* trans;

    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_initiator_socket<Cpu> socket;

    SC_CTOR (Cpu) : socket("socket"), dmi_ptr_valid(false) {
        // Register callbacks for incoming interface method calls
        socket.register_invalidate_direct_mem_ptr(this, &Cpu::invalidate_direct_mem_ptr);

        trans = new tlm::tlm_generic_payload;
        SC_THREAD(generate_payload);
    }

    void generate_payload() {
        sc_time delay = sc_time(10, SC_NS);

        // Generate a random sequence of reads and writes
        for (int i = 0; i < 128; i += 4) {
            tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);

            if (cmd == tlm::TLM_WRITE_COMMAND) {
                data = 0xFF000000 | i;
            }

            if (dmi_ptr_valid) {
                // Bypass transport interface and use direct memory interface
                comm_dmi(cmd, i);
            } else {
                comm_transport_interface(cmd, i, delay);
            }
        }
    }

    // Use transport interface for communicating with target
    void comm_transport_interface(tlm::tlm_command& cmd, int& i, sc_time& delay) {
        trans->set_command(cmd);
        trans->set_address(i);
        trans->set_data_ptr(reinterpret_cast<unsigned char*>(&data));
        trans->set_data_length(sizeof(data));
        trans->set_streaming_width(4);
        trans->set_byte_enable_ptr(0);
        trans->set_dmi_allowed(false);
        trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

        socket->b_transport(*trans, delay);

        // Check for errors from target
        if (trans->is_response_error()) {
            char txt[100];
            snprintf(txt, 100, "Error from b_transport, response status = %s",
                     trans->get_response_string().c_str());
            SC_REPORT_ERROR("TLM-2", txt);
        }

        // Check DMI hint
        if (trans->is_dmi_allowed()) {
            dmi_data.init();
            dmi_ptr_valid = socket->get_direct_mem_ptr(*trans, dmi_data);
        }

        cout << "trans = {" << (cmd ? 'W' : 'R') << ", " << hex << i << "} data = " << hex << data
             << " at time " << sc_time_stamp() << " delay = " << delay << endl;
    }

    // Use direct memory interface for communicating with target
    void comm_dmi(tlm::tlm_command& cmd, int& i) {
        if (cmd == tlm::TLM_READ_COMMAND) {
            assert(dmi_data.is_read_allowed());
            memcpy(&data, dmi_data.get_dmi_ptr() + i, sizeof(data));
            wait(dmi_data.get_read_latency());
        } else if (cmd == tlm::TLM_WRITE_COMMAND) {
            assert(dmi_data.is_write_allowed());
            memcpy(dmi_data.get_dmi_ptr() + i, &data, sizeof(data));
            wait(dmi_data.get_write_latency());
        } else {
            SC_REPORT_ERROR("TLM-2", "Memory does not support given command");
        }

        cout << "dmi   = {" << (cmd ? 'W' : 'R') << ", " << hex << i << "} , data = " << hex << data
             << " at time " << sc_time_stamp() << endl;
    }

    virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range) {
        // Ignore range and invalidate all DMI pointers
        dmi_ptr_valid = false;
    }

    ~Cpu() {
        delete trans;
    }
};

#endif //CPU_H