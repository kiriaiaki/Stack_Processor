#include "Assembler.h"

int main ()
{
    char* Buffer = Open_File_And_Copying_In_Buffer ();
    if (Buffer == NULL)
    {
        return 0;
    }

    struct byte_code_k Byte_Code = {};
    if (Byte_Code.Ptr_Byte_Code == NULL)
    {
        printf ("!NOT START ASSEMBLER! Error allocating memory for byte code\n");
        return 0;
    }
    Byte_Code.Ptr_Byte_Code[0] = Password;
    Byte_Code.Ptr_Byte_Code[1] = Version;
    Byte_Code.Ptr_Byte_Code[2] = Number_Version_Assembler;

    struct array_labels_k Array_Labels = {};
    if (Array_Labels.Ptr_Array_Labels == NULL)
    {
        printf ("!NOT START ASSEMBLER! Error allocating memory for array labels\n");
        return 0;
    }
    Array_Labels.Ptr_Array_Labels[0].Name_Label = (char*) calloc (10, sizeof (char));
    strcpy (Array_Labels.Ptr_Array_Labels[0].Name_Label, "Not_Find");
    Array_Labels.Ptr_Array_Labels[0].Programme_Counter = -1;
    Array_Labels.Counter_Array_Labels++;

    if (Assembler (&Array_Labels, &Byte_Code, Buffer) == There_Are_Errors)
    {
        printf ("!ASSEMBLER NOT FINISH!\n");
        return 0;
    }
    Byte_Code.Counter_Byte_Code = 3;
    if (Assembler (&Array_Labels, &Byte_Code, Buffer) == There_Are_Errors)
    {
        printf ("!ASSEMBLER NOT FINISH!\n");
        return 0;
    }

    if (Check_Correct_Label (&Byte_Code) == There_Are_Errors)
    {
        printf ("!ASSEMBLER NOT FINISH!\n");
        return 0;
    }
    FILE* File_Byte_Code = fopen (Name_File_Byte_Code, "w");
    if (File_Byte_Code == NULL)
    {
        printf ("!ASSEMBLER NOT FINISH!\n Error opening file for byte code\n");
        return 0;

    }
    if (fwrite (Byte_Code.Ptr_Byte_Code, sizeof (int), Byte_Code.Counter_Byte_Code, File_Byte_Code) < Byte_Code.Counter_Byte_Code)
    {
        printf ("!ASSEMBLER NOT FINISH!\n Error writing in file for byte code\n");
        return 0;
    }
    fclose (File_Byte_Code);

    printf ("Compilation was successful!\n");
    free (Buffer);
    free (Byte_Code.Ptr_Byte_Code);
    Array_Labels_Dtor (&Array_Labels);
    return 0;
}

int Assembler (array_labels_k* const Array_Labels, byte_code_k* const Byte_Code, char* const Buffer)
{
    size_t i = 0;
    char* Ptr_Last_Slash_N = Buffer;

    while (Buffer[i] != '\0')
    {
        if (Buffer[i] == '\n')
        {
            int Number_Label = 0;
            Buffer[i] = '\0';

            char* Current_Line = Ptr_Last_Slash_N;
            size_t Len_Current_Line = size_t (&Buffer[i] - Ptr_Last_Slash_N) + 1;
            Ptr_Last_Slash_N = &Buffer[i + 1];

            int Number_Command = Read_Task (Current_Line, Len_Current_Line);
            if (Number_Command == There_Are_Errors)
            {
                return There_Are_Errors;
            }

            switch (Number_Command)
            {
                case Bad_Input:
                    for (size_t k = 0; k < Len_Current_Line - 1; k++)
                    {
                        if (Current_Line[k] != ' ')
                        {
                            printf ("<%s> This string incorrect\n"
                                    "now programme counter = %zu\n", Current_Line, Byte_Code->Counter_Byte_Code);
                            return There_Are_Errors;
                        }
                    }
                    break;

                case LABEL:
                    Number_Label = Read_Label (Current_Line, Len_Current_Line, Array_Labels);
                    if (Number_Label == There_Are_Errors)
                    {
                        return There_Are_Errors;
                    }
                    Array_Labels->Ptr_Array_Labels[Number_Label].Programme_Counter = int (Byte_Code->Counter_Byte_Code);
                    break;

                default:
                    if (Append_In_Byte_Code (Byte_Code, Number_Command) == There_Are_Errors)
                    {
                        return There_Are_Errors;
                    }

                    int Argument = Read_Argument (Current_Line, Len_Current_Line, Number_Command, Array_Labels);
                    if (Argument == There_Are_Errors)
                    {
                        return There_Are_Errors;
                    }

                    if (Append_Argument (Byte_Code, Argument, Number_Command, Array_Labels) == There_Are_Errors)
                    {
                        return There_Are_Errors;
                    }
            }

            Buffer[i] = '\n';
        }

        i++;
    }

    return 0;
}

