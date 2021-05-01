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
    tlm::tlm_generic_payload* trans;
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_initiator_socket<Cpu> socket;

    SC_CTOR (Cpu) : socket("socket") {
        trans = new tlm::tlm_generic_payload;
        SC_THREAD(generate_payload);
    }

    void generate_payload() {
        sc_time delay = sc_time(10, SC_NS);

        // Generate a random sequence of reads and writes
        for (int i = 32; i < 96; i += 4) {
            tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);

            if (cmd == tlm::TLM_WRITE_COMMAND) {
                data = 0xFF000000 | i;
            }

            trans->set_command(cmd);
            trans->set_address(i);
            trans->set_data_ptr(reinterpret_cast<unsigned char*>(&data));
            trans->set_data_length(4);
            trans->set_streaming_width(4);
            trans->set_byte_enable_ptr(0);
            trans->set_dmi_allowed(false);
            trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

            socket->b_transport(*trans, delay);

            if (trans->is_response_error()) {
                SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
            }

            cout << "trans = {" << (cmd ? 'W' : 'R') << ", " << hex << i << "} data = " << hex << data << " at time "
                 << sc_time_stamp() << " delay = " << delay << endl;

            wait(delay);
        }
    }

    ~Cpu() {
        delete trans;
    }
};

#endif //CPU_H