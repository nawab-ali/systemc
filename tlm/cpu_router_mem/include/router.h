/**
 * @file router.h
 * @brief This file implements a TLM interconnect (Router).
 * @author Nawab Ali
 */

#ifndef ROUTER_H
#define ROUTER_H

#include <tlm.h>
#include <systemc.h>
#include <tlm_utils/simple_initiator_socket.h>

using namespace std;

SC_MODULE (Router) {


    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_initiator_socket<Cpu> socket;

    SC_CTOR (Router) : socket("socket") {
        // Register callbacks for incoming interface method calls
        socket.register_invalidate_direct_mem_ptr(this, &Cpu::invalidate_direct_mem_ptr);

        trans = new tlm::tlm_generic_payload;
        SC_THREAD(generate_payload);
    }


    // Use transport interface for communicating with target





    ~Router() {
    }
};

#endif //ROUTER_H