int Check_Correct_Label (byte_code_k* const Byte_Code)
{
    for (size_t i = 3; i < Byte_Code->Counter_Byte_Code - 1; i++)
    {
        switch (Byte_Code->Ptr_Byte_Code[i])
        {
            case JB:
                if (Byte_Code->Ptr_Byte_Code[i + 1] == -1)
                {
                    printf ("You have JB with programme counter <%zu> on incorrect label\n", i);
                    return There_Are_Errors;
                }
                break;
            case JBE:
                if (Byte_Code->Ptr_Byte_Code[i + 1] == -1)
                {
                    printf ("You have JBE with programme counter <%zu> on incorrect label\n", i);
                    return There_Are_Errors;
                }
                break;
            case JA:
                if (Byte_Code->Ptr_Byte_Code[i + 1] == -1)
                {
                    printf ("You have JA with programme counter <%zu> on incorrect label\n", i);
                    return There_Are_Errors;
                }
                break;
            case JAE:
                if (Byte_Code->Ptr_Byte_Code[i + 1] == -1)
                {
                    printf ("You have JAE with programme counter <%zu> on incorrect label\n", i);
                    return There_Are_Errors;
                }
                break;
            case JE:
                if (Byte_Code->Ptr_Byte_Code[i + 1] == -1)
                {
                    printf ("You have JE with programme counter <%zu> on incorrect label\n", i);
                    return There_Are_Errors;
                }
                break;
            case JNE:
                if (Byte_Code->Ptr_Byte_Code[i + 1] == -1)
                {
                    printf ("You have JNE with programme counter <%zu> on incorrect label\n", i);
                    return There_Are_Errors;
                }
                break;
            case JMP:
                if (Byte_Code->Ptr_Byte_Code[i + 1] == -1)
                {
                    printf ("You have JMP with programme counter <%zu> on incorrect label\n", i);
                    return There_Are_Errors;
                }
                break;
            default:
                break;
        }
    }

    return 0;
}

