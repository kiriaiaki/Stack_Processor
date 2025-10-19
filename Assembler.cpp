#include "Assembler.h"

int main ()
{
    printf ("\033[34mWork with file: %s\033[0m\n", Name_File_Assembler);

    char* Buffer = Open_File_And_Copying_In_Buffer ();
    if (Buffer == NULL)
    {
        printf ("\033[31m!NOT START ASSEMBLER!\033[0m \nError allocating memory for buffer\n");
        return 0;
    }

    struct byte_code_k Byte_Code = {};
    if (Byte_Code.Ptr_Byte_Code == NULL)
    {
        printf ("\033[31m!NOT START ASSEMBLER!\033[0m \nError allocating memory for byte code\n");
        return 0;
    }
    Byte_Code.Ptr_Byte_Code[0] = Password;
    Byte_Code.Ptr_Byte_Code[1] = Version;
    Byte_Code.Ptr_Byte_Code[2] = Number_Version_Assembler;

    struct array_labels_k Array_Labels = {};
    if (Array_Labels.Ptr_Array_Labels == NULL)
    {
        printf ("\033[31m!NOT START ASSEMBLER!\033[0m\n Error allocating memory for array labels\n");
        return 0;
    }
    Array_Labels.Ptr_Array_Labels[0].Name_Label = (char*) calloc (10, sizeof (char));
    strcpy (Array_Labels.Ptr_Array_Labels[0].Name_Label, "Not_Find");
    Array_Labels.Ptr_Array_Labels[0].Programme_Counter = -1;
    Array_Labels.Counter_Array_Labels++;

    if (Assembly (&Array_Labels, &Byte_Code, Buffer) == There_Are_Errors)
    {
        printf ("\033[31m!ASSEMBLER NOT FINISH!\033[0m\n");
        return 0;
    }
    Byte_Code.Counter_Byte_Code = 3;
    if (Assembly (&Array_Labels, &Byte_Code, Buffer) == There_Are_Errors)
    {
        printf ("\033[31m!ASSEMBLER NOT FINISH!\033[0m\n");
        return 0;
    }

    if (Check_Correct_Label (&Byte_Code) == There_Are_Errors)
    {
        printf ("\033[31m!ASSEMBLER NOT FINISH!\033[0m\n");
        return 0;
    }
    FILE* File_Byte_Code = fopen (Name_File_Byte_Code, "w");
    if (File_Byte_Code == NULL)
    {
        printf ("\033[31m!ASSEMBLER NOT FINISH!\033[0m\n Error opening file for byte code\n");
        return 0;

    }
    if (fwrite (Byte_Code.Ptr_Byte_Code, sizeof (int), Byte_Code.Counter_Byte_Code, File_Byte_Code) < Byte_Code.Counter_Byte_Code)
    {
        printf ("\033[31m!ASSEMBLER NOT FINISH!\033[0m\n Error writing in file for byte code\n");
        return 0;
    }
    fclose (File_Byte_Code);

    printf ("\033[32mCompilation was successful!\033[0m\n");
    free (Buffer);
    free (Byte_Code.Ptr_Byte_Code);
    Array_Labels_Dtor (&Array_Labels);
    return 0;
}

int Assembly (array_labels_k* const Array_Labels, byte_code_k* const Byte_Code, char* const Buffer)
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

            if (Read_Task (Current_Line, Len_Current_Line, Byte_Code, Array_Labels) == There_Are_Errors)
            {
                return There_Are_Errors;
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
            case CALL:
                if (Byte_Code->Ptr_Byte_Code[i + 1] == -1)
                {
                    printf ("You have CALL with programme counter <%zu> on incorrect label\n", i);
                    return There_Are_Errors;
                }
                break;
            default:
                break;
        }
    }

    return 0;
}

