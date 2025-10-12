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
    size_t Size = 0;
    size_t Capacity;
};

struct processor_k
{
    stack_k Stack;
    size_t Programme_Counter = 3;
    int* Array_Byte_Code;
    int Array_Register[4];
};

enum Name_Error
{
    Not_Error = 0,
    Not_Struct_Stack = 1,
    Not_Stack = 2,
    Bad_Capacity = 3,
    Bad_Size = 4,
    Bad_Canary = 5
};

enum Work_Byte_Code
{
    Password = 29022008,
    Version = 'V',
    Number_Version_Processor = 1
};

const int Canary = 29022008;

int Verifier_Byte_Code (struct processor_k *Processor);
size_t Len_Byte_Code ();
int* Receiving_Byte_Code ();
int Quantity_Digit (int Number);
int Printer_Null_After_Number_2 (int Number);
int Stack_Ctor (struct stack_k *Stack, const size_t Capacity);
int Stack_Dump (const stack_k *Stack, const int Stack_Error);
int Stack_Error (const struct stack_k *Stack);
int Stack_Dtor (struct stack_k *Stack);
int Stack_Check_Reserve (struct stack_k *Stack);
int Processor_Ctor (struct processor_k *Processor);
int Processor_Dump (const struct processor_k *Processor);
int Processor_Error (const struct processor_k *Processor);
int Processor_Dtor (struct processor_k *Processor);
int Stack_Push (struct stack_k *Stack, const int Element);
int Stack_Pop (struct stack_k *Stack);
int Stack_Add (struct stack_k *Stack);
int Stack_Sub (struct stack_k *Stack);
int Stack_Mul (struct stack_k *Stack);
int Stack_Div (struct stack_k *Stack);
int Stack_Out (struct stack_k *Stack);int Stack_Push_Reg (struct stack_k *Stack, int* Array_Register, size_t Number_Register);
int Stack_Pop_Reg (struct stack_k *Stack, int* Array_Register, size_t Number_Register);
int Stack_Jump_Below (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell);
int Stack_Jump_Below_Equal (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell);
int Stack_Jump_Above (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell);
int Stack_Jump_Above_Equal (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell);
int Stack_Jump_Equal (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell);
int Stack_Jump_Not_Equal (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell);
int Stack_Jump (size_t* Now_Cell , size_t First_Repeating_Cell);
int Stack_Sqrt (struct stack_k *Stack);
int Stack_In (struct stack_k *Stack);

#endif // PROCESSOR_H
