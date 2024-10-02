/**
 * @file top.h
 * @brief This file connects the TLM initiator and target.
 * @author Nawab Ali
 */

#ifndef TOP_H
#define TOP_H

#include "cpu.h"
#include "memory.h"
#include <systemc.h>

SC_MODULE(Top) {
    Cpu *cpu;
    Memory *memory;

    SC_CTOR(Top) {
        cpu = new Cpu("cpu");
        memory = new Memory("memory");

        cpu->socket.bind(memory->socket);
    }

    ~Top() {
        delete cpu;
        delete memory;
    }
};

#endif // TOP_H
