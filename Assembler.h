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
    char Name_Label[100];
    int Programme_Counter = -1;
};

int Open_File_And_Copying_In_Buffer (char** Buffer, ssize_t* Size_File);
size_t Assembler (label_k* const Array_Labels, size_t* const Counter_Label, int* const Byte_Code, char* const Buffer);
int Read_Task (const char* const Current_Line, label_k* const Array_Labels, size_t* const Counter_Label, int* Argument, const size_t Len_Current_Line);
int Comparison_Name_Label (const label_k* const Array_Labels, const size_t Counter_Label, const char* const Name);

#endif // ASSEMBLER_H
