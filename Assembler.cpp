#include "Assembler.h"

int main ()
{
    char* Buffer = Open_File_And_Copying_In_Buffer ();
    if (Buffer == NULL)
    {
        printf ("Error creating buffer\n");
        return 0;
    }

    struct byte_code_k Byte_Code = {};
    struct array_labels_k Array_Labels = {};

    Assembler (&Array_Labels, &Byte_Code, Buffer);

    Assembler (&Array_Labels, &Byte_Code, Buffer);

    FILE* File_Byte_Code = fopen (Name_File_Byte_Code, "w");
    fwrite (Byte_Code.Ptr_Byte_Code, sizeof (int), Byte_Code.Counter_Byte_Code, File_Byte_Code);
    fclose (File_Byte_Code);

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
            int Argument = 0;
            int Number_Command = Bad_Input;

            Buffer[i] = '\0';

            char* Current_Line = Ptr_Last_Slash_N;
            size_t Len_Current_Line = size_t (&Buffer[i] - Ptr_Last_Slash_N);
            Ptr_Last_Slash_N = &Buffer[i + 1];

            Number_Command = Read_Task (Current_Line, Array_Labels, &Argument, Len_Current_Line);

            switch (Number_Command)
            {
                case Bad_Input:
                    break;
                case LABEL:
                    Array_Labels->Ptr_Array_Labels[Argument].Programme_Counter = Byte_Code->Counter_Byte_Code;
                    break;
                default:
                    Byte_Code_Check_Reserve (Byte_Code);

                    Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Number_Command;
                    Byte_Code->Counter_Byte_Code++;

                    Byte_Code_Check_Reserve (Byte_Code);

                    switch (Number_Command)
                    {
                        case PUSH:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Argument;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        case PUSHREG:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Argument;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        case POPREG:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Argument;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        case JB:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Array_Labels->Ptr_Array_Labels[Argument].Programme_Counter;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        case JBE:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Array_Labels->Ptr_Array_Labels[Argument].Programme_Counter;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        case JA:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Array_Labels->Ptr_Array_Labels[Argument].Programme_Counter;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        case JAE:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Array_Labels->Ptr_Array_Labels[Argument].Programme_Counter;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        case JE:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Array_Labels->Ptr_Array_Labels[Argument].Programme_Counter;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        case JNE:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Array_Labels->Ptr_Array_Labels[Argument].Programme_Counter;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        case JMP:
                            Byte_Code->Ptr_Byte_Code[Byte_Code->Counter_Byte_Code] = Array_Labels->Ptr_Array_Labels[Argument].Programme_Counter;
                            Byte_Code->Counter_Byte_Code++;
                            break;
                        default:
                            break;
                    }
            }

            Buffer[i] = '\n';

        }

        i++;
    }

    return 0;
}

