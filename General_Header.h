#ifndef GENERAL_HEADER_H
#define GENERAL_HEADER_H

enum Name_Command
{
    PUSH = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    OUT = 6,
    PUSHREG = 7,
    POPREG = 8,
    JB = 9,
    JBE = 10,
    JA = 11,
    JAE = 12,
    JE = 13,
    JNE = 14,
    JMP = 15,
    SQRT = 16,
    LABEL = 17,
    IN = 18,
    CALL = 19,
    RET = 20,
    PUSHMEM = 21,
    POPMEM = 22,
    DRAW = 23,
    HLT = 0,
    Quantity_Commands = 24
};

enum Name_Registers
{
    AX = 0,
    BX = 1,
    CX = 2,
    DX = 3,
    Center_X = 4,
    Center_Y = 5,
    Rad = 6,
    Color = 7,
    X_1 = 8,
    Y_1 = 9,
    X_2 = 10,
    Y_2 = 11,
    Quantity_Registers = 12
};

const char Name_File_Byte_Code[] = "Byte_Code.txt";

const char Name_File_Assembler[] = "Packman.asm";

#endif // GENERAL_HEADER_H
