#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
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

const size_t Size_Ram = 1296;

int Run (struct processor_k* const Processor);
int Processor_Call (struct processor_k* const Processor, const size_t Location_Function);
int Processor_Ctor (struct processor_k* const Processor);
int* Create_Ram ();
int Ram_Draw (struct processor_k* const Processor);
int Delete_Ram (int* Random_Access_Memory);
int Push_Memory (struct processor_k* const Processor);
int Pop_Memory (struct processor_k* const Processor);
int Processor_Return (struct processor_k* const Processor);
int Processor_Dump (const struct processor_k* const Processor);
int Processor_Error (const struct processor_k* const Processor);
int Processor_Dtor (struct processor_k* const Processor);
int Stack_Ctor (struct stack_k* const Stack, const size_t Capacity);
int Stack_Dump (const stack_k* const Stack);
int Stack_Error (const struct stack_k* const Stack);
int Stack_Dtor (struct stack_k* const Stack);
int Stack_Check_Reserve (struct stack_k* const Stack);
int Stack_Push (struct stack_k* const Stack, const int Element);
int Stack_Pop (struct stack_k* const Stack);
int Stack_Add (struct stack_k* const Stack);
int Stack_Sub (struct stack_k* const Stack);
int Stack_Mul (struct stack_k* const Stack);
int Stack_Div (struct stack_k* const Stack);
int Stack_Out (struct stack_k* const Stack);
int Stack_Push_Reg (struct stack_k* const Stack, int* const Array_Register, const size_t Number_Register);
int Stack_Pop_Reg (struct stack_k* const Stack, int* const Array_Register, const size_t Number_Register);
int Stack_Jump_Below (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump);
int Stack_Jump_Below_Equal (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump);
int Stack_Jump_Above (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump);
int Stack_Jump_Above_Equal (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump);
int Stack_Jump_Equal (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump);
int Stack_Jump_Not_Equal (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump);
int Stack_Jump (size_t* const Programme_Counter , const size_t Location_Jump);
int Stack_Sqrt (struct stack_k* const Stack);
int Stack_In (struct stack_k* const Stack);
size_t Len_Byte_Code ();
int* Receiving_Byte_Code ();
int Verifier_Byte_Code (const struct processor_k* const Processor);
int Check_Input (const char* const Str);

#endif // PROCESSOR_H
