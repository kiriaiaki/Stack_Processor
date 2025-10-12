#include "Processor.h"

int main ()
{
    struct processor_k Processor = {};
    Processor_Ctor (&Processor);

    int Current_Number_Command = Processor.Array_Byte_Code[Processor.Programme_Counter];

    while (Current_Number_Command != HLT)
    {
        int Value = 0;

        switch (Current_Number_Command)
        {
            case PUSH:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Push (&Processor.Stack, Value);
                break;
            case ADD:
                Stack_Add (&Processor.Stack);
                break;
            case SUB:
                Stack_Sub (&Processor.Stack);
                break;
            case MUL:
                Stack_Mul (&Processor.Stack);
                break;
            case DIV:
                Stack_Div (&Processor.Stack);
                break;
            case OUT:
                printf ("%d\n", Stack_Out (&Processor.Stack));
                break;
            case PUSHREG:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Push_Reg (&Processor.Stack, Processor.Array_Register, size_t (Value));
                break;
            case POPREG:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Pop_Reg (&Processor.Stack, Processor.Array_Register, size_t (Value));
                break;
            case JB:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Jump_Below (&Processor.Stack, &Processor.Programme_Counter, size_t (Value));
                break;
            case JBE:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Jump_Below_Equal (&Processor.Stack, &Processor.Programme_Counter, size_t (Value));
                break;
            case JA:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Jump_Above (&Processor.Stack, &Processor.Programme_Counter, size_t (Value));
                break;
            case JAE:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Jump_Above_Equal (&Processor.Stack, &Processor.Programme_Counter, size_t (Value));
                break;
            case JE:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Jump_Equal (&Processor.Stack, &Processor.Programme_Counter, size_t (Value));
                break;
            case JNE:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Jump_Not_Equal (&Processor.Stack, &Processor.Programme_Counter, size_t (Value));
                break;
            case JMP:
                Value = Processor.Array_Byte_Code[Processor.Programme_Counter + 1];
                Processor.Programme_Counter++;
                Stack_Jump (&Processor.Programme_Counter, size_t (Value));
                break;
            case SQRT:
                Stack_Sqrt (&Processor.Stack);
                break;
            case IN:
                Stack_In(&Processor.Stack);
                break;
            case HLT:
                break;
            default:
                break;
        }

        Processor.Programme_Counter++;
        Current_Number_Command = Processor.Array_Byte_Code[Processor.Programme_Counter];

        //Processor_Dump (&Processor);
        //getchar ();

    }

    Processor_Dtor (&Processor);
    return 0;
}

int Stack_In (struct stack_k *Stack)
{
    int Value = 0;
    printf ("Value : ");
    scanf ("%d", &Value);
    //TODO -5 76t
    Stack_Push (Stack, Value);
    return 0;
}

int Processor_Error (const struct processor_k *Processor)
{
    //TODO write
    return 0;
}

int Processor_Dtor (struct processor_k *Processor)
{
    free (Processor->Array_Byte_Code);
    Processor->Programme_Counter = 0;
    Stack_Dtor(&Processor->Stack);
    for (size_t i = 0; i < 4; i++)
    {
        Processor->Array_Register[i] = 0;
    }
    return 0;
}

int Processor_Dump (const struct processor_k *Processor)
{
    printf ("\n----------------------------------------------------\n");
    printf ("\nSTACK:\n");
    Stack_Dump (&Processor->Stack, Stack_Error (&Processor->Stack));

    printf ("\nBYTE CODE: ");
    for (size_t i = 0; i < Len_Byte_Code (); i++)
    {
        Printer_Null_After_Number_2 (Processor->Array_Byte_Code[i]);
        printf ("%d ",Processor->Array_Byte_Code[i]);
    }
    printf ("\n");
    for (size_t i = 0; i < 11 + Processor->Programme_Counter * 3; i++)
    {
        printf (" ");
    }
    printf ("^^");

    printf ("\nPROGRAMME COUNTER: %zu\n", Processor->Programme_Counter);

    printf ("\nARRAY REGISTER: AX = %d; BX = %d; CX = %d; DX = %d",
            Processor->Array_Register[0], Processor->Array_Register[1],
            Processor->Array_Register[2], Processor->Array_Register[3]);

    printf ("\n----------------------------------------------------\n");
    return 0;
}

int Printer_Null_After_Number_2 (int Number)
{
    for (int i = 0; i < 2 - Quantity_Digit (Number); i++)
    {
        printf ("0");
    }

    return 0;
}

