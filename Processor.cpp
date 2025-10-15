#include "Processor.h"

int main ()
{
    struct processor_k Processor = {};
    if (Processor_Ctor (&Processor) == There_Are_Errors)
    {
        printf ("!NOT START PROCESSOR!\n");
        return 0;
    }

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

int Stack_In (struct stack_k* const Stack)
{
    char Value[1000];

    printf ("Value : ");
    scanf ("%[^\n]", Value);
    getchar ();

    while (Check_Input (Value) != 0)
    {
        printf ("Value : ");
        scanf ("%[^\n]", Value);
        getchar ();
    }

    if (Stack_Push (Stack, atoi (Value)) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Processor_Error (const struct processor_k* const Processor)
{
    //TODO write
    return 0;
}

int Processor_Dtor (struct processor_k* const Processor)
{
    free (Processor->Array_Byte_Code);
    Processor->Programme_Counter = 0;
    Stack_Dtor(&Processor->Stack);
    for (size_t i = 0; i < Quantity_Registers; i++)
    {
        Processor->Array_Register[i] = 0;
    }
    return 0;
}

int Processor_Dump (const struct processor_k* const Processor)
{
    printf ("\n----------------------------------------------------\n");
    printf ("\nSTACK:\n");

    Stack_Dump (&Processor->Stack);

    printf ("\nPASSWORD: %d\n", Processor->Array_Byte_Code[0]);

    printf ("\nVERSION: %c %d\n", Processor->Array_Byte_Code[1], Processor->Array_Byte_Code[2]);

    printf ("\nBYTE CODE: ");
    size_t Len = Len_Byte_Code ();
    if (Len == 0)
    {
        return There_Are_Errors;
    }

    for (size_t i = 3; i < Len; i++)
    {
        //printf ("%4-Quantity_Digit(Processor->Array_Byte_Code[i])d", 0);
        printf ("%d", Processor->Array_Byte_Code[i]);
    }
    printf ("\n");

    for (size_t i = 0; i < 11 + Processor->Programme_Counter * 4; i++)
    {
        printf (" ");
    }
    printf ("^^^^");
    //TODO  сделать разделение вывода по строчкам цвет

    printf ("\nPROGRAMME COUNTER: %zu\n", Processor->Programme_Counter);

    printf ("\nARRAY REGISTER: AX = %d; BX = %d; CX = %d; DX = %d",
            Processor->Array_Register[AX], Processor->Array_Register[BX],
            Processor->Array_Register[CX], Processor->Array_Register[DX]);

    printf ("\n----------------------------------------------------\n");

    return 0;
}

int Processor_Ctor (struct processor_k* const Processor)
{
    if (Stack_Ctor(&Processor->Stack, 5) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Processor->Array_Byte_Code = Receiving_Byte_Code ();
    if (Processor->Array_Byte_Code == NULL)
    {
        return There_Are_Errors;
    }

    if (Verifier_Byte_Code (Processor) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Processor->Programme_Counter = 3;

    return 0;
}

int Stack_Jump (size_t* const Programme_Counter , const size_t Location_Jump)
{
    *Programme_Counter = Location_Jump - 1;

    return 0;
}

int Stack_Jump_Not_Equal (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (A1 != A2)
    {
        *Programme_Counter = Location_Jump - 1;
    }

    return 0;
}

int Stack_Jump_Equal (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (A1 == A2)
    {
        *Programme_Counter = Location_Jump - 1;
    }

    return 0;
}

int Stack_Jump_Above_Equal (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (A1 >= A2)
    {
        *Programme_Counter = Location_Jump - 1;
    }

    return 0;
}

int Stack_Jump_Above (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (A1 > A2)
    {
        *Programme_Counter = Location_Jump - 1;
    }

    return 0;
}

int Stack_Jump_Below_Equal (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (A1 <= A2)
    {
        *Programme_Counter = Location_Jump - 1;
    }

    return 0;
}

int Stack_Jump_Below (struct stack_k* const Stack, size_t* const Programme_Counter , const size_t Location_Jump)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (A1 < A2)
    {
        *Programme_Counter = Location_Jump - 1;
    }

    return 0;
}

int Stack_Push_Reg (struct stack_k* const Stack, int* const Array_Register, const size_t Number_Register)
{
    if (Stack_Push (Stack, Array_Register[Number_Register]) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Pop_Reg (struct stack_k* const Stack,  int* const Array_Register, const size_t Number_Register)
{
    Array_Register[Number_Register] = Stack_Out (Stack);

    if (Array_Register[Number_Register] == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Sqrt (struct stack_k* const Stack)
{
    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (Stack_Push (Stack, int (sqrt (A1))) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Add (struct stack_k* const Stack)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (Stack_Push (Stack, A1 + A2) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Sub (struct stack_k* const Stack)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (Stack_Push (Stack, A1 - A2) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Mul (struct stack_k* const Stack)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (Stack_Push (Stack, A1 * A2) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Div (struct stack_k* const Stack)
{
    int A2 = Stack_Out (Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (A2 == 0)
    {
        printf ("Error in Stack_Div division by zero\n");
        return There_Are_Errors;
    }

    if (Stack_Push (Stack, A1 / A2) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Out (struct stack_k* const Stack)
{
    int A = Stack->Array[Stack->Size - 1 + 1];

    if (Stack_Pop (Stack) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return A;
}

int Stack_Dump (const stack_k* const Stack)
{
    int Stack_Err = Stack_Error (Stack);

    if (Stack_Err != 0)
    {
        printf ("\n!!!EEERRROOORRR IN STACK!!!\n");
    }

    if (Stack_Err == Not_Struct_Stack)
    {
        printf ("\nStruct with stack [%p] (not struct stack!)\n", Stack);
    }

    else
    {
        printf ("\nStruct with stack [%p]\n"
                "{\n", Stack);

        if (Stack_Err == Bad_Size)
        {
            printf ("    Size = %zu (bad size!)\n", Stack->Size);
        }

        else
        {
            printf ("    Size = %zu\n", Stack->Size);
        }

        if (Stack_Err == Capacity_Null)
        {
            printf ("    Capacity = %zu (bad capacity!)\n", Stack->Capacity);
        }

        else
        {
            printf ("    Capacity = %zu + 2\n", Stack->Capacity - 2);
        }

        if (Stack_Err == Not_Array_Stack)
        {
            printf ("    Stack [%p] (not array stack!)\n", Stack->Array);
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

            if (Stack_Err == Bad_Size)
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

int Stack_Error (const struct stack_k* const Stack)
{
    if (Stack == NULL)
    {
        return Not_Struct_Stack;
    }

    if (Stack->Array == NULL)
    {
        return Not_Array_Stack;
    }

    if (Stack->Capacity == 0)
    {
        return Capacity_Null;
    }

    if (Stack->Size > Stack->Capacity)
    {
        return Bad_Size;
    }

    if (Stack->Array[0] != Canary || Stack->Array[Stack->Capacity - 1] != Canary)
    {
        return Bad_Canary;
    }

    return Not_Error;
}

int Stack_Dtor (struct stack_k* const Stack)
{
    free (Stack->Array);
    Stack->Capacity = 0;
    Stack->Size = 0;
    return 0;
}

int Stack_Ctor (struct stack_k* const Stack, const size_t Capacity)
{
    Stack->Array = (int*) calloc (Capacity + 2, sizeof (int));
    if (Stack->Array == NULL)
    {
        printf ("Error allocation memory for array stack\n");
        return There_Are_Errors;
    }

    Stack->Capacity = Capacity + 2;

    Stack->Array[0] = Canary;
    Stack->Array[Stack->Capacity - 1] = Canary;

    Stack->Size = 0;

    if (Stack_Error (Stack) != Not_Error)
    {
        Stack_Dump (Stack);
        printf ("Error in Stack_Ctor\n\n");
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Pop (struct stack_k* const Stack)
{
    if (Stack_Error (Stack) != Not_Error)
    {
        Stack_Dump (Stack);
        printf ("Error in start Stack_Pop\n\n");
        return There_Are_Errors;
    }

    Stack->Array[Stack->Size - 1 + 1] = 0;
    Stack->Size--;

    if (Stack_Error (Stack) != Not_Error)
    {
        Stack_Dump (Stack);
        printf ("Error in finish Stack_Pop\n\n");
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Push (struct stack_k* const Stack, const int Element)
{
    if (Stack_Error (Stack) != Not_Error)
    {
        Stack_Dump (Stack);
        printf ("Error in start Stack_Push\n\n");
        return There_Are_Errors;
    }

    if (Stack_Check_Reserve (Stack) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Stack->Array[Stack->Size + 1] = Element;
    Stack->Size++;

    if (Stack_Error (Stack) != Not_Error)
    {
        Stack_Dump (Stack);
        printf ("Error in finish Stack_Push\n\n");
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Check_Reserve (struct stack_k* const Stack)
{
    if (Stack->Capacity - 1 - 2 == Stack->Size)
    {
        Stack->Array[Stack->Capacity - 1] = 0;

        Stack->Capacity = Stack->Capacity * 2 - 2;

        Stack->Array = (int*) realloc (Stack->Array, Stack->Capacity * sizeof (int));
        if (Stack->Array == NULL)
        {
            printf ("Error allocation memory for array stack\n");
            return There_Are_Errors;
        }

        Stack->Array[Stack->Capacity - 1] = Canary;
    }

    return 0;
}

size_t Len_Byte_Code ()
{
    struct stat Data_File_Byte_Code = {};

    if (stat (Name_File_Byte_Code, &Data_File_Byte_Code) != 0)
    {
        printf ("Error getting information about file with byte code\n");
        return 0;
    }

    size_t Len_Byte_Code = size_t (Data_File_Byte_Code.st_size) / sizeof(int);

    return Len_Byte_Code;
}

int* Receiving_Byte_Code ()
{
    size_t Len = Len_Byte_Code ();
    if (Len == 0)
    {
        return NULL;
    }

    int* Byte_Code = (int*) calloc (Len, sizeof (int));
    if (Byte_Code == NULL)
    {
        printf ("Error allocation memory for byte code\n");
        return NULL;
    }

    FILE* File = fopen (Name_File_Byte_Code, "r");
    if (File == NULL)
    {
        printf ("Error opening file with byte code\n");
        return NULL;
    }

    if (fread (Byte_Code, sizeof (int), Len, File) < Len)
    {
        printf ("Error reading file with byte code\n");
        return NULL;
    }

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

int Verifier_Byte_Code (const struct processor_k* const Processor)
{
    if (Processor->Array_Byte_Code[0] != Password)
    {
        printf ("Password doesn't work\n Likely this byte code created not my assembler\n");
        return There_Are_Errors;
    }

    if (Processor->Array_Byte_Code[1] != Version)
    {
        printf ("Password doesn't work\n Likely this byte code created not my assembler\n");
        return There_Are_Errors;
    }

    if (Processor->Array_Byte_Code[2] > Number_Version_Processor)
    {
        printf ("Version Assembler newer than Version Processor\n");
        return There_Are_Errors;
    }
    else if (Processor->Array_Byte_Code[2] < Number_Version_Processor)
    {
        printf ("!POSSIBLE BUGS!\n Version Processor newer than Version Assembler\n");
    }

    return 0;
}

int Check_Input (const char* const Str)
{
    size_t Len = strlen (Str);

    if (Len > 10)
    {
        printf ("Incorrect input, enter only int number\n");
        return -1;
    }

    for (size_t i = 0; i < Len; i++)
    {
        if ('9' < Str[i] || Str[i] < '0')
        {
            printf ("Incorrect input, enter only int number\n");
            return -1;
        }
    }

    return 0;
}
