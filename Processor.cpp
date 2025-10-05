#include "Processor.h"

int main ()
{
    struct stack_k Stack = {};
    Stack_Ctor (&Stack, 5);

    printf ("Hello!\n"
            "I am a stack-calculator, my command:\n"
            "PUSH (int Argument) - add to Argument in stack\n"
            "ADD - delete two last elements stack and add to their addition\n"
            "SUB - delete two last elements stack and add to their subtraction\n"
            "MUL - delete two last elements stack and add to their multiplication\n"
            "DIV - delete two last elements stack and add to their division\n"
            "OUT - delete last element stack and print him\n"
            "HLT - halt (finish)\n");

    int Quantity_Line_Source = 9; //TODO VERY BAAAD!!
    
    int* Buffer_With_Bite_Code = Receiving_Bite_Code (Quantity_Line_Source);
    size_t i = 0;
    int Number_Command = Buffer_With_Bite_Code[i];

    while (Number_Command != HLT)
    {
        int Value = 0;

        if (Number_Command == 1)
        {
            Value = Buffer_With_Bite_Code[i + 1];
            i++;
        }

        switch (Number_Command)
        {
            case PUSH:
                Stack_Push (&Stack, Value);
                break;
            case ADD:
                Stack_Add (&Stack);
                break;
            case SUB:
                Stack_Sub (&Stack);
                break;
            case MUL:
                Stack_Mul (&Stack);
                break;
            case DIV:
                Stack_Div (&Stack);
                break;
            case OUT:
                printf ("%d\n", Stack_Out (&Stack));
                break;
            case HLT:
                break;
        }

        i++;
        Number_Command = Buffer_With_Bite_Code[i];

        Stack_Dump (&Stack, Stack_Error (&Stack));
    }

    free (Buffer_With_Bite_Code);
    Stack_Dtor(&Stack);

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
            printf ("    Size = %d (bad size!)\n", Stack->Size);
        }
        else
        {
            printf ("    Size = %d\n", Stack->Size);
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

int Stack_Dtor (const struct stack_k *Stack)
{
    free (Stack->Array);

    return 0;
}

int Stack_Ctor (struct stack_k *Stack, const size_t Capacity)
{
    Stack->Array = (int*) calloc (Capacity + 2, sizeof (int));
    Stack->Size = 0;
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

int* Receiving_Bite_Code (const int Quantity_Line_Source)
{
    int* Buffer_With_Bite_Code = (int*) calloc (Quantity_Line_Source * 2, sizeof (int));

    FILE* File = fopen ("Bite_Code.txt", "r");
    fread (Buffer_With_Bite_Code, sizeof (int), Quantity_Line_Source * 2, File);
    fclose (File);

    return Buffer_With_Bite_Code;
}
