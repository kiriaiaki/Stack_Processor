#include "Processor.h"

int main ()
{
    struct processor_k Processor = {};
    if (Processor_Ctor (&Processor) == There_Are_Errors)
    {
        Processor_Dump (&Processor);
        printf ("\033[31m!NOT START PROCESSOR!\033[0m\n");
        return 0;
    }

    if (Run (&Processor) == There_Are_Errors)
    {
        Processor_Dump (&Processor);
        printf ("\033[31m!NOT FINISH PROCESSOR!\033[0m\n");
        return 0;
    }


    // TODO пустые аргументы (мб обертку)
    // TODO двойные функции ;(
    // TODO костыль общий массив структур почему так? не знаю как по другому (тк требует функцию!) (попробовать переместить)
    // TODO квадратные скобки у функций с памятью (проблема с массивом структур)
    // TODO рабочий файл через командную строку
    // TODO хеширование подшарить
    
    printf ("\033[32mProcessor worked successful!\033[0m\n");
    Processor_Dtor (&Processor);
    return 0;
}

int Run (struct processor_k* const Processor)
{
    int Current_Number_Command = Processor->Array_Byte_Code[Processor->Programme_Counter];

    while (Current_Number_Command != HLT)
    {
        int Value = 0;

        if (Array_Command[Current_Number_Command].Argument == 1)
        {
           if (Current_Number_Command == OUT)
           {
                printf ("%d\n", (*Array_Command[Current_Number_Command].Fun) (Processor, Current_Number_Command));
           }

           else if ((*Array_Command[Current_Number_Command].Fun) (Processor, Current_Number_Command) == There_Are_Errors)
           {
                return There_Are_Errors;
           }
        }

        if (Processor_Error (Processor) != Not_Error_Processor)
        {
            Processor_Dump (Processor);
            return There_Are_Errors;
        }

        Processor->Programme_Counter++;
        Current_Number_Command = Processor->Array_Byte_Code[Processor->Programme_Counter];

        if (Processor_Error (Processor) != Not_Error_Processor)
        {
            Processor_Dump (Processor);
            return There_Are_Errors;
        }

        // Processor_Dump (Processor);
        // getchar ();
    }

    return 0;
}

int Ram_Draw (struct processor_k* const Processor, const int Number_Command)
{
    printf ("\033[H\033[J");
    fflush(stdout);

    for (size_t i = 0; i < Size_Ram; i+=2)
    {
        printf ("\033[%dm%c \033[0m", Processor->Random_Access_Memory[i + 1], Processor->Random_Access_Memory[i]);

        if (i % (80 * 2) == 79 * 2)
        {
            printf ("\n");
        }
    }

    usleep (60000);
    return 0;
}

