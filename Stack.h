#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <assert.h>
#include "General_Header.h"

struct stack_k
{
    int* Array;
    size_t Size;
    size_t Capacity;
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

const int Canary = 29022008;

int Stack_Ctor         (stack_k* const Stack, const size_t Capacity);
int Stack_Dtor         (stack_k* const Stack);
int Stack_Error        (const stack_k* const Stack);
int Stack_Dump         (const stack_k* const Stack);
int Stack_Reallocation (stack_k* const Stack);

int Stack_Push (stack_k* const Stack, const int Element);
int Stack_Pop  (stack_k* const Stack);

#endif // STACK_H
