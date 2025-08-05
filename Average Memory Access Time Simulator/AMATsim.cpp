///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////Average Memory Access Time Simulator////////////////////////////////////////
////////////////////////Author:Praveen Saravanan///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdlib> 
#include <ctime>  

using namespace std;

class MemoryAccessModel {
private:
    // Latencies (cycles)
    const int L1_LAT = 1;
    const int L2_LAT = 12;
    const int DRAM_LAT = 100;

    // Counters
    int l1_hits = 0;
    int l2_hits = 0;
    int dram_hits = 0;
    int total_cycles = 0;

    int num_accesses;

public:
    // Constructor
    MemoryAccessModel(int accesses) : num_accesses(accesses) {
        srand(time(0)); // Seed RNG
    }

    void runSimulation() {
        for (int i = 0; i < num_accesses; i++) {
            int r = rand() % 100; // Random number [0..99]

            if (r < 90) { // 90% chance L1 hit
                l1_hits++;
                total_cycles += L1_LAT;
            }
            else if (r < 97) { // Next 7% chance L2 hit
                l2_hits++;
                total_cycles += L2_LAT;
            }
            else { // Remaining 3% DRAM
                dram_hits++;
                total_cycles += DRAM_LAT;
            }
        }
    }

    void printResults() const {
        double amat = static_cast<double>(total_cycles) / num_accesses;
        cout << "L1 Hits: " << l1_hits << "\n";
        cout << "L2 Hits: " << l2_hits << "\n";
        cout << "DRAM Hits: " << dram_hits << "\n";
        cout << "Average Memory Access Time (AMAT): " << amat << " cycles\n";
    }
};

int main() {
    MemoryAccessModel model(1000);
    model.runSimulation();
    model.printResults();
    return 0;
}
