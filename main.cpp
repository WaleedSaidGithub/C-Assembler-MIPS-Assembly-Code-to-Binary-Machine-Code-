#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>

#include "mipsAssembler.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " [input text filename] [output binary filename]" << endl;
        exit(1);
    }
    //First file read to get the labels and their corresponding line numbers
    ifstream lineNums (argv[1]);
    if (!lineNums.is_open()) {
        cerr << "The input file can't be opened! " << endl;
        exit(1);
    }

    string asmLine;
    int wordCounter = 0;
    int lineNumber = 0;
    string lineNum;
    string func;
    vector<int> mipsOutput;
    vector<string> labelLineNumbers;

    while (getline(lineNums, asmLine)) {
        wordCounter = 0;
        func = "";
        if (asmLine.size() > 0) {
            lineNumber++;
            for (string::size_type i = 0; i < asmLine.size(); i++) {
                if (wordCounter > 0) {
                    break;
                }
                if (!isspace(asmLine[i])) {
                    if (wordCounter == 0) {
                        func.push_back(asmLine[i]);
                    }
                    if (!isspace(asmLine[i]) && isspace(asmLine[i+1])) {
                        wordCounter++;
                    }
                }
            }
            if (func.back() == ':') {
                func.pop_back();
                labelLineNumbers.push_back(func);
                lineNum = to_string(lineNumber);
                labelLineNumbers.push_back(lineNum);
            }
        }
    }

    for (int i=0; i < labelLineNumbers.size(); i++) {
        cout << labelLineNumbers.at(i) << ' ';
    }
    cout << '\n' << endl;
    lineNums.close();

    //Second file read to actually assemble the mips instructions
    ifstream asmFile (argv[1]);
    if (!asmFile.is_open()) {
        cerr << "The input file can't be reopened! " << endl;
        exit(1);
    }

    lineNumber = 0;

    while (getline(asmFile, asmLine)){
        int mipsBinary;
        int address;
        lineNumber++;


        if (asmLine.size() > 0) {
            string first;
            string second;
            string third;
            string fourth;
            int wordCounter = 0;
            string temp;

            for (string::size_type i = 0; i < asmLine.size(); i++) {

                if (!isspace(asmLine[i]) && isspace(asmLine[i+1])) {
                    if (wordCounter == 0) {
                        first.push_back(asmLine[i]);
                    }
                    if (wordCounter == 1) {
                        second.push_back(asmLine[i]);
                    }
                    if (wordCounter == 2) {
                        third.push_back(asmLine[i]);
                    }
                    if (wordCounter == 3) {
                        fourth.push_back(asmLine[i]);
                    }
                    wordCounter = wordCounter + 1;
                }

                if (!isspace(asmLine[i])) {
                    if (wordCounter == 0) {
                        first.push_back(asmLine[i]);
                    }
                    if (wordCounter == 1) {
                        second.push_back(asmLine[i]);
                    }
                    if (wordCounter == 2) {
                        third.push_back(asmLine[i]);
                    }
                    if (wordCounter == 3) {
                        fourth.push_back(asmLine[i]);
                    }
                }

            }

            if (second.size() > 0) {
                second = second.substr(1);
            }
            if (third.size() > 0 ) {
                third = third.substr(1);
            }
            if (fourth.size() > 0) {
                fourth = fourth.substr(1);
            }
            if (first.find(",") != string::npos) {
                first.erase(remove(first.begin(), first.end(), ','), first.end());
            }
            if (second.find(",") != string::npos) {
                second.erase(remove(second.begin(), second.end(), ','), second.end());
            }
            if (third.find(",") != string::npos) {
                third.erase(remove(third.begin(), third.end(), ','), third.end());
            }
            if (fourth.find(",") != string::npos) {
                fourth.erase(remove(fourth.begin(), fourth.end(), ','), fourth.end());
            }

            if (third.find('(') != string::npos && third.find(')') != string::npos) {
                temp = third.substr((third.find('(')+1), (third.find(')')));
                if (temp.find(')') != string::npos) {
                    temp.erase(remove(temp.begin(), temp.end(), ')'), temp.end());
                }
                fourth = temp;
                size_t pos = third.find('(');
                third = third.substr(0, pos);
            }

            //This if statement handles the case where a comment appears within a mips instruction
            if (second.find('#') != string::npos) {
                second = "";
                third = "";
                fourth = "";
            }
            if (third.find('#') != string::npos) {
                third = "";
                fourth = "";
            }
            if (fourth.find('#') != string::npos) {
                fourth = "";
            }

            if (!(first.size() > 0 && (first.at(0) == '.') || first.at(0) == '#') ) {
                //cout << "First: " << first << " Sec: " << second << " Third: " << third << " Fourth: " << fourth << endl;
                //Now, we pass in the first, second, third, and fourth strings into an object
                //if ()

                if (first.back() == ':') {

                    //get rid of the colon character at the end of the function string
                    // in order to compare it with branch and jump instructions
                    first.pop_back();
                }
                else {
                    if (first == "beq" || first == "bne") {

                        int currLine = lineNumber;
                        int funcLine = -1;
                        for (int i = 0; i < labelLineNumbers.size(); i++) {
                            if (labelLineNumbers[i] == fourth) {
                                funcLine = atoi(labelLineNumbers[i+1].c_str());
                                break;
                            }
                        }
                        if (funcLine == -1) {
                            cerr << "Invalid function label! " << endl;
                            exit(1);
                        }
                        if (currLine > funcLine) {
                            funcLine++;
                            address = funcLine - currLine;
                        }
                        else {
                            //currLine is earlier in the file
                            address = funcLine - currLine;
                        }
                        address = address - 1;
                        fourth = to_string(address);
                        mipsAssembler assembleObject = mipsAssembler(first, second, third, fourth);
                        mipsBinary = assembleObject.assemble();
                    }
                    // if j type instruction
                    else if (first == "j" || first == "jal") {
                        //cout << "Label name of j instruction: " << first << '\n' << endl;
                        int index;
                        int jAddress;
                        for (int i = 0; i < labelLineNumbers.size(); i++) {
                            if (labelLineNumbers[i] == second) {
                                index = i;
                                break;

                            }
                            if (i > labelLineNumbers.size()-2) {
                                cerr << "Function name not found! " << endl;
                                exit(1);
                            }

                        }
                        //cout << "Index of function label in vector: " << index << '\n' << endl;
                        int numFunctions;
                        numFunctions = index / 2;
                        int labelLine;
                        labelLine = atoi(labelLineNumbers[index+1].c_str());
                        //cout << "Label line of function is: " << labelLine << '\n' << endl;
                        jAddress = labelLine - (numFunctions * atoi(labelLineNumbers[1].c_str()));
                        if (index == 0) {
                            jAddress = 0;
                        }
                        if (jAddress != 0) {
                            jAddress = jAddress - 1;
                        }
                        second = to_string(jAddress);
                        //cout << "Jump address for this line is: " << second << '\n' << endl;
                        mipsAssembler assembleObject = mipsAssembler(first, second, third, fourth);
                        //cout << " Yo" << '\n' << endl;
                        mipsBinary = assembleObject.assemble();
                        //cout << "Assembled j instruction binary int value: " << mipsBinary << '\n' << endl;
                    }

                    else {


                        //cout << "Hi" << '\n' << endl;
                        if (second.size() > 0 || first == "syscall") {
                            mipsAssembler assembleObject = mipsAssembler(first, second, third, fourth);
                            mipsBinary = assembleObject.assemble();
                        }

                    }

                        cout << first << ' ' << second << ' ' << third << ' ' << fourth << '\n' << endl;
                        mipsOutput.push_back(mipsBinary);
                        cout << hex << mipsBinary << '\n' << endl;
                }

            }

        }
    }

    asmFile.close();

    cout << "Mips Instructions: " << '\n' << endl;
    for (int i = 0; i < mipsOutput.size(); i++) {
        cout << hex << mipsOutput[i]<< '\n' << endl;
    }
    cout << "There are " << mipsOutput.size() << " instructions in this assembly file." << '\n' << endl;

    ofstream binFile(argv[2], ios::binary);

    if (!binFile.is_open()) {
        cerr << "The output binary file can't be opened! " << endl;
        exit(1);
    }

    for (int i = 0; i < mipsOutput.size(); i++) {
        int inst = mipsOutput[i];
        binFile.write((char *) &inst, sizeof(int));
    }

    binFile.close();
}
