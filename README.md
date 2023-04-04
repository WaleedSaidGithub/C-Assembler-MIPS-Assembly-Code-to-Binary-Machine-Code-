# C-Assembler-MIPS-Assembly-Code-to-Binary-Machine-Code-

The main.cpp file reads in a MIPS assembly code file and produces two output files. The first output file is a list of labels and their corresponding line numbers, which is produced by parsing the input file and extracting lines that end with a colon. The second output file is a binary file containing the assembled MIPS code. The input and output file names are passed as command-line arguments.

The code first checks if the number of arguments is correct, and if not, prints an error message and exits. Then it opens the input file and reads it line by line to extract the labels and their line numbers. It stores the label names and their corresponding line numbers in two vectors. It then closes the input file and opens it again to read the file line by line and assemble the MIPS code.

Each line of the input file is parsed to extract the opcode and its operands. The operands are then converted to their binary representation, and the binary instruction is stored in a vector of integers. After parsing all the lines of the input file, the binary instructions are written to the output binary file.

The code also handles comments within instructions and skips them during the parsing.