int Read_Task (const char* const Current_Line, const size_t Len_Current_Line, byte_code_k* const Byte_Code, array_labels_k* const Array_Labels)
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
        int Number_Label = (*Array_Command[LABEL].Read_Argument) (Current_Line, Len_Current_Line, Array_Labels);
        if (Number_Label == There_Are_Errors)
        {
            return There_Are_Errors;
        }
        Array_Labels->Ptr_Array_Labels[Number_Label].Programme_Counter = int (Byte_Code->Counter_Byte_Code);
        return 0;
    }

    for (size_t Number_Command = 0; Number_Command < Quantity_Commands; Number_Command++)
    {
        if (strcmp (Array_Command[Number_Command].Name_Command, Str_With_Task) == 0)
        {
            if (Append_In_Byte_Code (Byte_Code, Number_Command) == There_Are_Errors)
            {
                return There_Are_Errors;
            }

            if (Array_Command[Number_Command].Append_Argument == 1)
            {
                int Value = (*Array_Command[Number_Command].Read_Argument) (Current_Line, Len_Current_Line, Array_Labels);

                if (Value == There_Are_Errors)
                {
                    return There_Are_Errors;
                }

                if (Append_In_Byte_Code (Byte_Code, Value) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }

            }

            free (Str_With_Task);
            return 0;
        }
    }

    for (size_t k = 0; k < Len_Current_Line - 1; k++)
    {
        if (Current_Line[k] != ' ')
        {
            printf ("<%s> This string incorrect\n"
                    "now programme counter = %zu\n", Current_Line, Byte_Code->Counter_Byte_Code);
            free (Str_With_Task);
            return There_Are_Errors;
        }
    }

    free (Str_With_Task);
    return 0;
}

int Read_Number (const char* const Current_Line, const size_t Len_Current_Line, array_labels_k* const Array_Labels)
{
    char* Str_With_Task = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Task == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with task\n");
        return There_Are_Errors;
    }
    char* Str_With_Number = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Number == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with arguments\n");
        return There_Are_Errors;
    }

    sscanf (Current_Line, "%s %s", Str_With_Task, Str_With_Number);

    for (size_t i = 0; i < Len_Current_Line; i++)
    {
        if (Str_With_Number[i] == '\0')
        {
            break;
        }

        if ('0' > Str_With_Number[i] || Str_With_Number[i] > '9')
        {
            if (i == 0 && Str_With_Number[i] == '-')
            {
                continue;
            }

            else
            {
                printf ("<%s> \nThis string incorrect, argument push not a number\n", Current_Line);
                free (Str_With_Task);
                free (Str_With_Number);
                return There_Are_Errors;
            }
        }
    }

    int Number = atoi (Str_With_Number);
    free (Str_With_Task);
    free (Str_With_Number);
    return Number;
}

int Append_Argument (byte_code_k* const Byte_Code, const int Value, const int Number_Command, array_labels_k* const Array_Labels)
{

    return 0;
}

int Read_Label (const char* const Current_Line, const size_t Len_Current_Line, array_labels_k* const Array_Labels)
{
    char* Str_With_Task = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Task == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with task\n");
        return There_Are_Errors;
    }
    char* Str_With_Label = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Label == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with arguments\n");
        return There_Are_Errors;
    }

    sscanf (Current_Line, "%s %s", Str_With_Task, Str_With_Label);

    if (Str_With_Label[0] == ':')
    {
        int Number_Label = Comparison_Name_Label (Array_Labels, &Str_With_Label[1]);

        free (Str_With_Label);
        free (Str_With_Task);
        return Array_Labels->Ptr_Array_Labels[Number_Label].Programme_Counter;
    }

    free (Str_With_Label);
    free (Str_With_Task);
    printf ("<%s> \n This string incorrect, label must begin :\n", Current_Line);
    return There_Are_Errors;
}

int Read_Register (const char* const Current_Line, const size_t Len_Current_Line, array_labels_k* const Array_Labels)
{
    char* Str_With_Task = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Task == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with task\n");
        return There_Are_Errors;
    }
    char* Str_With_Register = (char*) calloc (Len_Current_Line, sizeof (char));
    if (Str_With_Register == NULL)
    {
        printf ("!ERROR IN ASSEMBLER! Error allocation memory for string with arguments\n");
        return There_Are_Errors;
    }

    sscanf (Current_Line, "%s %s", Str_With_Task, Str_With_Register);

    for (size_t Number_Register = 0; Number_Register < Quantity_Registers; Number_Register++)
    {
        if (strcmp (Str_With_Register, Array_Register[Number_Register].Name_Register) == 0)
        {
            free (Str_With_Task);
            free (Str_With_Register);
            return Number_Register;
        }
    }

    free (Str_With_Task);
    free (Str_With_Register);
    printf ("<%s> \n This string incorrect, this register doesn't exist\n", Current_Line);
    return There_Are_Errors;
}

int Addition_Label (const char* const Current_Line, const size_t Len_Current_Line, array_labels_k* const Array_Labels)
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
