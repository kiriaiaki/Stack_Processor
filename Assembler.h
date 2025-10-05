#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "General_Header.h"

int Read_Task (char* Str_With_Task, int *Value);
int Counter_Symbol_In_Str (const char* const Str, const char Symbol);
int Open_File_And_Copying_In_Buffer (char** Buffer, size_t* Size_Source);
char* Str_From_Buffer_Based_On_Slash_N (char* Buffer, size_t *Position_Last_Slash_N, const size_t Size_Source);

#endif // ASSEMBLER_H
