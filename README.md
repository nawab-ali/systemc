# SystemC/TLM Projects

1. adder: half-adder, full-adder, 4-bit adder
2. alu: 4-bit ALU
3. counter: 4-bit counter
4. encoder_decoder: 4x2 encoder, 2x4 decoder, 3x8 decoder
5. fir: N-order Finite Impulse Response (FIR) filter
6. shift_reg: 4-bit shift register
7. systolic_array: NxN Systolic Array
8. tlm/cpu_mem: Blocking TLM transactions between CPU and memory
9. tlm/cpu_mem_dmi: Blocking TLM transactions between CPU and memory using Direct Memory Interface
10. tlm/cpu_router_mem: TLM transactions between CPU and multiple memories via an interconnect
11. xor: XOR gate using NAND gates

## Build Instructions

Switch to each project directory to build the executable, e.g.

```
bash$ cd fir
bash$ mkdir build
bash$ cd build
bash$ cmake ..
bash$ make
```
