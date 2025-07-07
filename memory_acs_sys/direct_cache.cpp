////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////DIRECT MAPPING CACHE SIMULATION  ///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  Author:Praveen Saravanan         ///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
using namespace std;

// Cache configuration
const int NUM_LINES = 4;

// Cache line structure
struct cacheline {
    bool valid;
    bool dirty;
    int tag;

    cacheline() : valid(false), dirty(false), tag(-1) {}
};

// Direct-mapped cache
vector<cacheline> cache(NUM_LINES);

// Address breakdown helpers
int get_index(int address) {
    return (address >> 2) & 0b11;  // Use 2 bits for 4 lines
}

int get_tag(int address) {
    return address >> 4;  // Remaining upper bits as tag
}

// Check for hit
bool check_hit(int address) {
    int index = get_index(address);
    int tag = get_tag(address);
    return cache[index].valid && cache[index].tag == tag;
}

int main() {
    vector<int> addresses = {
        0x00, 0x04, 0x08, 0x00, 0x10, 0x04, 0x04, 0x03, 0x03
    };

    int hit_count = 0, miss_count = 0, total_cycles = 0;

    for (int addr : addresses) {
        cout << "Accessing address 0x" << hex << addr << ": ";
        int index = get_index(addr);
        int tag = get_tag(addr);

        if (check_hit(addr)) {
            hit_count++;
            total_cycles += 1;
            cout << "HIT" << endl;
        } else {
            cout << "MISS";
            // Check if existing line is dirty → write-back
            if (cache[index].valid && cache[index].dirty && cache[index].tag != tag) {
                total_cycles += 5;  // Write-back penalty
                cout << " → Write-back occurred";
            }

            // Replace line
            cache[index].valid = true;
            cache[index].tag = tag;
            cache[index].dirty = true;  // Simulate store access
            miss_count++;
            total_cycles += 11;
            cout << endl;
        }
    }

    // Final report
    cout << "\n=== Cache Simulation Stats ===\n";
    cout << "Total accesses     : " << addresses.size() << endl;
    cout << "Hits               : " << hit_count << endl;
    cout << "Misses             : " << miss_count << endl;
    cout << "Total cycles       : " << total_cycles << endl;

    float hit_rate = (float)hit_count / addresses.size();
    float amat = (float)total_cycles / addresses.size();

    cout << "Hit rate           : " << hit_rate * 100 << "%" << endl;
    cout << "Average memory access time (AMAT): " << amat << " cycles" << endl;

    return 0;
}
