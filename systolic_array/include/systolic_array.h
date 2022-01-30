/**
 * @file systolic_array.h
 * @brief This file implements a Weight-stationary Systolic Array.
 * @author Nawab Ali
 */

#ifndef SYSTOLIC_ARRAY_H
#define SYSTOLIC_ARRAY_H

#include "pe.h"
#include "util.h"
#include <vector>
#include <systemc.h>

using namespace std;

template<uint8_t N>
SC_MODULE (systolic_array) {
public:
    sc_in<bool> clk;
    sc_vector<sc_in<sc_int<8>>> activation_in{"activation_in", N};
    sc_vector<sc_in<sc_int<32>>> partial_sum_in{"partial_sum_in", N};
    sc_vector<sc_out<sc_int<8>>> activation_out{"activation_out", N};
    sc_vector<sc_out<sc_int<32>>> partial_sum_out{"partial_sum_out", N};

    SC_CTOR (systolic_array) : pe_grid(N, vector<pe*>(N, nullptr)) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                char name[16];
                snprintf(name, 16, "PE_%d_%d", i, j);

                // Initialize PEs
                pe_grid[i][j] = new pe(name);
                pe_grid[i][j]->clk(clk);
                pe_grid[i][j]->set_weight(random(-128, 127));

                // Connect the PEs via signals
                if (i == 0 && j == 0) {
                    pe_grid[i][j]->activation_in(activation_in[i]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_in[j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else if (i == 0 && j == N-1) {
                    pe_grid[i][j]->activation_in(activation_s[i][j-1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_in[j]);
                    pe_grid[i][j]->activation_out(activation_out[i]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else if (i == N-1 && j == 0) {
                    pe_grid[i][j]->activation_in(activation_in[i]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i-1][j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_out[j]);
                } else if (i == N-1 && j == N-1) {
                    pe_grid[i][j]->activation_in(activation_s[i][j-1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i-1][j]);
                    pe_grid[i][j]->activation_out(activation_out[i]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_out[j]);
                } else if (i == 0) {
                    pe_grid[i][j]->activation_in(activation_s[i][j-1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_in[j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else if (j == 0) {
                    pe_grid[i][j]->activation_in(activation_in[i]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i-1][j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else if (i == N-1) {
                    pe_grid[i][j]->activation_in(activation_s[i][j-1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i-1][j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_out[j]);
                } else if (j == N-1) {
                    pe_grid[i][j]->activation_in(activation_s[i][j-1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i-1][j]);
                    pe_grid[i][j]->activation_out(activation_out[i]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else {
                    pe_grid[i][j]->activation_in(activation_s[i][j-1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i-1][j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                }
            }
        }
    }

    ~systolic_array() {
        for (auto& v : pe_grid) {
            for (auto& p : v) {
                delete p;
            }
        }
    }

private:
    vector<vector<pe *>> pe_grid;
    sc_signal<sc_int<8>> activation_s[N][N-1];
    sc_signal<sc_int<32>> partial_sum_s[N-1][N];
};

#endif //SYSTOLIC_ARRAY_H