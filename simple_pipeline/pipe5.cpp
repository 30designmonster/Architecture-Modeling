#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

enum Opcode { ADD, LOAD, STORE, NOP };

struct Instruction {
    Opcode op;
    int dest;
    int src1;
    int src2;
    string repr;

    Instruction(Opcode o, int d, int s1, int s2, string r) :
        op(o), dest(d), src1(s1), src2(s2), repr(r) {}

    static Instruction NOPInstr() {
        return Instruction(NOP, -1, -1, -1, "NOP");
    }
};

struct PipelineStage {
    string name;
    Instruction instr;

    PipelineStage(string n) : name(n), instr(Instruction::NOPInstr()) {}
};

bool hasRAWDependency(const Instruction& a, const Instruction& b) {
    if (b.op == NOP) return false;
    return (a.src1 == b.dest || a.src2 == b.dest);
}

int main() {
    // Simple program
    vector<Instruction> program = {
        Instruction(LOAD, 1, 0, -1, "LOAD R1, 0(R0)"),
        Instruction(ADD, 2, 1, 3, "ADD R2, R1, R3"),
        Instruction(STORE, 2, 4, -1, "STORE R2, 0(R4)"),
        Instruction(ADD, 5, 2, 6, "ADD R5, R2, R6")
    };

    vector<PipelineStage> pipeline = {
        PipelineStage("IF"), PipelineStage("ID"),
        PipelineStage("EX"), PipelineStage("MEM"),
        PipelineStage("WB")
    };

    int cycle = 0;
    int pc = 0;
    queue<Instruction> fetchQueue;
    bool done = false;

    while (!done) {
        cycle++;
        cout << "Cycle " << cycle << ":\n";

        // Move pipeline forward
        for (int i = pipeline.size() - 1; i > 0; --i)
            pipeline[i].instr = pipeline[i - 1].instr;

        // Insert NOP if RAW hazard
        if (pc < program.size()) {
            Instruction curr = program[pc];
            Instruction prev = pipeline[1].instr;  // ID stage

            if (hasRAWDependency(curr, prev)) {
                pipeline[0].instr = Instruction::NOPInstr(); // Insert NOP
            } else {
                pipeline[0].instr = curr;
                pc++;
            }
        } else {
            pipeline[0].instr = Instruction::NOPInstr();
        }

        // Print pipeline status
        for (int i = 0; i < pipeline.size(); ++i)
            cout << "  " << pipeline[i].name << ": " << pipeline[i].instr.repr << "\n";

        // Check for completion
        done = true;
        for (auto& stage : pipeline) {
            if (stage.instr.op != NOP) {
                done = false;
                break;
            }
        }
    }

    return 0;
}
