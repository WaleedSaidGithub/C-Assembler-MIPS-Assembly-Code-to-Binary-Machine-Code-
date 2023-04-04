#include <iostream>
#include <string>
#include <unordered_map>
#include "mipsAssembler.h"
using namespace std;

//Default Constructor
mipsAssembler::mipsAssembler() {
    first = "";
    second = "";
    third = "";
    fourth = "";
}


mipsAssembler::mipsAssembler(string fst, string scd, string thr, string fth) {
    first = fst;
    second = scd;
    third = thr;
    fourth = fth;
}

int mipsAssembler::assemble() {
    if (this->first == "addi") {
        return this->addiInstruction();
    }
    if (this->first == "add") {
        return this->addInstruction();
    }
    if (this->first == "sub") {
        return this->subInstruction();
    }
    if (this->first == "mult") {
        return this->multInstruction();
    }
    if (this->first == "div") {
        return this->divInstruction();
    }
    if (this->first == "mflo") {
        return this->mfloInstruction();
    }
    if (this->first == "mfhi") {
        return this->mfhiInstruction();
    }
    if (this->first == "sll") {
        return this->sllInstruction();
    }
    if (this->first == "srl") {
        return this->srlInstruction();
    }
    if (this->first == "lw") {
        return this->lwInstruction();
    }
    if (this->first == "sw") {
        return this->swInstruction();
    }
    if (this->first == "slt") {
        return this->sltInstruction();
    }
    if (this->first == "beq") {
        return this->beqInstruction();
    }
    if (this->first == "bne") {
        return this->bneInstruction();
    }
    if (this->first == "j") {
        return this->jInstruction();
    }
    if (this->first == "jal") {
        return this->jalInstruction();
    }
    if (this->first == "jr") {
        return this->jrInstruction();
    }
    if (this->first == "jalr") {
        return this->jalrInstruction();
    }
    if (this->first == "syscall") {
        return this->syscallInstruction();
    }
    else {
        cerr << "There is an instruction which this assembler can not execute. " << endl;
        exit(1);
    }
    return 0;
}

int mipsAssembler::addInstruction() {
    int addBinary;
    int opcode = 0;
    int rs = mipsAssembler::registerCode(this->third);
    int rt = mipsAssembler::registerCode(this->fourth);
    int rd = mipsAssembler::registerCode(this->second);
    int shamt = 0;
    int funcCode = 32;

    rs = rs << 21;
    rt = rt << 16;
    rd = rd << 11;

    addBinary = opcode + rs + rt + rd + shamt + funcCode;
    return addBinary;
}

int mipsAssembler::addiInstruction() {
    int addiBinary;
    int opcode = 8 << 26;
    int rs = mipsAssembler::registerCode(this->third);
    int rt = mipsAssembler::registerCode(this->second);
    int immediate = atoi(this->fourth.c_str());
    immediate = immediate & 0xffff;

    rs = rs << 21;
    rt = rt << 16;
    addiBinary = opcode + rs + rt + immediate;

    return addiBinary;
}

int mipsAssembler::subInstruction() {
    int subBinary;
    int opcode = 0;
    int rs = mipsAssembler::registerCode(this->third);
    int rt = mipsAssembler::registerCode(this->fourth);
    int rd = mipsAssembler::registerCode(this->second);
    int funcCode = 34;

    rs = rs << 21;
    rt = rt << 16;
    rd = rd << 11;

    subBinary = opcode + rs + rt + rd + funcCode;
    return subBinary;
}

int mipsAssembler::multInstruction() {
    int multBinary;
    int opcode = 0;
    int rs = mipsAssembler::registerCode(this->second);
    int rt = mipsAssembler::registerCode(this->third);
    int funcCode = 24;

    rs = rs << 21;
    rt = rt << 16;

    multBinary = opcode + rs + rt + funcCode;

    return multBinary;
}

int mipsAssembler::divInstruction() {
    int divBinary;
    int opcode = 0;
    int rs = mipsAssembler::registerCode(this->second);
    int rt = mipsAssembler::registerCode(this->third);
    int funcCode = 26;

    rs = rs << 21;
    rt = rt << 16;

    divBinary = opcode + rs + rt + funcCode;

    return divBinary;
}

int mipsAssembler::mfloInstruction() {
    int mfloBinary;
    int opcode = 0;
    int rd = mipsAssembler::registerCode(this->second);
    int funcCode = 18;

    rd = rd << 11;

    mfloBinary = opcode + rd + funcCode;

    return mfloBinary;
}

