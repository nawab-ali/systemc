/**
 * @file top.h
 * @brief This file connects the TLM initiator and target.
 * @author Nawab Ali
 */

#ifndef TOP_H
#define TOP_H

#include "cpu.h"
#include "memory.h"
#include "router.h"
#include <systemc.h>

SC_MODULE (Top) {
    Cpu* cpu;
    Router<4>* router;
    Memory* memory[4];

    SC_CTOR (Top) {
        cpu = new Cpu("cpu");
        router = new Router<4>("router");
        cpu->socket.bind(router->target_socket);

        for (int i = 0; i < 4; ++i) {
            char memory_id[size];
            snprintf(memory_id, size, "memory_%d", i);
            memory[i] = new Memory(memory_id);
            router->initiator_socket[i]->bind(memory[i]->socket);
        }
    }

    ~Top() {
        delete cpu;
        delete router;

        for (int i = 0; i < 4; ++i) {
            delete memory[i];
        }
    }
};

#endif //TOP_H