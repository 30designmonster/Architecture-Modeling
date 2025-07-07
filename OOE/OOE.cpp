
// SIMPLE CORE OUT-OF-ORDER EXECUTION (Fixed Version)
// Author: Praveen + ChatGPT Cleanup

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Opcode { ADD, LOAD, STORE, BRANCH, NOP };

struct Instruction {
    Opcode op;
    int dest;
    int src1;
    int src2;
    int robid;
    string repr;

    Instruction(Opcode o, int d, int s1, int s2, string r) :
        op(o), dest(d), src1(s1), src2(s2), repr(r), robid(-1) {}

    Instruction() : op(NOP), dest(-1), src1(-1), src2(-1), robid(-1), repr("NOP") {}
};

struct ROBEntry {
    int rob_id;
    Instruction instr;
    bool ready;
    int result;
};

struct INQEntry {
    int q_id;
    Instruction qinst;
    int result;
};

vector<ROBEntry> ROB;
vector<INQEntry> IQ;
int rob_id_counter = 0;

// Decode stage: assign ROB ID, insert into IQ and ROB
void decode(const Instruction& inst) {
    ROBEntry rob_entry = { rob_id_counter, inst, false, -1 };
    ROB.push_back(rob_entry);

    INQEntry iq_entry = { rob_id_counter, inst, -1 };
    IQ.push_back(iq_entry);

    cout << "Decoded and issued to IQ & ROB: " << inst.repr << " (ROB ID: " << rob_id_counter << ")" << endl;
    rob_id_counter++;
}

// Execute stage: simulate result calculation
int execute(const Instruction& a, int val1, int val2) {
    switch (a.op) {
        case ADD:
            return val1 + val2;
        case LOAD:
            return val1 + 100; // dummy memory load
        case STORE:
            return val1;
        case BRANCH:
        case NOP:
        default:
            return 0;
    }
}

// Hazard checks
bool rr_waw(const Instruction& a, const Instruction& b) {
    return (a.dest == b.dest);
}

bool is_war_hazard(const Instruction& a, const Instruction& b) {
    return (a.src1 == b.dest || a.src2 == b.dest);
}

void scoreboard(const Instruction& curr, const Instruction& prev) {
    if (is_war_hazard(curr, prev)) {
        cout << "WAR hazard detected between: " << curr.repr << " and " << prev.repr << endl;
    } else if (rr_waw(curr, prev)) {
        cout << "WAW hazard detected between: " << curr.repr << " and " << prev.repr << endl;
    }
}

int main() {
    vector<Instruction> program = {
        Instruction(LOAD, 1, 0, -1, "LOAD R1, 0(R0)"),
        Instruction(ADD, 2, 1, 3, "ADD R2, R1, R3"),
        Instruction(STORE, 2, 4, -1, "STORE R2, 0(R4)"),
        Instruction(ADD, 5, 2, 6, "ADD R5, R2, R6")
    };

    int pc = 0;
    int cycle = 0;
    bool done = false;

    while (!done) {
        cout << "\\nCycle " << cycle++ << ":" << endl;

        // Decode & issue if program not done
        if (pc < program.size()) {
            Instruction curr = program[pc];
            if (pc > 0) {
                Instruction prev = program[pc - 1];
                scoreboard(curr, prev);
            }
            decode(curr);
            pc++;
        }

        // Simulate execute (very simplified: all IQ entries execute immediately)
        for (auto& iq_entry : IQ) {
            if (iq_entry.result == -1) {
                iq_entry.result = execute(iq_entry.qinst, 5, 3); // dummy operands
                for (auto& rob_entry : ROB) {
                    if (rob_entry.rob_id == iq_entry.q_id) {
                        rob_entry.result = iq_entry.result;
                        rob_entry.ready = true;
                    }
                }
            }
        }

        // Simulate commit (in order)
        while (!ROB.empty() && ROB.front().ready) {
            cout << "Committed: " << ROB.front().instr.repr << " (Result: " << ROB.front().result << ")" << endl;
            ROB.erase(ROB.begin());
        }

        // Exit when all instructions fetched, ROB empty
        done = (pc >= program.size() && ROB.empty());
    }

    return 0;
}

