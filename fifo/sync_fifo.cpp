#include <iostream>
#include <queue>

using namespace std;

const int W = 2;
const int R = 3;
const int D = 4;
const int N = 50;

queue<int> fifo;

void producer(int data) {
    fifo.push(data);
    cout << "Cycle: data pushed -> " << data << "\n";
}

void consumer() {
    int val = fifo.front();
    fifo.pop();
    cout << "Cycle: data popped -> " << val << "\n";
}

int main() {
    int cycle = 0;
    int t = 0;  // counter for data written

    int write_attempts = 0, write_success = 0;
    int read_attempts = 0, read_success = 0;

    while (cycle < N) {
        bool full = (fifo.size() == D);
        bool empty = fifo.empty();
        bool we = (cycle % W == 0);
        bool re = (cycle % R == 0);

        if (re) {
            read_attempts++;
            if (!empty) {
                consumer();
                read_success++;
            } else {
                cout << "Cycle: read stall (FIFO empty)\n";
            }
        }

        if (we) {
            write_attempts++;
            if (!full) {
                producer(t++);
                write_success++;
            } else {
                cout << "Cycle: write stall (FIFO full)\n";
            }
        }

        cycle++;
    }

    cout << "\n--- Simulation Summary ---\n";
    cout << "Total Cycles: " << N << "\n";
    cout << "Write Attempts: " << write_attempts << ", Success: " << write_success << "\n";
    cout << "Read Attempts: " << read_attempts << ", Success: " << read_success << "\n";
    cout << "Final FIFO Occupancy: " << fifo.size() << " entries\n";

    return 0;
}
