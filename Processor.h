#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "General_Header.h"

struct stack_k
{
    int* Array;
    size_t Size;
    size_t Capacity;
};

struct processor_k
{
    stack_k Stack;
    size_t Programme_Counter;
    int* Array_Byte_Code;
    int Array_Register[Quantity_Registers];
    stack_k Return_Stack;
    int* Random_Access_Memory;
};

enum Name_Error_Stack
{
    Not_Error_Stack = 0,
    Not_Struct_Stack = 1,
    Not_Array_Stack = 2,
    Capacity_Null = 3,
    Bad_Size = 4,
    Bad_Canary = 5
};

enum Name_Error_Processor
{
    Not_Error_Processor = 0,
    Error_Stack = 1,
    Error_Byte_Code = 2,
    Error_Programme_Counter = 3,
    Error_Ver_Byte_Code = 4,
    Error_Return_Stack = 5
};

enum Work_Byte_Code
{
    Password = 29022008,
    Version = 'V',
    Number_Version_Processor = 1
};

const int Canary = 29022008;

const int There_Are_Errors = -2902;

const size_t Size_Ram = 7200;

int Run (struct processor_k* const Processor);
int Processor_Call (struct processor_k* const Processor, const int Number_Command);
int Processor_Ctor (struct processor_k* const Processor);
int* Create_Ram ();
int Ram_Draw (struct processor_k* const Processor, const int Number_Command);
int Delete_Ram (int* Random_Access_Memory);
int Stack_Conditional_Jump (struct processor_k* const Processor, const int Number_Command);
int Stack_Pushs (struct processor_k* const Processor, const int Number_Command);
int Stack_Math (struct processor_k* const Processor, const int Number_Command);
int Pop_Memory (struct processor_k* const Processor, const int Number_Command);
int Processor_Return (struct processor_k* const Processor, const int Number_Command);
int Processor_Dump (const struct processor_k* const Processor);
int Processor_Error (const struct processor_k* const Processor);
int Processor_Dtor (struct processor_k* const Processor);
int Stack_Ctor (struct stack_k* const Stack, const size_t Capacity);
int Stack_Dump (const stack_k* const Stack);
int Stack_Error (const struct stack_k* const Stack);
int Stack_Dtor (struct stack_k* const Stack);
int Stack_Check_Reserve (struct stack_k* const Stack);
int Stack_Pop (struct stack_k* const Stack);
int Stack_Out (struct processor_k* const Processor, const int Number_Command);
int Stack_Pop_Reg (struct processor_k* const Processor, const int Number_Command);
int Stack_Jump (struct processor_k* const Processor, const int Number_Command);
int Stack_Sqrt (struct processor_k* const Processor, const int Number_Command);
int Stack_In (struct processor_k* const Processor, const int Number_Command);
int Push_In_Stack (struct stack_k* const Stack, const int Element);
size_t Len_Byte_Code ();
int* Receiving_Byte_Code ();
int Verifier_Byte_Code (const struct processor_k* const Processor);
int Check_Input (const char* const Str);
int Jump (size_t* const Programme_Counter , const size_t Location_Jump);
int Out_From_Stack (struct stack_k* const Stack);

struct command_k
{
    int Argument;
    int (*Fun) (struct processor_k* const Processor, const int Number_Command);
};

const command_k Array_Command[Quantity_Commands] = {
{0,  NULL},
{1,  Stack_Pushs},
{1,  Stack_Math},
{1,  Stack_Math},
{1,  Stack_Math},
{1,  Stack_Math},
{1,  Stack_Out},
{1,  Stack_Pushs},
{1,  Stack_Pop_Reg},
{1,  Stack_Conditional_Jump},
{1,  Stack_Conditional_Jump},
{1,  Stack_Conditional_Jump},
{1,  Stack_Conditional_Jump},
{1,  Stack_Conditional_Jump},
{1,  Stack_Conditional_Jump},
{1,  Stack_Jump},
{1,  Stack_Sqrt},
{0,  NULL},
{1,  Stack_In},
{1,  Processor_Call},
{1,  Processor_Return},
{1,  Stack_Pushs},
{1,  Pop_Memory},
{1,  Ram_Draw}
};

#endif // PROCESSOR_H