int mipsAssembler::mfhiInstruction() {
    int mfhiBinary;
    int opcode = 0;
    int rd = mipsAssembler::registerCode(this->second);
    int funcCode = 16;

    rd = rd << 11;

    mfhiBinary = opcode + rd + funcCode;

    return mfhiBinary;
}

int mipsAssembler::sllInstruction() {
    int sllBinary;
    int opcode = 0;
    int rt = mipsAssembler::registerCode(this->third);
    int rd = mipsAssembler::registerCode(this->second);
    int shamt = atoi(this->fourth.c_str());
    int funcCode = 0;

    rt = rt << 16;
    rd = rd << 11;
    shamt = shamt << 6;

    sllBinary = opcode + rt + rd + shamt + funcCode;

    return sllBinary;
}

int mipsAssembler::srlInstruction() {
    int srlBinary;
    int opcode = 0;
    int rt = mipsAssembler::registerCode(this->third);
    int rd = mipsAssembler::registerCode(this->second);
    int shamt = atoi(this->fourth.c_str());
    int funcCode = 2;

    rt = rt << 16;
    rd = rd << 11;
    shamt = shamt << 6;

    srlBinary = opcode + rt + rd + shamt + funcCode;

    return srlBinary;
}

int mipsAssembler::lwInstruction() {
    //First: lw Sec: $s1 Third: 0 Fourth: $t1
    int lwBinary;
    int opcode = 35;
    int base = mipsAssembler::registerCode(this->fourth);
    int rt = mipsAssembler::registerCode(this->second);
    int offset = atoi(this->third.c_str());

    opcode = opcode << 26;
    base = base << 21;
    rt = rt << 16;

    lwBinary = opcode + base + rt + offset;
    return lwBinary;
}

int mipsAssembler::swInstruction() {
    //First: sw Sec: $ra Third: 12 Fourth: $sp
    int swBinary;
    int opcode = 43;
    int base = mipsAssembler::registerCode(this->fourth);
    int rt = mipsAssembler::registerCode(this->second);
    int offset = atoi(this->third.c_str());

    opcode = opcode << 26;
    base = base << 21;
    rt = rt << 16;

    swBinary = opcode + base + rt + offset;
    return swBinary;
}

int mipsAssembler::sltInstruction() {
    //First: slt Sec: $t2 Third: $s1 Fourth: $zero
    int sltBinary;
    int opcode = 0;
    int rs = mipsAssembler::registerCode(this->third);
    int rt = mipsAssembler::registerCode(this->fourth);
    int rd = mipsAssembler::registerCode(this->second);
    int funcCode = 42;

    rs = rs << 21;
    rt = rt << 16;
    rd = rd << 11;

    sltBinary = opcode + rs + rt + rd + funcCode;
    return sltBinary;
}

int mipsAssembler::beqInstruction() {
    //First: beq Sec: $t2 Third: $zero Fourth: string of the address
    int beqBinary;
    int opcode = 4;
    int rs = mipsAssembler::registerCode(this->second);
    //cout << "Beq's second register is equal to " << rs << '\n' << endl;
    int rt = mipsAssembler::registerCode(this->third);
    //cout << "Beq's third register is equal to " << rt << '\n' << endl;
    int offset = atoi(this->fourth.c_str());
    //cout << "The offset value is: " << offset << '\n' << endl;
    offset = offset & 0xffff;
    opcode = opcode << 26;
    //cout << "The opcode :" << opcode << '\n' << endl;
    rs = rs << 21;
    //cout << "After the bit shifting of the second register: " << rs << '\n' << endl;
    rt = rt << 16;
    //cout << "After the bit shifting of the third register: " << rt << '\n' << endl;

    beqBinary = opcode + rs + rt + offset;
    return beqBinary;
}

int mipsAssembler::bneInstruction() {
    int bneBinary;
    int opcode = 5;
    int rs = mipsAssembler::registerCode(this->second);
    //cout << "Beq's second register is equal to " << rs << '\n' << endl;
    int rt = mipsAssembler::registerCode(this->third);
    //cout << "Beq's third register is equal to " << rt << '\n' << endl;
    int offset = atoi(this->fourth.c_str());
    //cout << "The offset value is: " << offset << '\n' << endl;
    offset = offset & 0xffff;
    opcode = opcode << 26;
    //cout << "The opcode :" << opcode << '\n' << endl;
    rs = rs << 21;
    //cout << "After the bit shifting of the second register: " << rs << '\n' << endl;
    rt = rt << 16;
    //cout << "After the bit shifting of the third register: " << rt << '\n' << endl;

    bneBinary = opcode + rs + rt + offset;
    return bneBinary;
}

