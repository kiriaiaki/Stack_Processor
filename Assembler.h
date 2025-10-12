#ifndef ASSEMBLER_H
#define ASSEMBLER_H

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
    int Programme_Counter = -1;
};

struct array_labels_k
{
    struct label_k* Ptr_Array_Labels = (label_k*) calloc (2, sizeof (label_k));
    size_t Counter_Array_Labels = 0;
    size_t Len_Array_Labels = 2;
};

struct byte_code_k
{
    int* Ptr_Byte_Code = (int*) calloc (2, sizeof (int));
    size_t Counter_Byte_Code = 0;
    size_t Len_Byte_Code = 2;
};

char* Open_File_And_Copying_In_Buffer ();
int Assembler (array_labels_k* const Array_Labels, byte_code_k* const Byte_code, char* const Buffer);
int Read_Task (const char* const Current_Line, array_labels_k* const Array_Labels, int* Argument, const size_t Len_Current_Line);
int Comparison_Name_Label (const array_labels_k* const Array_Labels, const char* const Name);
int Array_Labels_Check_Reserve (array_labels_k* const Array_Labels);
int Byte_Code_Check_Reserve (byte_code_k* const Byte_code);
int Array_Labels_Dtor (array_labels_k* const Array_Labels);

#endif // ASSEMBLER_H
