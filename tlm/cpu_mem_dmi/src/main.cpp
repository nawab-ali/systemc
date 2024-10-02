/**
 * @file main.cpp
 * @brief This file simulates the TLM transactions.
 * @author Nawab Ali
 */

#include "top.h"
#include <systemc.h>

#define SC_INCLUDE_DYNAMIC_PROCESSES

int sc_main(int argc, char **argv) {
    srand(time(nullptr));

    Top top("top");
    sc_start();

    return 0;
}