int Read_Task (const char* const Current_Line, const size_t Len_Current_Line)
{
    char* Str_With_Task = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Task == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with task\n");
        return There_Are_Errors;
    }
    sscanf (Current_Line, "%s", Str_With_Task);

    if (Str_With_Task[0] == ':')
    {
        return LABEL;
    }

    if (strcmp (Str_With_Task, "PUSH") == 0)
    {
       return PUSH;
    }
    else if (strcmp (Str_With_Task, "ADD") == 0)
    {
       return ADD;
    }
    else if (strcmp (Str_With_Task, "SUB") == 0)
    {
       return SUB;
    }
    else if (strcmp (Str_With_Task, "MUL") == 0)
    {
        return MUL;
    }
    else if (strcmp (Str_With_Task, "DIV") == 0)
    {
       return DIV;
    }
    else if (strcmp (Str_With_Task, "OUT") == 0)
    {
       return OUT;
    }
    else if (strcmp (Str_With_Task, "HLT") == 0)
    {
       return HLT;
    }
    else if (strcmp (Str_With_Task, "PUSHREG") == 0)
    {
       return PUSHREG;
    }
    else if (strcmp (Str_With_Task, "POPREG") == 0)
    {
        return POPREG;
    }
    else if (strcmp (Str_With_Task, "JB") == 0)
    {
        return JB;
    }
    else if (strcmp (Str_With_Task, "JBE") == 0)
    {
        return JBE;
    }
    else if (strcmp (Str_With_Task, "JA") == 0)
    {
        return JA;
    }
    else if (strcmp (Str_With_Task, "JAE") == 0)
    {
        return JAE;
    }
    else if (strcmp (Str_With_Task, "JE") == 0)
    {
        return JE;
    }
    else if (strcmp (Str_With_Task, "JNE") == 0)
    {
        return JNE;
    }
    else if (strcmp (Str_With_Task, "JMP") == 0)
    {
        return JMP;
    }
    else if (strcmp (Str_With_Task, "SQRT") == 0)
    {
       return SQRT;
    }
    else if (strcmp (Str_With_Task, "IN") == 0)
    {
       return IN;
    }
    else
    {
        return Bad_Input;
    }
    //TODO FREEE ?!?!?!??!
}

int Read_Argument (const char* const Current_Line, const size_t Len_Current_Line, const int Number_Command, array_labels_k* const Array_Labels)
{
    char* Str_With_Task = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Task == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with task\n");
        return There_Are_Errors;
    }
    char* Str_With_Argument = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Argument == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with arguments\n");
        return There_Are_Errors;
    }

    sscanf (Current_Line, "%s %s", Str_With_Task, Str_With_Argument);
    switch (Number_Command)
    {
        case PUSH:
            for (size_t i = 0; i < Len_Current_Line; i++)
            {
                if (Str_With_Argument[i] == '\0')
                {
                    break;
                }
                if ('0' > Str_With_Argument[i] || Str_With_Argument[i] > '9')
                {
                    if (i == 0 && Str_With_Argument[i] == '-')
                    {
                        continue;
                    }
                    else
                    {
                        printf ("<%s> \nThis string incorrect, argument push not a number\n", Current_Line);
                        return There_Are_Errors;
                    }
                }
            }
            return atoi (Str_With_Argument);
            break;
        case PUSHREG:
            if (strcmp (Str_With_Argument, "AX") == 0)
            {
                return AX;
            }
            else if (strcmp (Str_With_Argument, "BX") == 0)
            {
                return BX;
            }
            else if (strcmp (Str_With_Argument, "CX") == 0)
            {
                return CX;
            }
            else if (strcmp (Str_With_Argument, "DX") == 0)
            {
                return DX;
            }
            else
            {
                printf ("<%s> \n This string incorrect, this register doesn't exist\n", Current_Line);
                return There_Are_Errors;
            }
            break;
        case POPREG:
            if (strcmp (Str_With_Argument, "AX") == 0)
            {
                return AX;
            }
            else if (strcmp (Str_With_Argument, "BX") == 0)
            {
                return BX;
            }
            else if (strcmp (Str_With_Argument, "CX") == 0)
            {
                return CX;
            }
            else if (strcmp (Str_With_Argument, "DX") == 0)
            {
                return DX;
            }
            else
            {
                printf ("<%s> \n This string incorrect, this register doesn't exist\n", Current_Line);
                return There_Are_Errors;
            }
            break;
        case JB:
            if (Str_With_Argument[0] == ':')
            {
                return Comparison_Name_Label (Array_Labels, &Str_With_Argument[1]);
            }
            else
            {
                printf ("<%s> \n This string incorrect, label must begin :\n", Current_Line);
                return There_Are_Errors;
            }
            break;
        case JBE:
            if (Str_With_Argument[0] == ':')
            {
                return Comparison_Name_Label (Array_Labels, &Str_With_Argument[1]);
            }
            else
            {
                printf ("<%s> \n This string incorrect, label must begin :\n", Current_Line);
                return There_Are_Errors;
            }
            break;
        case JA:
            if (Str_With_Argument[0] == ':')
            {
                return Comparison_Name_Label (Array_Labels, &Str_With_Argument[1]);
            }
            else
            {
                printf ("<%s> \n This string incorrect, label must begin :\n", Current_Line);
                return There_Are_Errors;
            }
            break;
        case JAE:
            if (Str_With_Argument[0] == ':')
            {
                return Comparison_Name_Label (Array_Labels, &Str_With_Argument[1]);
            }
            else
            {
                printf ("<%s> \n This string incorrect, label must begin :\n", Current_Line);
                return There_Are_Errors;
            }
            break;
        case JE:
            if (Str_With_Argument[0] == ':')
            {
                return Comparison_Name_Label (Array_Labels, &Str_With_Argument[1]);
            }
            else
            {
                printf ("<%s> \n This string incorrect, label must begin :\n", Current_Line);
                return There_Are_Errors;
            }
            break;
        case JNE:
            if (Str_With_Argument[0] == ':')
            {
                return Comparison_Name_Label (Array_Labels, &Str_With_Argument[1]);
            }
            else
            {
                printf ("<%s> \n This string incorrect, label must begin :\n", Current_Line);
                return There_Are_Errors;
            }
            break;
        case JMP:
            if (Str_With_Argument[0] == ':')
            {
                return Comparison_Name_Label (Array_Labels, &Str_With_Argument[1]);
            }
            else
            {
                printf ("<%s> \n This string incorrect, label must begin :\n", Current_Line);
                return There_Are_Errors;
            }
            break;
        default:
            return 0;
            break;
    }
    //TODO FREEEEE?!?!??!?!?
}

