#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Stack.h"
#include "General_Header.h"

struct processor_k
{
    stack_k Stack;

    size_t Programme_Counter;
    int* Array_Byte_Code;

    int Array_Register[Quantity_Registers];

    stack_k Return_Stack;

    int* Random_Access_Memory;
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

const size_t Size_Ram = 7200;

int Run (processor_k* const Processor);

int Processor_Ctor  (processor_k* const Processor);
int Processor_Error (const processor_k* const Processor);
int Processor_Dump  (const processor_k* const Processor);
int Processor_Dtor  (processor_k* const Processor);

int Processor_Pushs            (processor_k* const Processor, const int Number_Command);
int Processor_Pops             (processor_k* const Processor, const int Number_Command);
int Processor_Math             (processor_k* const Processor, const int Number_Command);
int Processor_Sqrt             (processor_k* const Processor, const int Number_Command);
int Processor_Conditional_Jump (processor_k* const Processor, const int Number_Command);
int Processor_Jump             (processor_k* const Processor, const int Number_Command);
int Processor_In               (processor_k* const Processor, const int Number_Command);
int Processor_Out              (processor_k* const Processor, const int Number_Command);
int Processor_Call             (processor_k* const Processor, const int Number_Command);
int Processor_Return           (processor_k* const Processor, const int Number_Command);
int Processor_Draw             (processor_k* const Processor, const int Number_Command);

int* Create_Ram ();
int Delete_Ram  (int* const Random_Access_Memory);

int Check_Input          (const char* const Str);
int Jump                 (size_t* const Programme_Counter , const size_t Location_Jump);
size_t Len_Byte_Code     ();
int* Receiving_Byte_Code ();
int Verifier_Byte_Code   (const processor_k* const Processor);

struct command_k
{
    int Command;
    int (*Fun) (struct processor_k* const Processor, const int Number_Command);
};

const command_k Array_Command[Quantity_Commands] = {
{0,  NULL},
{1,  Processor_Pushs},
{1,  Processor_Math},
{1,  Processor_Math},
{1,  Processor_Math},
{1,  Processor_Math},
{1,  Processor_Out},
{1,  Processor_Pushs},
{1,  Processor_Pops},
{1,  Processor_Conditional_Jump},
{1,  Processor_Conditional_Jump},
{1,  Processor_Conditional_Jump},
{1,  Processor_Conditional_Jump},
{1,  Processor_Conditional_Jump},
{1,  Processor_Conditional_Jump},
{1,  Processor_Jump},
{1,  Processor_Sqrt},
{0,  NULL},
{1,  Processor_In},
{1,  Processor_Call},
{1,  Processor_Return},
{1,  Processor_Pushs},
{1,  Processor_Pops},
{1,  Processor_Draw}
};

#endif // PROCESSOR_H
