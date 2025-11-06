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

const int There_Are_Errors = -2902;

const char Name_File_Byte_Code[] = "Byte_Code.txt";

const char Name_File_Assembler[] = "code.asm/Packman.asm";
//
// const char* Array_Name_Register[Quantity_Registers] = {
//     "AX",
//     "BX",
//     "CX",
//     "DX",
//     "Center_X",
//     "Center_Y",
//     "Rad",
//     "Color",
//     "X_1",
//     "Y_1",
//     "X_2",
//     "Y_2"
// };
//

// struct command_k
// {
//     char Name_Command[10];
//     int (*Fun_Read_Argument) (const char* const Current_Line, char* const Str_With_Argument, array_labels_k* const Array_Labels);
//     int Type_Argument;
//     int (*Fun_Processor) (processor_k* const Processor, const int Number_Command);
// };
//
// const command_k Array_Command[Quantity_Commands] = {
// {"HLT",     NULL,           0,  NULL                       },
// {"PUSH",    Read_Number,    1,  Processor_Pushs            },
// {"ADD",     NULL,           0,  Processor_Math             },
// {"SUB",     NULL,           0,  Processor_Math             },
// {"MUL",     NULL,           0,  Processor_Math             },
// {"DIV",     NULL,           0,  Processor_Math             },
// {"OUT",     NULL,           0,  Processor_Out              },
// {"PUSHREG", Read_Register,  2,  Processor_Pushs            },
// {"POPREG",  Read_Register,  2,  Processor_Pops             },
// {"JB",      Read_Label,     3,  Processor_Conditional_Jump },
// {"JBE",     Read_Label,     3,  Processor_Conditional_Jump },
// {"JA",      Read_Label,     3,  Processor_Conditional_Jump },
// {"JAE",     Read_Label,     3,  Processor_Conditional_Jump },
// {"JE",      Read_Label,     3,  Processor_Conditional_Jump },
// {"JNE",     Read_Label,     3,  Processor_Conditional_Jump },
// {"JMP",     Read_Label,     3,  Processor_Jump             },
// {"SQRT",    NULL,           0,  Processor_Sqrt             },
// {"LABEL",   Number_Label,   0,  NULL                       },
// {"IN",      NULL,           0,  Processor_In               },
// {"CALL",    Read_Label,     3,  Processor_Call             },
// {"RET",     NULL,           0,  Processor_Return           },
// {"PUSHMEM", Read_Register,  2,  Processor_Pushs            },
// {"POPMEM",  Read_Register,  2,  Processor_Pops             },
// {"DRAW",    NULL,           0,  Processor_Draw             }
// };
//

#endif // GENERAL_HEADER_H
