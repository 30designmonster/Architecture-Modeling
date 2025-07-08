# Direct-Mapped Cache Simulator
**Author:** Praveen Saravanan

A C++ implementation of a direct-mapped cache with write-back policy and dirty bit tracking. This simulator demonstrates cache organization, address mapping, hit/miss detection, and performance metrics calculation including AMAT (Average Memory Access Time).

## Overview

This cache simulator models a direct-mapped cache system with:
- **Direct mapping**: Each memory address maps to exactly one cache line
- **Write-back policy**: Modified data written to memory only when evicted
- **Dirty bit tracking**: Identifies cache lines that need write-back
- **Performance analysis**: Calculates hit rates, miss rates, and AMAT

## Cache Configuration

const int NUM_LINES = 4;        // 4 cache lines total

**Cache Organization:**
- **Mapping**: Direct-mapped (1-way associative)
- **Lines**: 4 cache lines indexed 0-3
- **Block size**: 4 bytes (implied from address breakdown)
- **Write policy**: Write-back with dirty bit


- **Single-dimensional vector**: cache[index]
- **4 lines**: Directly indexed by address bits
- **No associativity**: One location per memory block

## Address Mapping

### Address Decomposition
For a given memory address, the simulator extracts:

Address Bits: [Tag | Index | Offset]
             [31:4 | 3:2  | 1:0  ]

- **Tag**: Upper bits for line identification (bits 4 and above)
- **Index**: Middle bits to select cache line (bits 3:2, 2 bits for 4 lines)
- **Offset**: Lower bits for byte within block (bits 1:0, 4-byte blocks)

## Cache Operations

1. **Extract** index and tag from address
2. **Check** if cache line is valid
3. **Compare** stored tag with address tag
4. **Return** hit status

### Miss Handling & Write-Back
1. **Check** if current line is dirty and valid
2. **If dirty**, perform write-back (5 cycle penalty)
3. **Replace** line with new tag
4. **Set** valid and dirty bits
5. **Add** miss penalty (11 cycles)

## Performance Metrics
### Timing Model
- **Cache hit**: 1 cycle
- **Cache miss**: 11 cycles (memory access)
- **Write-back**: 5 additional cycles when dirty line evicted

### Calculated Metrics
- **Hit Rate**: (Hits / Total Accesses) × 100%
- **Miss Rate**: (Misses / Total Accesses) × 100%
- **AMAT**: Total Cycles / Total Accesses
|

## Cache Behavior Analysis
### Line 0 Conflicts (addresses 0x00, 0x10, 0x03)
- **Address 0x00**: Tag 0, maps to line 0
- **Address 0x10**: Tag 1, maps to line 0 (conflict!)
- **Address 0x03**: Tag 0, maps to line 0 (conflict again!)
- **Result**: Frequent write-backs and capacity misses

### Line 1 Stability (address 0x04)
- **Single mapping**: Only 0x04 maps to line 1 in test sequence
- **Result**: High hit rate after initial miss
- **Demonstrates**: Best-case direct-mapped behavior

## Write-Back Policy Impact

### Write-Back Triggers
- **Dirty line eviction**: When replacing modified data
- **Performance cost**: Additional 5 cycles per write-back
- **Memory bandwidth**: Reduces writes compared to write-through

### Dirty Bit Management
- **Set on store**: All accesses treated as stores in this simulation
- **Clear on write-back**: Reset when data written to memory
- **Optimization**: Only write-back when actually dirty
