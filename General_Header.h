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
    HLT = 0,
    Bad_Input = -1
};

enum Name_Register
{
    AX = 0,
    BX = 1,
    CX = 2,
    DX = 3
};

const char Name_File_Byte_Code[] = "Byte_Code.txt";

const char Name_File_Assembler[] = "Square.asm";

#endif // GENERAL_HEADER_H
