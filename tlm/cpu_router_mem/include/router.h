/**
 * @file router.h
 * @brief This file implements a TLM interconnect (Router).
 * @author Nawab Ali
 */

#ifndef ROUTER_H
#define ROUTER_H

#include <tlm.h>
#include <systemc.h>
#include <tlm_utils/simple_target_socket.h>
#include <tlm_utils/simple_initiator_socket.h>

const unsigned int size = 16;
const unsigned int num_targets = 4;

template <unsigned int num_targets>
SC_MODULE (Router) {
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<Router> target_socket;
    tlm_utils::simple_initiator_socket_tagged<Router>* initiator_socket[num_targets];

    SC_CTOR (Router) : target_socket("target_socket") {
        // Register callbacks for incoming interface method calls
        target_socket.register_b_transport(this, &Router::b_transport);
        target_socket.register_get_direct_mem_ptr(this, &Router::get_direct_mem_ptr);

        for (int i = 0; i < num_targets; ++i) {
            char socket_id[size];
            snprintf(socket_id, size, "socket_%d", i);
            initiator_socket[i] = new tlm_utils::simple_initiator_socket_tagged<Router>(socket_id);

            // Register callbacks for incoming interface method calls, including tags
            initiator_socket[i]->register_invalidate_direct_mem_ptr(this, &Router::invalidate_direct_mem_ptr, i);
        }
    }

    ~Router() {
        for (int i = 0; i < num_targets; ++i) {
            delete initiator_socket[i];
        }
    }
};

#endif //ROUTER_H