////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// CACHE 2 WAY :SET ASSOCIATIVITY  ///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  Author:Praveen Saravanan         ///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

using namespace std;

// Configurable cache parameters
const int NUM_SETS = 4;         // Number of sets in the cache
const int ASSOCIATIVITY = 2;    // 2-way set-associative
const int BLOCK_SIZE = 1;       // 1 word per block (offset ignored)
const int OFFSET_BITS = 0;      // Since block size is 1
const int INDEX_BITS = 2;       // log2(NUM_SETS)

// Represents one line (block) in the cache
struct CacheLine {
    int tag;
    bool valid;
    int lru;  // 0 = most recently used, 1 = least recently used

    CacheLine() : tag(-1), valid(false), lru(0) {}
};

// The full cache: 2D vector (sets × ways)
vector<vector<CacheLine>> cache(NUM_SETS, vector<CacheLine>(ASSOCIATIVITY));

// Utility: Extract index from address
int getIndex(int address) {
    return (address >> OFFSET_BITS) & ((1 << INDEX_BITS) - 1);
}

// Utility: Extract tag from address
int getTag(int address) {
    return address >> (OFFSET_BITS + INDEX_BITS);
}

// The LRU values in a set: accessed_way becomes most recent (0), other becomes 1
void updateLRU(vector<CacheLine>& set, int accessed_way) {
    for (int i = 0; i < ASSOCIATIVITY; ++i) {
        if (i == accessed_way) {
            set[i].lru = 0;
        } else {
            set[i].lru = 1;
        }
    }
}

// Perform one cache access and print hit/miss
void cacheAccess(int address) {
    int index = getIndex(address);
    int tag = getTag(address);

    vector<CacheLine>& set = cache[index];
    bool hit = false;

    // Check for hit
    for (int i = 0; i < ASSOCIATIVITY; ++i) {
        if (set[i].valid && set[i].tag == tag) {
            hit = true;
            updateLRU(set, i);
            cout << "HIT" << endl;
            return;
        }
    }

    // Miss: find LRU line (lru == 1) or first invalid line
    int replace_index = -1;
    for (int i = 0; i < ASSOCIATIVITY; ++i) {
        if (!set[i].valid) {
            replace_index = i;
            break;
        }
    }

    if (replace_index == -1) {
        for (int i = 0; i < ASSOCIATIVITY; ++i) {
            if (set[i].lru == 1) {
                replace_index = i;
                break;
            }
        }
    }

    // Replace LRU line
    set[replace_index].tag = tag;
    set[replace_index].valid = true;
    updateLRU(set, replace_index);
    cout << "MISS" << endl;
}

// Simple sample test
int main() {
    vector<int> addresses = {
        0x00, 0x04, 0x08, 0x00, 0x10, 0x04, 0x04,0x03,0x03
    };

    for (int addr : addresses) {
        cout << "Accessing address 0x" << hex << addr << " : ";
        cacheAccess(addr);
    }

    return 0;
}