int Append_Argument (byte_code_k* const Byte_Code, const int Value, const int Number_Command, array_labels_k* const Array_Labels)
{
    switch (Number_Command)
    {
        case PUSH:
            if (Append_In_Byte_Code (Byte_Code, Value) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case PUSHREG:
            if (Append_In_Byte_Code (Byte_Code, Value) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case POPREG:
            if (Append_In_Byte_Code (Byte_Code, Value) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case JB:
            if (Append_In_Byte_Code (Byte_Code, Array_Labels->Ptr_Array_Labels[Value].Programme_Counter) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case JBE:
            if (Append_In_Byte_Code (Byte_Code, Array_Labels->Ptr_Array_Labels[Value].Programme_Counter) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case JA:
            if (Append_In_Byte_Code (Byte_Code, Array_Labels->Ptr_Array_Labels[Value].Programme_Counter) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case JAE:
            if (Append_In_Byte_Code (Byte_Code, Array_Labels->Ptr_Array_Labels[Value].Programme_Counter) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case JE:
            if (Append_In_Byte_Code (Byte_Code, Array_Labels->Ptr_Array_Labels[Value].Programme_Counter) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case JNE:
            if (Append_In_Byte_Code (Byte_Code, Array_Labels->Ptr_Array_Labels[Value].Programme_Counter) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        case JMP:
            if (Append_In_Byte_Code (Byte_Code, Array_Labels->Ptr_Array_Labels[Value].Programme_Counter) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
        default:
            break;
    }
    return 0;
}

int Read_Label (const char* const Current_Line, const size_t Len_Current_Line, array_labels_k* const Array_Labels)
{
    char* Str_With_Label = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Label == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with label\n");
        return There_Are_Errors;
    }
    sscanf (Current_Line, "%s", Str_With_Label);

    int Number_Label = Comparison_Name_Label (Array_Labels, &Str_With_Label[1]);

    if (Number_Label == 0)
    {
        Array_Labels_Check_Reserve (Array_Labels);

        Array_Labels->Ptr_Array_Labels[Array_Labels->Counter_Array_Labels].Name_Label = (char*) calloc (Len_Current_Line, sizeof (char));
        strcpy (Array_Labels->Ptr_Array_Labels[Array_Labels->Counter_Array_Labels].Name_Label, &Str_With_Label[1]);

        Array_Labels->Counter_Array_Labels++;
        free (Str_With_Label);
        return int(Array_Labels->Counter_Array_Labels) - 1;
    }

    else
    {
        free (Str_With_Label);
        return Number_Label;
    }
}

int Append_In_Byte_Code (byte_code_k* const Byte_Code, const int Value)
{
    if (Byte_Code_Check_Reserve (Byte_Code) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Value;
    Byte_Code->Counter_Byte_Code++;

    return 0;
}

char* Open_File_And_Copying_In_Buffer ()
{
    struct stat Data_File_Asm = {};

    if (stat (Name_File_Assembler, &Data_File_Asm) != 0)
    {
        printf ("!NOT START ASSEMBLER! Error getting information about ASM file\n");
        return NULL;
    }

    ssize_t Size_File = Data_File_Asm.st_size;

    const int File_Asm = open (Name_File_Assembler, O_RDONLY);
    if (File_Asm == -1)
    {
        printf ("!NOT START ASSEMBLER! Error opening ASM file\n");
        return NULL;
    }

    char* Buffer = (char*) calloc (size_t (Size_File), sizeof (char));
    if (Buffer == NULL)
    {
        printf ("!NOT START ASSEMBLER! Error allocating memory for ASM file\n");
        return NULL;
    }

    if (read (File_Asm, Buffer, size_t (Size_File)) < Size_File)
    {
        printf ("!NOT START ASSEMBLER! Error reading ASM file\n");
        return NULL;
    }

    close (File_Asm);

    return Buffer;
}

int Comparison_Name_Label (const array_labels_k* const Array_Labels, const char* const Name)
{
    for (size_t i = 1; i < Array_Labels->Counter_Array_Labels; i++)
    {
        if (strcmp (Array_Labels->Ptr_Array_Labels[i].Name_Label, Name) == 0)
        {
            return int (i);
        }
    }

    return 0;
}

int Array_Labels_Check_Reserve (array_labels_k* const Array_Labels)
{
    if (Array_Labels->Counter_Array_Labels == Array_Labels->Len_Array_Labels - 1)
    {
        Array_Labels->Len_Array_Labels = Array_Labels->Len_Array_Labels * 2;
        Array_Labels->Ptr_Array_Labels = (label_k*) realloc (Array_Labels->Ptr_Array_Labels, Array_Labels->Len_Array_Labels * sizeof (label_k));
        if (Array_Labels->Ptr_Array_Labels == NULL)
        {
            printf ("!ERROR IN ASSEMBLER! Error allocating memory for array labels\n");
            return There_Are_Errors;
        }
    }

    return 0;
}

int Byte_Code_Check_Reserve (byte_code_k* const Byte_Code)
{
    if (Byte_Code->Counter_Byte_Code == Byte_Code->Len_Byte_Code - 1)
    {
        Byte_Code->Len_Byte_Code = Byte_Code->Len_Byte_Code * 2;
        Byte_Code->Ptr_Byte_Code = (int*) realloc (Byte_Code->Ptr_Byte_Code, Byte_Code->Len_Byte_Code * sizeof (int));
        if (Byte_Code->Ptr_Byte_Code == NULL)
        {
            printf ("!ERROR IN ASSEMBLER! Error allocating memory for byte code\n");
            return There_Are_Errors;
        }
    }

    return 0;
}

int Array_Labels_Dtor (array_labels_k* const Array_Labels)
{
    for (size_t i = 0; i < Array_Labels->Counter_Array_Labels; i++)
    {
        free (Array_Labels->Ptr_Array_Labels[i].Name_Label);
    }

    free (Array_Labels->Ptr_Array_Labels);

    return 0;
}
