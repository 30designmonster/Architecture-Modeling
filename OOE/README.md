## Simple Core Out-of-Order Execution Simulator
## Author: Praveen Saravanan

## Overview
A C++ simulation of a simplified out-of-order execution processor core that demonstrates key concepts in modern CPU architecture including instruction scheduling, hazard detection, and in-order commit.


This simulator models the core components of an out-of-order execution pipeline:
- **Instruction Queue (IQ)**: Holds decoded instructions waiting for execution
- **Reorder Buffer (ROB)**: Maintains program order for in-order commit
- **Hazard Detection**: Identifies WAR (Write-After-Read) and WAW (Write-After-Write) hazards
- **Out-of-Order Execution**: Instructions can execute when operands are ready
- **In-Order Commit**: Results are committed in original program order

## Architecture Components

### Data Structures

#### Instruction

struct Instruction {
    Opcode op;      // Operation type (ADD, LOAD, STORE, BRANCH, NOP)
    int dest;       // Destination register
    int src1, src2; // Source registers
    int robid;      // Reorder Buffer ID
    string repr;    // String representation
}


#### ROB Entry (Reorder Buffer)

struct ROBEntry {
    int rob_id;     // Unique ROB identifier
    Instruction instr; // The instruction
    bool ready;     // Execution completed?
    int result;     // Execution result
}


#### IQ Entry (Instruction Queue)

struct INQEntry {
    int q_id;       // Queue identifier (matches ROB ID)
    Instruction qinst; // The instruction
    int result;     // Execution result
}


## Pipeline Stages

### 1. Decode & Issue
- Assigns unique ROB ID to each instruction
- Inserts instruction into both IQ and ROB
- Maintains program order in ROB

### 2. Execute
- Instructions in IQ execute when operands are ready
- Simplified execution model with dummy operand values
- Updates corresponding ROB entry when execution completes

### 3. Commit
- Instructions commit in-order from ROB head
- Only commits when instruction is ready (executed)
- Maintains precise exception semantics

## Hazard Detection

The simulator implements a scoreboard mechanism to detect:

### WAR Hazards (Write-After-Read)
- Occurs when instruction A reads a register that instruction B writes
- Example: `LOAD R1, 0(R0)` followed by `ADD R2, R1, R3`

### WAW Hazards (Write-After-Write) 
- Occurs when two instructions write to the same destination register
- Example: `ADD R1, R2, R3` followed by `LOAD R1, 0(R4)`

## Sample Program

The simulator runs a simple 4-instruction program:

LOAD R1, 0(R0)    # Load from memory to R1
ADD R2, R1, R3    # Add R1 + R3, store in R2  
STORE R2, 0(R4)   # Store R2 to memory
ADD R5, R2, R6    # Add R2 + R6, store in R5


## Sample Output


Cycle 0:
Decoded and issued to IQ & ROB: LOAD R1, 0(R0) (ROB ID: 0)

Cycle 1:
WAR hazard detected between: ADD R2, R1, R3 and LOAD R1, 0(R0)
Decoded and issued to IQ & ROB: ADD R2, R1, R3 (ROB ID: 1)
Committed: LOAD R1, 0(R0) (Result: 105)

Cycle 2:
Decoded and issued to IQ & ROB: STORE R2, 0(R4) (ROB ID: 2)
Committed: ADD R2, R1, R3 (Result: 8)

Cycle 3:
WAR hazard detected between: ADD R5, R2, R6 and STORE R2, 0(R4)
Decoded and issued to IQ & ROB: ADD R5, R2, R6 (ROB ID: 3)
Committed: STORE R2, 0(R4) (Result: 5)

Cycle 4:
Committed: ADD R5, R2, R6 (Result: 8)


## Key Features

 **Out-of-Order Execution**: Instructions can execute when ready  
 **In-Order Commit**: Results committed in program order  
 **Hazard Detection**: WAR and WAW hazard identification  
 **ROB Management**: Proper reorder buffer handling  
 **Cycle-by-Cycle Simulation**: Clear execution timeline  
