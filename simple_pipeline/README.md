**5-Stage Pipeline Simulator**
**Author: Praveen Saravanan**

A C++ implementation of a classic 5-stage RISC pipeline with RAW (Read-After-Write) hazard detection and stall insertion. This simulator demonstrates fundamental pipelining concepts including instruction flow, data dependencies, and hazard handling mechanisms.

## Overview

This pipeline simulator models a traditional RISC processor pipeline with:
- **5-stage pipeline**: IF → ID → EX → MEM → WB
- **RAW hazard detection**: Identifies data dependencies between instructions
- **Pipeline stalls**: Inserts NOPs to resolve hazards
- **Cycle-by-cycle execution**: Shows instruction progression through pipeline stages

## Pipeline Configuration
### Pipeline Stages
IF  - Instruction Fetch
ID  - Instruction Decode
EX  - Execute
MEM - Memory Access
WB  - Write Back

**Pipeline Depth:** 5 stages  
**Throughput:** 1 instruction per cycle (ideal case)  
**Latency:** 5 cycles per instruction (pipeline depth)


### Supported Instructions
- **ADD**: Register-register addition (`ADD R2, R1, R3`)
- **LOAD**: Memory to register transfer (`LOAD R1, 0(R0)`)
- **STORE**: Register to memory transfer (`STORE R2, 0(R4)`)
- **NOP**: No operation (pipeline bubble)

## Hazard Detection

### RAW (Read-After-Write) Dependencies
bool hasRAWDependency(const Instruction& a, const Instruction& b) {
    if (b.op == NOP) return false;
    return (a.src1 == b.dest || a.src2 == b.dest);
}

**Detection Logic:**
1. **Compare** current instruction's source registers
2. **Against** previous instruction's destination register
3. **Insert stall** if dependency detected

### Hazard Types Handled
- **RAW Hazard**: Current instruction reads register that previous instruction writes
- **Pipeline Stalls**: NOPs inserted to prevent incorrect data usage
- **In-order execution**: Maintains program correctness


### Dependency Analysis
| Instruction | Dependencies | Hazard Type |
|-------------|--------------|-------------|
| `LOAD R1, 0(R0)` | None | - |
| `ADD R2, R1, R3` | Reads R1 (written by LOAD) | RAW |
| `STORE R2, 0(R4)` | Reads R2 (written by ADD) | RAW |
| `ADD R5, R2, R6` | Reads R2 (written by previous ADD) | RAW |


## Pipeline Performance Analysis

### Stall Impact
- **Ideal CPI**: 1.0 (one instruction per cycle)
- **With stalls**: CPI > 1.0 due to hazard penalties
- **Performance loss**: Each stall adds one cycle delay

## Implementation Highlights
### Simple Hazard Detection
- **Single-stage lookahead**: Only checks ID stage instruction
- **Conservative approach**: Stalls on any detected dependency
- **No forwarding**: Relies purely on stall insertion

### Pipeline State Tracking
- **Cycle-by-cycle visualization**: Shows instruction movement
- **Clear stage identification**: Easy to follow execution flow
- **Debug-friendly output**: Useful for understanding pipeline behavior

### Instruction Set Abstraction
- **Generic instruction format**: Extensible to additional opcodes
- **Register-based operations**: Standard RISC-style addressing
- **Simple dependency model**: Focus on register dependencies

## Pipeline Concepts Demonstrated
### Instruction Pipelining
- **Overlapped execution**: Multiple instructions in different stages
- **Throughput improvement**: Potential for 1 instruction/cycle
- **Latency unchanged**: Still takes 5 cycles per instruction

### Pipeline Control
- **Stage advancement**: Systematic instruction movement
- **Hazard insertion**: Dynamic pipeline modification
- **Completion detection**: Proper pipeline drain

