#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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

const int There_Are_Errors = -2902;

enum Work_Byte_Code
{
    Password = 29022008,
    Version = 'V',
    Number_Version_Disassembler = 1
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
