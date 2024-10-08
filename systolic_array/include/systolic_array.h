/**
 * @file systolic_array.h
 * @brief This file implements a Weight-stationary Systolic Array.
 * @author Nawab Ali
 */

#ifndef SYSTOLIC_ARRAY_H
#define SYSTOLIC_ARRAY_H

#include "pe.h"
#include "util.h"
#include <string>
#include <systemc.h>
#include <vector>

using namespace std;

template <uint8_t N> SC_MODULE(systolic_array) {
  public:
    sc_in<bool> clk;
    sc_vector<sc_in<sc_int<8>>> activation_in{"activation_in", N};
    sc_vector<sc_in<sc_int<32>>> partial_sum_in{"partial_sum_in", N};
    sc_vector<sc_out<sc_int<8>>> activation_out{"activation_out", N};
    sc_vector<sc_out<sc_int<32>>> partial_sum_out{"partial_sum_out", N};

    SC_CTOR(systolic_array) : pe_grid(N, vector<pe *>(N, nullptr)) {
        SC_METHOD(monitor);
        dont_initialize();
        sensitive << clk.pos();

        // Create a NxN Systolic Array
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                // Initialize PEs
                string name = "PE_" + to_string(i) + "_" + to_string(j);
                pe_grid[i][j] = new pe(name.c_str());
                pe_grid[i][j]->clk(clk);

                // The weight matrix should be transposed before being loaded in the systolic array.
                // I'm using random weights for now.
                pe_grid[i][j]->set_weight(random(-128, 127));

                // Connect the PEs via signals
                if (i == 0 && j == 0) {
                    pe_grid[i][j]->activation_in(activation_in[i]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_in[j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else if (i == 0 && j == N - 1) {
                    pe_grid[i][j]->activation_in(activation_s[i][j - 1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_in[j]);
                    pe_grid[i][j]->activation_out(activation_out[i]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else if (i == N - 1 && j == 0) {
                    pe_grid[i][j]->activation_in(activation_in[i]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i - 1][j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_out[j]);
                } else if (i == N - 1 && j == N - 1) {
                    pe_grid[i][j]->activation_in(activation_s[i][j - 1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i - 1][j]);
                    pe_grid[i][j]->activation_out(activation_out[i]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_out[j]);
                } else if (i == 0) {
                    pe_grid[i][j]->activation_in(activation_s[i][j - 1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_in[j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else if (j == 0) {
                    pe_grid[i][j]->activation_in(activation_in[i]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i - 1][j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else if (i == N - 1) {
                    pe_grid[i][j]->activation_in(activation_s[i][j - 1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i - 1][j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_out[j]);
                } else if (j == N - 1) {
                    pe_grid[i][j]->activation_in(activation_s[i][j - 1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i - 1][j]);
                    pe_grid[i][j]->activation_out(activation_out[i]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                } else {
                    pe_grid[i][j]->activation_in(activation_s[i][j - 1]);
                    pe_grid[i][j]->partial_sum_in(partial_sum_s[i - 1][j]);
                    pe_grid[i][j]->activation_out(activation_s[i][j]);
                    pe_grid[i][j]->partial_sum_out(partial_sum_s[i][j]);
                }
            }
        }
    }

    ~systolic_array() {
        for (auto &v : pe_grid) {
            for (auto &p : v) {
                delete p;
            }
        }
    }

  private:
    vector<vector<pe *>> pe_grid;
    sc_signal<sc_int<8>> activation_s[N][N - 1];
    sc_signal<sc_int<32>> partial_sum_s[N - 1][N];

    // Monitor activation_in values every cycle
    void monitor() {
        string log = "activation_in: ";

        for (auto &a : activation_in) {
            log += to_string(static_cast<int32_t>(a.read())) + " ";
        }
        SC_REPORT_INFO("systolic_array", log.c_str());
    }
};

#endif // SYSTOLIC_ARRAY_H
