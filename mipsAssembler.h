#ifndef __MIPSASSEMBLER_H__
#define __MIPSASSEMBLER_H__

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class mipsAssembler {

private:

    string first;
    string second;
    string third;
    string fourth;

public:

    mipsAssembler();
    mipsAssembler(string fst, string scd, string thr, string fth);
    int assemble();
    int addInstruction();
    int addiInstruction();
    int subInstruction();
    int multInstruction();
    int divInstruction();
    int mfloInstruction();
    int mfhiInstruction();
    int sllInstruction();
    int srlInstruction();
    int lwInstruction();
    int swInstruction();
    int sltInstruction();
    int beqInstruction();
    int bneInstruction();
    int jInstruction();
    int jalInstruction();
    int jrInstruction();
    int jalrInstruction();
    int syscallInstruction();
    int registerCode(string reg);

};



#endif
