/**
 * @file router.h
 * @brief This file implements a TLM interconnect (Router).
 * @author Nawab Ali
 */

#ifndef ROUTER_H
#define ROUTER_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

const unsigned int size = 16;

template <unsigned int num_targets> SC_MODULE(Router) {
    // TLM-2 socket, defaults to 32-bits wide, base protocol
    tlm_utils::simple_target_socket<Router> target_socket;
    tlm_utils::simple_initiator_socket_tagged<Router> *initiator_socket[num_targets];

    SC_CTOR(Router) : target_socket("target_socket") {
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

    // TLM-2 blocking transport method
    virtual void b_transport(tlm::tlm_generic_payload & trans, sc_time & delay) {
        sc_dt::uint64 masked_address;
        sc_dt::uint64 address = trans.get_address();
        unsigned int target = decode_address(address, masked_address);

        // Modify address within transaction
        trans.set_address(masked_address);

        // Forward transaction to appropriate target
        (*initiator_socket[target])->b_transport(trans, delay);
    }

    // TLM-2 forward DMI method
    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload & trans, tlm::tlm_dmi & dmi_data) {
        sc_dt::uint64 masked_address;
        sc_dt::uint64 address = trans.get_address();
        sc_dt::uint64 dmi_start_address = dmi_data.get_start_address();
        sc_dt::uint64 dmi_end_address = dmi_data.get_end_address();
        unsigned int target = decode_address(address, masked_address);

        trans.set_address(masked_address);
        bool status = (*initiator_socket[target])->get_direct_mem_ptr(trans, dmi_data);

        // Calculate DMI address of target in system address space
        dmi_data.set_start_address(encode_address(target, dmi_start_address));
        dmi_data.set_end_address(encode_address(target, dmi_end_address));

        return status;
    }

    virtual void invalidate_direct_mem_ptr(int id, sc_dt::uint64 start_range, sc_dt::uint64 end_range) {
        // Reconstruct address range in system memory map
        sc_dt::uint64 bw_start_range = encode_address(id, start_range);
        sc_dt::uint64 bw_end_range = encode_address(id, end_range);

        target_socket->invalidate_direct_mem_ptr(bw_start_range, bw_end_range);
    }

    // Simple fixed address decoding
    inline unsigned int decode_address(sc_dt::uint64 & address, sc_dt::uint64 & masked_address) {
        unsigned int target = static_cast<unsigned int>((address >> 8) & 0x3);
        masked_address = address & 0xFF;
        return target;
    }

    inline unsigned int encode_address(unsigned int target, sc_dt::uint64 &address) {
        return (target << 8) | (address & 0xFF);
    }

    ~Router() {
        for (int i = 0; i < num_targets; ++i) {
            delete initiator_socket[i];
        }
    }
};

#endif // ROUTER_H
