#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include "General_Header.h"

struct stack_k
{
    int* Array;
    int Size;
    size_t Capacity;
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

const int Canary = 29022008;

int* Receiving_Bite_Code ();
int Stack_Pop (struct stack_k *Stack);
int Stack_Add (struct stack_k *Stack);
int Stack_Sub (struct stack_k *Stack);
int Stack_Mul (struct stack_k *Stack);
int Stack_Div (struct stack_k *Stack);
int Stack_Out (struct stack_k *Stack);
int Counter_Int_Number_In_Bite_Code ();
int Stack_Dtor (const struct stack_k *Stack);
int Stack_Error (const struct stack_k *Stack);
int Stack_Check_Reserve (struct stack_k *Stack);
int Stack_Push (struct stack_k *Stack, const int Element);
int Stack_Dump (const stack_k *Stack, const int Stack_Error);
int Stack_Ctor (struct stack_k *Stack, const size_t Capacity);

#endif // PROCESSOR_H