int Processor_Ctor (struct processor_k *Processor)
{
    Stack_Ctor(&Processor->Stack, 5);
    Processor->Array_Byte_Code = Receiving_Byte_Code ();

    return 0;
}

int Stack_Jump (size_t* Now_Cell , size_t First_Repeating_Cell)
{
    *Now_Cell = First_Repeating_Cell - 1;

    return 0;
}

int Stack_Jump_Not_Equal (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    if (A1 != A2)
    {
        *Now_Cell = First_Repeating_Cell - 1;
    }

    return 0;
}

int Stack_Jump_Equal (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    if (A1 == A2)
    {
        *Now_Cell = First_Repeating_Cell - 1;
    }

    return 0;
}

int Stack_Jump_Above_Equal (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    if (A1 >= A2)
    {
        *Now_Cell = First_Repeating_Cell - 1;
    }

    return 0;
}

int Stack_Jump_Above (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    if (A1 > A2)
    {
        *Now_Cell = First_Repeating_Cell - 1;
    }

    return 0;
}

int Stack_Jump_Below_Equal (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    if (A1 <= A2)
    {
        *Now_Cell = First_Repeating_Cell - 1;
    }

    return 0;
}

int Stack_Jump_Below (struct stack_k *Stack, size_t* Now_Cell , size_t First_Repeating_Cell)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    if (A1 < A2)
    {
        *Now_Cell = First_Repeating_Cell - 1;
    }

    return 0;
}

int Stack_Push_Reg (struct stack_k *Stack, int* Array_Register, size_t Number_Register)
{
    Stack_Push (Stack, Array_Register[Number_Register]);

    return 0;
}

int Stack_Pop_Reg (struct stack_k *Stack,  int* Array_Register, size_t Number_Register)
{
    Array_Register[Number_Register] = Stack_Out (Stack);

    return 0;
}

int Stack_Sqrt (struct stack_k *Stack)
{
    int A1 = Stack_Out (Stack);

    Stack_Push (Stack, int (sqrt (A1)));

    return 0;
}

int Stack_Add (struct stack_k *Stack)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    Stack_Push (Stack, A1 + A2);

    return 0;
}

int Stack_Sub (struct stack_k *Stack)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    Stack_Push (Stack, A1 - A2);

    return 0;
}

int Stack_Mul (struct stack_k *Stack)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    Stack_Push (Stack, A1 * A2);

    return 0;
}

int Stack_Div (struct stack_k *Stack)
{
    int A2 = Stack_Out (Stack);
    int A1 = Stack_Out (Stack);

    Stack_Push (Stack, A1 / A2);

    return 0;
}

int Stack_Out (struct stack_k *Stack)
{
    int A = Stack->Array[Stack->Size + 1 - 1];

    Stack_Pop (Stack);

    return A;
}

int Stack_Dump (const stack_k *Stack, const int Stack_Error)
{
    if (Stack_Error != 0)
    {
        printf ("\nEEERRROOORRR!!!");
    }

    if (Stack_Error == Not_Struct_Stack)
    {
        printf ("\nStruct with stack [%p] (not struct stack!)\n", Stack);
    }
    else
    {
        printf ("\nStruct with stack [%p]\n"
                "{\n", Stack);

        if (Stack_Error == Bad_Size)
        {
            printf ("    Size = %zu (bad size!)\n", Stack->Size);
        }
        else
        {
            printf ("    Size = %zu\n", Stack->Size);
        }

        if (Stack_Error == Bad_Capacity)
        {
            printf ("    Capacity = %zu (bad capacity!)\n", Stack->Capacity);
        }
        else
        {
            printf ("    Capacity = %zu + 2\n", Stack->Capacity - 2);
        }

        if (Stack_Error == Not_Stack)
        {
            printf ("    Stack [%p] (not stack!)\n", Stack->Array);
        }
        else
        {
            printf ("    Stack [%p]\n"
                    "    {\n", Stack->Array);

            if (Stack->Array[0] != Canary)
            {
                printf ("       -[Start_Canary] = %d (bad canary!)\n", Stack->Array[0]);
            }
            else
            {
                printf ("       +[Start_Canary] = %d\n", Stack->Array[0]);
            }

            if (Stack_Error == Bad_Size)
            {
                for (size_t i = 0; i < Stack->Capacity - 2; i++)
                {
                    printf ("        [%zu] = %d\n", i, Stack->Array[i + 1]);
                }
            }
            else
            {
                for (size_t i = 0; i < Stack->Size; i++)
                {
                    printf ("       *[%zu] = %d\n", i, Stack->Array[i + 1]);
                }

                for (size_t i = Stack->Size; i < Stack->Capacity - 2; i++)
                {
                    printf ("        [%zu] = %d (poison)\n", i, Stack->Array[i + 1]);
                }
            }

            if (Stack->Array[Stack->Capacity - 1] != Canary)
            {
                printf ("       -[Finish_Canary] = %d (bad canary!)\n"
                        "    }\n", Stack->Array[Stack->Capacity - 1]);
            }
            else
            {
                printf ("       +[Finish_Canary] = %d\n"
                        "    }\n", Stack->Array[Stack->Capacity - 1]);
            }
        }

        printf ("}\n");
    }

    return 0;
}