int Processor_Call (struct processor_k* const Processor, const int Number_Command)
{
    Processor->Programme_Counter++;
    int Location_Function = Processor->Array_Byte_Code[Processor->Programme_Counter];

    if (Push_In_Stack (&Processor->Return_Stack, Processor->Programme_Counter + 1) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Processor->Programme_Counter = Location_Function - 1;

    return 0;
}

int Processor_Return (struct processor_k* const Processor, const int Number_Command)
{
    int Location_Return = Out_From_Stack (&Processor->Return_Stack);
    if (Location_Return == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Jump (&Processor->Programme_Counter, Location_Return);

    return 0;
}

int Stack_In (struct processor_k* const Processor, const int Number_Command)
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

    if (Push_In_Stack (&Processor->Stack, atoi (Value)) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Processor_Error (const struct processor_k* const Processor)
{
    if (Stack_Error (&Processor->Stack) != Not_Error_Stack)
    {
        return Error_Stack;
    }

    if (Processor->Array_Byte_Code == NULL)
    {
        return Error_Byte_Code;
    }

    if (Processor->Programme_Counter < 3)
    {
        return Error_Programme_Counter;
    }

    if (Verifier_Byte_Code (Processor) != 0)
    {
        return Error_Ver_Byte_Code;
    }

    if (Stack_Error (&Processor->Return_Stack) != Not_Error_Stack)
    {
        return Error_Return_Stack;
    }

    return Not_Error_Processor;
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
    Stack_Dtor(&Processor->Return_Stack);
    Delete_Ram (Processor->Random_Access_Memory);
    return 0;
}

int Processor_Dump (const struct processor_k* const Processor)
{
    int Processor_Err = Processor_Error (Processor);

    printf ("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");

    if (Processor_Err != Not_Error_Processor)
    {
        printf ("\n\033[31m!!!ERROR IN PROCESSOR!!!\033[0m\n");
    }

    printf ("\n\033[34mSTACK\033[0m:\n");
    Stack_Dump (&Processor->Stack);

    if (Processor_Err != Error_Ver_Byte_Code)
    {
        printf ("\n\033[34mPASSWORD\033[0m: \033[32m%d\033[0m\n", Processor->Array_Byte_Code[0]);
        printf ("\n\033[34mVERSION\033[0m: \033[32m%c %d\033[0m\n", Processor->Array_Byte_Code[1], Processor->Array_Byte_Code[2]);
    }
    else
    {
        printf ("\n\033[31mERROR VERIFICATION BYTE CODE\033[0m\n");
        printf ("\nPASSWORD: \033[31m%d\033[0m\n", Processor->Array_Byte_Code[0]);
        printf ("\nVERSION: \033[31m%c %d\033[0m\n", Processor->Array_Byte_Code[1], Processor->Array_Byte_Code[2]);
    }

    if (Processor_Err != Error_Byte_Code)
    {
        printf ("\n\033[34mBYTE CODE\033[0m: \n\n");
        size_t Len = Len_Byte_Code ();
        if (Len == 0)
        {
            return There_Are_Errors;
        }

        size_t Len_Line = 20;
        size_t k = 0;

        for (size_t j = 0; j < Len_Line; j++)
        {
            printf ("+-----");
        }
        printf ("+\n");

        if ((Len - 3) % Len_Line == 0)
        {
            k = Len;
        }
        else
        {
            k = Len + (Len_Line - (Len - 3) % Len_Line);
        }

        for (size_t i = 3; i < k; i++)
        {
            if (i == Processor->Programme_Counter)
            {
                printf ("|\033[0;44;1m %3d \033[0m", Processor->Array_Byte_Code[i]);
            }

            else if (i >= Len)
            {
                printf ("|     ");
            }

            else
            {
                printf ("| %3d ", Processor->Array_Byte_Code[i]);
            }

            if ((i - 3) % Len_Line == Len_Line - 1)
            {
                printf ("|\n");

                for (size_t j = 0; j < Len_Line; j++)
                {
                    printf ("+-----");
                }

                printf ("+\n");
            }
        }
    }
    else
    {
        printf ("\n\033[31mERROR PTR BYTE CODE\033[0m\n");
        printf ("\nArray with byte code [%p]\n", Processor->Array_Byte_Code);
    }

    if (Processor_Err != Error_Programme_Counter)
    {
        printf ("\n\033[34mPROGRAMME COUNTER\033[0m: %zu\n", Processor->Programme_Counter);
    }
    else
    {
        printf ("\n\033[31mERROR PROGRAMME COUNTER\033[0m\n");
        printf ("\nPROGRAMME COUNTER: %zu\n", Processor->Programme_Counter);
    }

    printf ("\n\033[34mARRAY REGISTER\033[0m: AX = %d; BX = %d; CX = %d; DX = %d; Center_X = %d; Center_Y = %d; Rad = %d\n",
            Processor->Array_Register[AX], Processor->Array_Register[BX],
            Processor->Array_Register[CX], Processor->Array_Register[DX],
            Processor->Array_Register[Center_X], Processor->Array_Register[Center_Y],
            Processor->Array_Register[Rad]);

    printf ("\n\033[34mRETURN STACK\033[0m:\n");
    Stack_Dump (&Processor->Return_Stack);

    printf ("\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");

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

    Processor->Programme_Counter = 3;

    if (Stack_Ctor (&Processor->Return_Stack, 3) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (Processor_Error (Processor) != Not_Error_Processor)
    {
        Processor_Dump (Processor);
        return There_Are_Errors;
    }

    Processor->Random_Access_Memory = Create_Ram ();
    if (Processor->Random_Access_Memory == NULL)
    {
        return There_Are_Errors;
    }

    return 0;
}

int* Create_Ram ()
{
    int* Random_Access_Memory = (int*) calloc (Size_Ram, sizeof (int));

    if (Random_Access_Memory == NULL)
    {
        printf ("Error allocation memory for ram\n");
        return NULL;
    }

    return Random_Access_Memory;
}

int Delete_Ram (int* Random_Access_Memory)
{
    free (Random_Access_Memory);
    return 0;
}

int Pop_Memory (struct processor_k* const Processor, const int Number_Command)
{

    Processor->Programme_Counter++;
    int Number_Register = Processor->Array_Byte_Code[Processor->Programme_Counter];

    int Value = Stack_Out (Processor, 0);
    if (Value == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int Value_Register = Processor->Array_Register[Number_Register];
    Processor->Random_Access_Memory[Value_Register] = Value;

    return 0;
}

int Stack_Jump (struct processor_k* const Processor, const int Number_Command)
{
    Processor->Programme_Counter++;
    int Location_Jump = Processor->Array_Byte_Code[Processor->Programme_Counter];

    Processor->Programme_Counter = Location_Jump - 1;

    return 0;
}

int Stack_Conditional_Jump (struct processor_k* const Processor, const int Number_Command)
{
    int A2 = Stack_Out (Processor, 0);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Processor, 0);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Processor->Programme_Counter++;
    int Location_Jump = Processor->Array_Byte_Code[Processor->Programme_Counter];

    switch (Number_Command)
    {
        case JB:
            if (A1 < A2)
            {
                Processor->Programme_Counter = Location_Jump - 1;
            }
            break;
        case JBE:
            if (A1 <= A2)
            {
                Processor->Programme_Counter = Location_Jump - 1;
            }
            break;
        case JA:
            if (A1 > A2)
            {
                Processor->Programme_Counter = Location_Jump - 1;
            }
            break;
        case JAE:
            if (A1 >= A2)
            {
                Processor->Programme_Counter = Location_Jump - 1;
            }
            break;
        case JE:
            if (A1 == A2)
        {
            Processor->Programme_Counter = Location_Jump - 1;
        }
            break;
        case JNE:
            if (A1 != A2)
            {
                Processor->Programme_Counter = Location_Jump - 1;
            }
            break;
    }

    return 0;
}

int Stack_Pushs (struct processor_k* const Processor, const int Number_Command)
{
    if (Stack_Error (&Processor->Stack) != Not_Error_Stack)
    {
        Stack_Dump (&Processor->Stack);
        printf ("Error in start Stack_Pushs\n\n");
        return There_Are_Errors;
    }

    if (Stack_Check_Reserve (&Processor->Stack) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Processor->Programme_Counter++;
    int Element = Processor->Array_Byte_Code[Processor->Programme_Counter];

    switch (Number_Command)
    {
        case PUSH:
            Processor->Stack.Array[Processor->Stack.Size + 1] = Element;
            Processor->Stack.Size++;
            break;
        case PUSHREG:
            Processor->Stack.Array[Processor->Stack.Size + 1] = Processor->Array_Register[Element];
            Processor->Stack.Size++;
            break;
        case PUSHMEM:
            int Value_Register = Processor->Array_Register[Element];
            int Value = Processor->Random_Access_Memory[Value_Register];

            Processor->Stack.Array[Processor->Stack.Size + 1] = Processor->Random_Access_Memory[Value_Register];
            Processor->Stack.Size++;
            break;
    }

    if (Stack_Error (&Processor->Stack) != Not_Error_Stack)
    {
        Stack_Dump (&Processor->Stack);
        printf ("Error in finish Stack_Pushs\n\n");
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Pop_Reg (struct processor_k* const Processor, const int Number_Command)
{
    Processor->Programme_Counter++;
    int Number_Register = Processor->Array_Byte_Code[Processor->Programme_Counter];

    Processor->Array_Register[Number_Register] = Stack_Out (Processor, 0);
    if (Processor->Array_Register[Number_Register] == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Sqrt (struct processor_k* const Processor, const int Number_Command)
{
    int A1 = Stack_Out  (Processor, 0);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (Push_In_Stack (&Processor->Stack, int (sqrt (A1))) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Math (struct processor_k* const Processor, const int Number_Command)
{
    int A2 = Stack_Out (Processor, 0);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Out (Processor, 0);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    switch (Number_Command)
    {
        case ADD:
            if (Push_In_Stack (&Processor->Stack, A1 + A2) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case SUB:
            if (Push_In_Stack (&Processor->Stack, A1 - A2) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case MUL:
            if (Push_In_Stack (&Processor->Stack, A1 * A2) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case DIV:
            if (A2 == 0)
            {
                printf ("Error in Stack_Div division by zero\n");
                return There_Are_Errors;
            }

            if (Push_In_Stack (&Processor->Stack, A1 / A2) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
    }

    return 0;
}

int Push_In_Stack (struct stack_k* const Stack, const int Element)
{
    if (Stack_Error (Stack) != Not_Error_Stack)
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

    if (Stack_Error (Stack) != Not_Error_Stack)
    {
        Stack_Dump (Stack);
        printf ("Error in finish Stack_Push\n\n");
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Out (struct processor_k* const Processor, const int Number_Command)
{
    int A = Processor->Stack.Array[Processor->Stack.Size - 1 + 1];

    if (Stack_Pop (&Processor->Stack) == There_Are_Errors)
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
        printf ("\n\033[31m!!!EEERRROOORRR IN STACK!!!\033[0m\n");
    }

    if (Stack_Err == Not_Struct_Stack)
    {
        printf ("\nStruct with stack [%p] \033[31m(not struct stack!)\033[0m\n", Stack);
    }

    else
    {
        printf ("\nStruct with stack [%p]\n"
                "{\n", Stack);

        if (Stack_Err == Bad_Size)
        {
            printf ("    Size = %zu \033[31m(bad size!)\033[0m\n", Stack->Size);
        }

        else
        {
            printf ("    Size = %zu\n", Stack->Size);
        }

        if (Stack_Err == Capacity_Null)
        {
            printf ("    Capacity = %zu \033[31m(bad capacity!)\033[0m\n", Stack->Capacity);
        }

        else
        {
            printf ("    Capacity = %zu + 2\n", Stack->Capacity - 2);
        }

        if (Stack_Err == Not_Array_Stack)
        {
            printf ("    Stack [%p] \033[31m(not array stack!)\033[0m\n", Stack->Array);
        }

        else
        {
            printf ("    Stack [%p]\n"
                    "    {\n", Stack->Array);

            if (Stack->Array[0] != Canary)
            {
                printf ("       -[Start_Canary] = %d \033[31m(bad canary!)\033[0m\n", Stack->Array[0]);
            }

            else
            {
                printf ("       +[\033[32mStart_Canary\033[0m] = %d\n", Stack->Array[0]);
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
                    printf ("        [%zu] = %d \033[31m(poison)\033[0m\n", i, Stack->Array[i + 1]);
                }
            }

            if (Stack->Array[Stack->Capacity - 1] != Canary)
            {
                printf ("       -[Finish_Canary] = %d \033[31m(bad canary!)\033[0m\n"
                        "    }\n", Stack->Array[Stack->Capacity - 1]);
            }

            else
            {
                printf ("       +[\033[32mFinish_Canary\033[0m] = %d\n"
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

    return Not_Error_Stack;
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

    if (Stack_Error (Stack) != Not_Error_Stack)
    {
        Stack_Dump (Stack);
        printf ("Error in Stack_Ctor\n\n");
        return There_Are_Errors;
    }

    return 0;
}

int Stack_Pop (struct stack_k* const Stack)
{
    if (Stack_Error (Stack) != Not_Error_Stack)
    {
        Stack_Dump (Stack);
        printf ("Error in start Stack_Pop\n\n");
        return There_Are_Errors;
    }

    Stack->Array[Stack->Size - 1 + 1] = 0;
    Stack->Size--;

    if (Stack_Error (Stack) != Not_Error_Stack)
    {
        Stack_Dump (Stack);
        printf ("Error in finish Stack_Pop\n\n");
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

int Jump (size_t* const Programme_Counter , const size_t Location_Jump)
{
    *Programme_Counter = Location_Jump - 1;

    return 0;
}

int Out_From_Stack (struct stack_k* const Stack)
{
    int A = Stack->Array[Stack->Size - 1 + 1];

    if (Stack_Pop (Stack) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return A;
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
            if (i == 0 && Str[i] == '-')
            {
                continue;
            }

            printf ("Incorrect input, enter only int number\n");
            return -1;
        }
    }

    return 0;
}
