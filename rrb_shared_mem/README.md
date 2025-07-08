# Multi-Core Round-Robin Bus Arbitration Simulator

**Author:** Praveen Saravanan

A C++ implementation of round-robin bus arbitration for multi-core systems. This simulator demonstrates fair resource allocation, priority rotation, and conflict resolution in shared bus architectures commonly found in multi-core processors.

## Overview

This arbitration simulator models a shared bus system with:
- **4-core configuration**: Multiple cores competing for bus access
- **Round-robin scheduling**: Fair access policy with rotating priority
- **Request-grant protocol**: Standard bus arbitration mechanism
- **Cycle-by-cycle simulation**: Real-time arbitration decisions

## System Configuration

const int core = 4;         // Number of processor cores
const int N = 10;           // Simulation cycles

**Bus Architecture:**
- **Shared resource**: Single bus connecting all cores
- **Arbitration policy**: Round-robin with fairness guarantee
- **Access granularity**: One core per cycle maximum
- **Priority rotation**: Prevents starvation


### Core States
- **Requesting**: Core needs bus access (`request[i] = true`)
- **Idle**: Core not requesting access (`request[i] = false`)
- **Granted**: Core receives bus access and response

## Round-Robin Arbitration Algorithm

### Priority Rotation Logic
for (int i = 1; i <= core; ++i) {
    int idx = (last_grant + i) % core;
    if (request[idx]) {
        // Grant access to this core
        grant_access(idx);
        last_grant = idx;
        break;
    }
}

### Arbitration Steps
1. **Start** from next core after last granted core
2. **Search** clockwise for first requesting core
3. **Grant** access to first found requester
4. **Update** last_grant pointer for next cycle
5. **Send response** to granted core

## Fairness Mechanism

### Round-Robin Properties
- **Equal opportunity**: Every core gets equal chance for access
- **Starvation prevention**: No core can be indefinitely blocked
- **Predictable latency**: Maximum wait time is (N-1) cycles for N cores
- **Simple implementation**: O(N) search complexity



### Arbitration Decisions
| Cycle | Requests | Last Grant | Search Order | Winner | New Last Grant |
|-------|----------|------------|--------------|--------|----------------|
| 0 | [0,2] | -1 | 0→1→2→3 | Core 0 | 0 |
| 1 | [1,3] | 0 | 1→2→3→0 | Core 1 | 1 |
| 2 | [2] | 1 | 2→3→0→1 | Core 2 | 2 |
| 3 | [] | 2 | 3→0→1→2 | None | 2 |

## Bus Utilization Analysis

### Efficiency Metrics
- **Bus utilization**: Percentage of cycles with granted requests
- **Request satisfaction**: Ratio of grants to requests
- **Idle cycles**: Cycles with no active requests
- **Fairness index**: Distribution of grants across cores

### Performance Characteristics
- **Throughput**: One transaction per active cycle
- **Latency**: Variable based on request conflicts
- **Fairness**: Guaranteed equal access over time
- **Overhead**: Minimal arbitration logic required

## Multi-Core System Context

### Why Bus Arbitration Matters
- **Shared resources**: Memory controllers, I/O interfaces, caches
- **Conflict resolution**: Multiple cores accessing same resource
- **Performance impact**: Arbitration delays affect overall throughput
- **Fairness requirements**: Prevent core starvation

### Real-World Applications
- **Cache coherence**: Snooping bus protocols
- **Memory access**: Shared memory controller arbitration
- **I/O operations**: Peripheral access coordination
- **Inter-core communication**: Message passing mechanisms

## Arbitration Policy Comparison

### Round-Robin Advantages
- **Simple implementation**: Easy hardware realization
- **Fair access**: Equal opportunity for all cores
- **Predictable behavior**: Bounded waiting times
- **Low overhead**: Minimal arbitration logic

## System Integration

### Bus Protocol Stack
1. **Physical layer**: Electrical bus signals
2. **Data link layer**: Error detection and correction
3. **Arbitration layer**: Access control (this simulator)
4. **Transaction layer**: Request/response protocols

### Performance Optimization
- **Pipelining**: Overlap arbitration with data transfer
- **Burst transfers**: Reduce arbitration overhead
- **Priority inheritance**: Handle urgent requests
- **Dynamic priority**: Adapt to workload patterns

## Scalability Considerations

### Core Count Impact
- **Linear search**: O(N) arbitration complexity
- **Fairness guarantee**: Still maintained with more cores
- **Latency increase**: Maximum wait time grows with core count
- **Hardware complexity**: More request/grant signals needed

### Optimization Strategies
- **Hierarchical arbitration**: Tree-based selection
- **Parallel arbiters**: Multiple bus segments
- **Virtual channels**: Separate logical buses
- **Crossbar switches**: Non-blocking interconnects

## Mobile/Embedded Applications

### Power Considerations
- **Clock gating**: Disable arbiter when no requests
- **Request prediction**: Anticipate access patterns
- **Power-aware scheduling**: Consider energy costs
- **Sleep state handling**: Manage core power transitions

### Real-Time Constraints
- **Bounded latency**: Guarantee maximum response time
- **Priority inheritance**: Handle urgent requests
- **Deadline scheduling**: Time-aware arbitration
- **Jitter minimization**: Consistent access patterns