int mipsAssembler::jInstruction() {
    int jBinary;
    int opcode = 2;
    int target = atoi(this->second.c_str());

    opcode = opcode << 26;
    jBinary = opcode + target;
    return jBinary;
}

int mipsAssembler::jalInstruction() {
    //cout << "Start of jal assembling . . ." << '\n' << endl;
    int jalBinary;
    int opcode = 3;
    int target = atoi(this->second.c_str());
    opcode = opcode << 26;
    //cout << "This is the opcode: " << opcode << '\n' << endl;
    jalBinary = opcode + target;
    return jalBinary;
}

int mipsAssembler::jrInstruction() {
    if (this->second != "$ra") {
        cerr << "Jr instructions only accept $ra' as the selected register!" << endl;
        exit(1);
    }
    int jrBinary;
    int opcode = 8;
    int ra = 31;
    ra = ra << 21;
    jrBinary = opcode + ra;
    return jrBinary;
}

int mipsAssembler::jalrInstruction() {
    int jalrBinary;
    int opcode = 9;
    int rs = mipsAssembler::registerCode(this->third);
    int rd = mipsAssembler::registerCode(this->second);
    rs = rs << 21;
    rd = rd << 11;
    jalrBinary = rs + rd + opcode;
    return jalrBinary;
}

int mipsAssembler::syscallInstruction() {
    int syscallBinary;
    int opcode = 12;
    syscallBinary = opcode;
    return syscallBinary;
}

// map containing registerCodes
int mipsAssembler::registerCode(string reg) {
    int regCode;
    unordered_map<string, int> registerCode;
    registerCode["$zero"] = 0;
    registerCode["$0"] = 0;
    registerCode["$at"] = 1;
    registerCode["$1"] = 1;
    registerCode["$v0"] = 2;
    registerCode["$2"] = 2;
    registerCode["$v1"] = 3;
    registerCode["$3"] = 3;
    registerCode["$a0"] = 4;
    registerCode["$4"] = 4;
    registerCode["$a1"] = 5;
    registerCode["$5"] = 5;
    registerCode["$a2"] = 6;
    registerCode["$6"] = 6;
    registerCode["$a3"] = 7;
    registerCode["$7"] = 7;
    registerCode["$t0"] = 8;
    registerCode["$8"] = 8;
    registerCode["$t1"] = 9;
    registerCode["$9"] = 9;
    registerCode["$t2"] = 10;
    registerCode["$10"] = 10;
    registerCode["$t3"] = 11;
    registerCode["$11"] = 11;
    registerCode["$t4"] = 12;
    registerCode["$12"] = 12;
    registerCode["$t5"] = 13;
    registerCode["$13"] = 13;
    registerCode["$t6"] = 14;
    registerCode["$14"] = 14;
    registerCode["$t7"] = 15;
    registerCode["$15"] = 15;
    registerCode["$s0"] = 16;
    registerCode["$16"] = 16;
    registerCode["$s1"] = 17;
    registerCode["$17"] = 17;
    registerCode["$s2"] = 18;
    registerCode["$18"] = 18;
    registerCode["$s3"] = 19;
    registerCode["$19"] = 19;
    registerCode["$s4"] = 20;
    registerCode["$20"] = 20;
    registerCode["$s5"] = 21;
    registerCode["$21"] = 21;
    registerCode["$s6"] = 22;
    registerCode["$22"] = 22;
    registerCode["$s7"] = 23;
    registerCode["$23"] = 23;
    registerCode["$t8"] = 24;
    registerCode["$24"] = 24;
    registerCode["$t9"] = 25;
    registerCode["$25"] = 25;
    registerCode["$k0"] = 26;
    registerCode["$26"] = 26;
    registerCode["$k1"] = 27;
    registerCode["$27"] = 27;
    registerCode["$gp"] = 28;
    registerCode["$28"] = 28;
    registerCode["$sp"] = 29;
    registerCode["$29"] = 29;
    registerCode["$fp"] = 30;
    registerCode["$30"] = 30;
    registerCode["$ra"] = 31;
    registerCode["$31"] = 31;
    regCode = registerCode[reg];
    return regCode;
}
