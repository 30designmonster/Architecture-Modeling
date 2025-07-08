# 2-Way Set-Associative Cache Simulator
**Author:** Praveen Saravanan

A C++ implementation of a 2-way set-associative cache with LRU (Least Recently Used) replacement policy. This simulator demonstrates cache organization, address mapping, hit/miss detection, and replacement algorithms.

## Overview

This cache simulator models a realistic cache hierarchy component with:
- **2-way set-associative organization**: Each set contains 2 cache lines
- **LRU replacement policy**: Evicts the least recently used line on conflicts
- **Address decomposition**: Separates addresses into tag, index, and offset components
- **Real-time hit/miss tracking**: Shows cache behavior for memory access patterns

## Cache Configuration

const int NUM_SETS = 4;         // 4 sets in the cache
const int ASSOCIATIVITY = 2;    // 2 lines per set
const int BLOCK_SIZE = 1;       // 1 word per block
const int INDEX_BITS = 2;       // log2(4 sets) = 2 bits
const int OFFSET_BITS = 0;      // Single word blocks


**Total Cache Size:** 4 sets × 2 ways × 1 word = 8 words

## Address Mapping
### Address Decomposition
For a given memory address, the simulator extracts:

Address Bits: [Tag | Index | Offset]
             [31:2 | 1:0  |   -   ]


- **Tag**: Upper bits for line identification
- **Index**: Middle bits to select cache set (2 bits for 4 sets)
- **Offset**: Lower bits for word within block (0 bits, single word)

## Cache Operations
### Hit Detection
1. **Extract** tag and index from address
2. **Search** both ways in the indexed set
3. **Compare** stored tags with address tag
4. **Update** LRU on hit

### Miss Handling & Replacement
1. **Check** for invalid (empty) lines first
2. **If all valid**, find LRU line (lru == 1)
3. **Replace** LRU line with new data
4. **Update** LRU status


## Key Features
 **Set-Associative Mapping**: Flexible cache organization  
 **LRU Replacement**: Realistic replacement policy  
 **Address Decomposition**: Proper tag/index extraction  
 **Hit/Miss Detection**: Accurate cache behavior simulation  
 **Conflict Resolution**: Handles cache conflicts properly  

## Cache Behavior Analysis

### Set 0 Analysis (addresses 0x00, 0x04, 0x08, 0x10)
- **Capacity**: 2 lines in set 0
- **Conflict**: 4 different tags competing for 2 slots
- **Result**: Frequent misses due to capacity conflicts
- **LRU Effect**: Older entries evicted when set is full

### Set 3 Analysis (address 0x03)
- **First access**: Cold miss (empty set)
- **Second access**: Hit (data still in cache)
- **No conflicts**: Set 3 has no other competing addresses