int Stack_Error (const struct stack_k *Stack)
{
    if (Stack == NULL)
    {
        return Not_Struct_Stack;
    }

    if (Stack->Array == NULL)
    {
        return Not_Stack;
    }

    if (Stack->Capacity == 0)
    {
        return Bad_Capacity;
    }

    if (Stack->Size < 0)
    {
        return Bad_Size;
    }

    if (Stack->Array[0] != Canary || Stack->Array[Stack->Capacity - 1] != Canary)
    {
        return Bad_Canary;
    }

    return Not_Error;
}

int Stack_Dtor (struct stack_k *Stack)
{
    free (Stack->Array);
    Stack->Capacity = 0;
    Stack->Size = 0;
    return 0;
}

int Stack_Ctor (struct stack_k *Stack, const size_t Capacity)
{
    Stack->Array = (int*) calloc (Capacity + 2, sizeof (int));
    Stack->Capacity = Capacity + 2;

    Stack->Array[0] = Canary;
    Stack->Array[Stack->Capacity - 1] = Canary;

    if (Stack_Error (Stack) != 0)
    {
        Stack_Dump (Stack, Stack_Error (Stack));
        printf ("Error in Stack_Ctor\n\n");
        return Stack_Error (Stack);
    }

    return 0;
}

int Stack_Pop (struct stack_k *Stack)
{
    if (Stack_Error (Stack) != 0)
    {
        Stack_Dump (Stack, Stack_Error (Stack));
        printf ("Error in start Stack_Pop\n\n");
        return Stack_Error (Stack);
    }

    Stack->Array[Stack->Size - 1 + 1] = 0;
    Stack->Size--;

    if (Stack_Error (Stack) != 0)
    {
        Stack_Dump (Stack, Stack_Error (Stack));
        printf ("Error in finish Stack_Pop\n\n");
        return Stack_Error (Stack);
    }

    return 0;
}

int Stack_Push (struct stack_k *Stack, const int Element)
{
    if (Stack_Error (Stack) != 0)
    {
        Stack_Dump (Stack, Stack_Error (Stack));
        printf ("Error in start Stack_Push\n\n");
        return Stack_Error (Stack);
    }

    Stack->Array[Stack->Size + 1] = Element;
    Stack->Size++;

    Stack_Check_Reserve (Stack);

    if (Stack_Error (Stack) != 0)
    {
        Stack_Dump (Stack, Stack_Error (Stack));
        printf ("Error in finish Stack_Push\n\n");
        return Stack_Error (Stack);
    }

    return 0;
}

int Stack_Check_Reserve (struct stack_k *Stack)
{
    if (Stack->Capacity - 3 == Stack->Size)
    {
        Stack->Array[Stack->Capacity - 1] = 0;
        Stack->Capacity = Stack->Capacity * 2 - 2;
        Stack->Array = (int*) realloc (Stack->Array, Stack->Capacity * sizeof (int));
        Stack->Array[Stack->Capacity - 1] = Canary;
    }

    return 0;
}

size_t Len_Byte_Code ()
{
    struct stat Data_File_Byte_Code = {};

    if (stat (Name_File_Byte_Code, &Data_File_Byte_Code) != 0)
    {
        return 0;
    }

    size_t Len_Byte_Code = size_t (Data_File_Byte_Code.st_size) / sizeof(int);

    return Len_Byte_Code;
}

int* Receiving_Byte_Code ()
{
    size_t Len = Len_Byte_Code ();

    int* Byte_Code = (int*) calloc (Len , sizeof (int));

    FILE* File = fopen (Name_File_Byte_Code, "r");
    fread (Byte_Code, sizeof (int), Len, File);
    fclose (File);

    return Byte_Code;
}

int Quantity_Digit (int Number)
{
    int Quantity = 0;

    if (Number <= 0)
    {
        Number = Number * (-1);
        Quantity++;
    }

    while (Number != 0)
    {
        Number /= 10;
        Quantity++;
    }

    return Quantity;
}

