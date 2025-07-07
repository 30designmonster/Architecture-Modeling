////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////MULTI CORE RRB SIMULATION ///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////  Author:Praveen Saravanan         ///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const int core = 4;
const int N = 10;  // Number of simulation cycles

vector<bool> request(core, false);
int last_grant = -1;  // Tracks last core granted

void response(int i) {
    cout << "  Response sent to Core " << i << endl;
}

int main() {
    for (int cycle = 0; cycle < N; ++cycle) {
        cout << "Cycle " << cycle << ":\n";

        // Generate random requests for demo
        for (int i = 0; i < core; ++i) {
            request[i] = (rand() % 2 == 0);  // 50% chance of requesting
        }

        // Print active requests
        for (int i = 0; i < core; ++i) {
            if (request[i])
                cout << "  Core " << i << " requested access\n";
        }

        // Round-robin arbitration
        bool granted = false;
        for (int i = 1; i <= core; ++i) {
            int idx = (last_grant + i) % core;
            if (request[idx]) {
                cout << "  Request granted to Core " << idx << endl;
                response(idx);
                last_grant = idx;
                granted = true;
                break;
            }
        }

        if (!granted) {
            cout << "  No requests. Bus idle.\n";
        }

        cout << "------------------\n";
    }

    return 0;
}
