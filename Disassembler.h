#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include "General_Header.h"

struct label_k
{
    char* Name_Label;
    size_t Programme_Counter;
};

struct array_labels_k
{
    label_k* Ptr_Array_Labels = (label_k*) calloc (2, sizeof (label_k));
    size_t Counter_Array_Labels = 0;
    size_t Len_Array_Labels = 2;
};

enum Work_Byte_Code
{
    Password = 29022008,
    Version = 'V',
    Number_Version_Disassembler = 1
};

struct register_k
{
    char Name_Register[10];
};

const register_k Array_Register[Quantity_Registers] = {
{"AX"},
{"BX"},
{"CX"},
{"DX"},
{"Center_X"},
{"Center_Y"},
{"Rad"},
{"Color"},
{"X_1"},
{"Y_1"},
{"X_2"},
{"Y_2"},
{"X_3"},
{"Y_3"},
{"X_A"},
{"Y_A"},
{"Direction"},
{"Len"},
{"For"},
{"Score"}
};

struct command_k
{
    char Name_Command[10];
    int Append_Argument;
    int Number_Append_Argument;
};

const command_k Array_Command[Quantity_Commands] = {
{"HLT",         0, 0},
{"PUSH",        1, 1},
{"ADD",         0, 0},
{"SUB",         0, 0},
{"MUL",         0, 0},
{"DIV",         0, 0},
{"OUT",         0, 0},
{"PUSHREG",     1, 2},
{"POPREG",      1, 2},
{"JB",          1, 3},
{"JBE",         1, 3},
{"JA",          1, 3},
{"JAE",         1, 3},
{"JE",          1, 3},
{"JNE",         1, 3},
{"JMP",         1, 3},
{"SQRT",        0, 0},
{"LABEL",       0, 0},
{"IN",          0, 0},
{"CALL",        1, 3},
{"RET",         0, 0},
{"PUSHMEM",     1, 2},
{"POPMEM",      1, 2},
{"DRAW",        0, 0},
{"RANDOM",      0, 0}
};

int Disassembly (const int* const Byte_Code, array_labels_k* const Array_Labels, FILE* const File_ASM);
int Len_Byte_Code ();
int* Receiving_Byte_Code ();
int Verifier_Byte_Code (const int* const Byte_Code);
int Compare_Registers (const int Number_Register, FILE* const File_ASM);
int Append_Label (array_labels_k* const Array_Labels, const int Programme_Counter);
int Array_Labels_Check_Reserve (array_labels_k* const Array_Labels);
int Comparison_Programme_Counter_Label (const array_labels_k* const Array_Labels, const int Programme_Counter);
int Array_Labels_Dtor (array_labels_k* const Array_Labels);
int Reverse_Str (char* const Str);
char* itoa_k (int Number, char* const Str);
int Print_Label (FILE* const File_ASM, array_labels_k* const Array_Labels, const int Programme_Counter);

#endif // DISASSEMBLER_H