int Read_Task (const char* const Current_Line, array_labels_k* const Array_Labels, int* Argument, const size_t Len_Current_Line)
{
    char* Str_With_Task = (char*) calloc (Len_Current_Line, sizeof (char));
    char* Str_With_Register = (char*) calloc (Len_Current_Line, sizeof (char));
    sscanf (Current_Line, "%s %d", Str_With_Task, Argument);
    sscanf (Current_Line, "%s %s", Str_With_Task, Str_With_Register);
    // TODO bad protection
    if (Str_With_Task[0] == ':')
    {
        int Number = Comparison_Name_Label (Array_Labels, &Str_With_Task[1]);

        if (Number == -1)
        {
            Array_Labels_Check_Reserve (Array_Labels);

            Array_Labels->Ptr_Array_Labels[Array_Labels->Counter_Array_Labels].Name_Label = (char*) calloc (Len_Current_Line, sizeof (char));
            strcpy (Array_Labels->Ptr_Array_Labels[Array_Labels->Counter_Array_Labels].Name_Label, &Str_With_Task[1]);

            *Argument = Array_Labels->Counter_Array_Labels;
            Array_Labels->Counter_Array_Labels++;

        }

        else
        {
            *Argument = Number;
        }

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
       if (strcmp (Str_With_Register, "AX") == 0)
       {
            *Argument = AX;
            return PUSHREG;
       }
       else if (strcmp (Str_With_Register, "BX") == 0)
       {
            *Argument = BX;
            return PUSHREG;
       }
       else if (strcmp (Str_With_Register, "CX") == 0)
       {
            *Argument = CX;
            return PUSHREG;
       }
       else if (strcmp (Str_With_Register, "DX") == 0)
       {
            *Argument = DX;
            return PUSHREG;
       }
    }
    else if (strcmp (Str_With_Task, "POPREG") == 0)
    {
       if (strcmp (Str_With_Register, "AX") == 0)
       {
            *Argument = AX;
            return POPREG;
       }
       else if (strcmp (Str_With_Register, "BX") == 0)
       {
            *Argument = BX;
            return POPREG;
       }
       else if (strcmp (Str_With_Register, "CX") == 0)
       {
            *Argument = CX;
            return POPREG;
       }
       else if (strcmp (Str_With_Register, "DX") == 0)
       {
            *Argument = DX;
            return POPREG;
       }
    }
    else if (strcmp (Str_With_Task, "JB") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, &Str_With_Register[1]);
        return JB;
    }
    else if (strcmp (Str_With_Task, "JBE") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, &Str_With_Register[1]);
        return JBE;
    }
    else if (strcmp (Str_With_Task, "JA") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, &Str_With_Register[1]);
        return JA;
    }
    else if (strcmp (Str_With_Task, "JAE") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, &Str_With_Register[1]);
        return JAE;
    }
    else if (strcmp (Str_With_Task, "JE") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, &Str_With_Register[1]);
        return JE;
    }
    else if (strcmp (Str_With_Task, "JNE") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, &Str_With_Register[1]);
        return JNE;
    }
    else if (strcmp (Str_With_Task, "JMP") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, &Str_With_Register[1]);
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

    free (Str_With_Task);
    free (Str_With_Register);
    return 0;
}

char* Open_File_And_Copying_In_Buffer ()
{
    struct stat Data_File_Asm = {};

    if (stat (Name_File_Assembler, &Data_File_Asm) != 0)
    {
        return NULL;
    }

    ssize_t Size_File = Data_File_Asm.st_size;

    const int File_Asm = open (Name_File_Assembler, O_RDONLY);

    char* Buffer = (char*) calloc (size_t (Size_File), sizeof (char));

    if (read (File_Asm, Buffer, size_t (Size_File)) < Size_File)
    {
        return NULL;
    }

    close (File_Asm);

    return Buffer;
}

int Comparison_Name_Label (const array_labels_k* const Array_Labels, const char* const Name)
{
    for (size_t i = 0; i < Array_Labels->Counter_Array_Labels; i++)
    {
        if (strcmp (Array_Labels->Ptr_Array_Labels[i].Name_Label, Name) == 0)
        {
            return int (i);
        }
    }

    return -1;
}

int Array_Labels_Check_Reserve (array_labels_k* const Array_Labels)
{
    if (Array_Labels->Counter_Array_Labels == Array_Labels->Len_Array_Labels - 1)
    {
        Array_Labels->Len_Array_Labels = Array_Labels->Len_Array_Labels * 2;
        Array_Labels->Ptr_Array_Labels = (label_k*) realloc (Array_Labels->Ptr_Array_Labels, Array_Labels->Len_Array_Labels * sizeof (label_k));
    }

    return 0;
}

int Byte_Code_Check_Reserve (byte_code_k* const Byte_Code)
{
    if (Byte_Code->Counter_Byte_Code == Byte_Code->Len_Byte_Code - 1)
    {
        Byte_Code->Len_Byte_Code = Byte_Code->Len_Byte_Code * 2;
        Byte_Code->Ptr_Byte_Code = (int*) realloc (Byte_Code->Ptr_Byte_Code, Byte_Code->Len_Byte_Code * sizeof (int));
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
