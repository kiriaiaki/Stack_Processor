#include "Assembler.h"

int main ()
{
    char* Buffer = (char*) calloc (1, sizeof (char));
    if (Buffer == NULL)
    {
        return 0;
    }
    ssize_t Size_File = 0;
    if (Open_File_And_Copying_In_Buffer (&Buffer, &Size_File) == -1)
    {
        return 0;
    }

    int* Byte_Code = (int*) calloc (size_t (Size_File) / 2, sizeof (int));
    if (Byte_Code == NULL)
    {
        return 0;
    }
    // TODO Size_Source very big and 10
    struct label_k* Array_Labels = (label_k*) calloc (10, sizeof (label_k));
    if (Array_Labels == NULL)
    {
        return 0;
    }
    size_t Counter_Label = 0;

    Assembler (Array_Labels, &Counter_Label, Byte_Code, Buffer);

    size_t Len_Byte_Code = Assembler (Array_Labels, &Counter_Label, Byte_Code, Buffer);

    FILE* File_Byte_Code = fopen (Name_File_Byte_Code, "w");
    fwrite (Byte_Code, sizeof (int), Len_Byte_Code, File_Byte_Code);
    fclose (File_Byte_Code);

    free (Buffer);
    free (Byte_Code);
    free (Array_Labels);

    return 0;
}

size_t Assembler (label_k* const Array_Labels, size_t* const Counter_Label, int* const Byte_Code, char* const Buffer)
{
    size_t i = 0;
    char* Ptr_Last_Slash_N = Buffer;
    size_t Position_In_Byte_Code = 0;

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

            Number_Command = Read_Task (Current_Line, Array_Labels, Counter_Label, &Argument, Len_Current_Line);

            switch (Number_Command)
            {
                case Bad_Input:
                    break;
                case LABEL:
                    Array_Labels[Argument].Programme_Counter = Position_In_Byte_Code;
                    break;
                default:
                    Byte_Code[Position_In_Byte_Code] = Number_Command;
                    Position_In_Byte_Code++;

                    switch (Number_Command)
                    {
                        case PUSH:
                            Byte_Code[Position_In_Byte_Code] = Argument;
                            Position_In_Byte_Code++;
                            break;
                        case PUSHREG:
                            Byte_Code[Position_In_Byte_Code] = Argument;
                            Position_In_Byte_Code++;
                            break;
                        case POPREG:
                            Byte_Code[Position_In_Byte_Code] = Argument;
                            Position_In_Byte_Code++;
                            break;
                        case JB:
                            Byte_Code[Position_In_Byte_Code] = Array_Labels[Argument].Programme_Counter;
                            Position_In_Byte_Code++;
                            break;
                        case JBE:
                            Byte_Code[Position_In_Byte_Code] = Array_Labels[Argument].Programme_Counter;
                            Position_In_Byte_Code++;
                            break;
                        case JA:
                            Byte_Code[Position_In_Byte_Code] = Array_Labels[Argument].Programme_Counter;
                            Position_In_Byte_Code++;
                            break;
                        case JAE:
                            Byte_Code[Position_In_Byte_Code] = Array_Labels[Argument].Programme_Counter;
                            Position_In_Byte_Code++;
                            break;
                        case JE:
                            Byte_Code[Position_In_Byte_Code] = Array_Labels[Argument].Programme_Counter;
                            Position_In_Byte_Code++;
                            break;
                        case JNE:
                            Byte_Code[Position_In_Byte_Code] = Array_Labels[Argument].Programme_Counter;
                            Position_In_Byte_Code++;
                            break;
                        case JMP:
                            Byte_Code[Position_In_Byte_Code] = Array_Labels[Argument].Programme_Counter;
                            Position_In_Byte_Code++;
                            break;
                        default:
                            break;
                    }
            }

            Buffer[i] = '\n';

        }

        i++;
    }

    return Position_In_Byte_Code;
}

int Read_Task (const char* const Current_Line, label_k* const Array_Labels, size_t* Counter_Label, int* Argument, const size_t Len_Current_Line)
{
    char Str_With_Task[Len_Current_Line];
    char Str_With_Register[Len_Current_Line];
    sscanf (Current_Line, "%s %d", Str_With_Task, Argument);
    sscanf (Current_Line, "%s %s", Str_With_Task, Str_With_Register);
    // TODO bad protection

    if (Str_With_Task[0] == ':')
    {
        int Number = Comparison_Name_Label (Array_Labels, *Counter_Label, &Str_With_Task[1]);

        if (Number == -1)
        {
            strcpy (Array_Labels[*Counter_Label].Name_Label, &Str_With_Task[1]);
            // TODO why not work  Array_Labels[*Counter_Label].Name_Label = &Str_With_Task[1]
            *Argument = *Counter_Label;
            *Counter_Label = *Counter_Label + 1;
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
        *Argument = Comparison_Name_Label (Array_Labels, *Counter_Label, &Str_With_Register[1]);
        return JB;
    }
    else if (strcmp (Str_With_Task, "JBE") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, *Counter_Label, &Str_With_Register[1]);
        return JBE;
    }
    else if (strcmp (Str_With_Task, "JA") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, *Counter_Label, &Str_With_Register[1]);
        return JA;
    }
    else if (strcmp (Str_With_Task, "JAE") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, *Counter_Label, &Str_With_Register[1]);
        return JAE;
    }
    else if (strcmp (Str_With_Task, "JE") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, *Counter_Label, &Str_With_Register[1]);
        return JE;
    }
    else if (strcmp (Str_With_Task, "JNE") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, *Counter_Label, &Str_With_Register[1]);
        return JNE;
    }
    else if (strcmp (Str_With_Task, "JMP") == 0)
    {
        *Argument = Comparison_Name_Label (Array_Labels, *Counter_Label, &Str_With_Register[1]);
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

    return 0;
}

int Open_File_And_Copying_In_Buffer (char** Buffer, ssize_t* Size_File)
{
    struct stat Data_File_Asm = {};

    if (stat (Name_File_Assembler, &Data_File_Asm) != 0)
    {
        return -1;
    }

    *Size_File = Data_File_Asm.st_size;

    const int File_Asm = open (Name_File_Assembler, O_RDONLY);

    *Buffer = (char*) calloc (size_t (*Size_File), sizeof (char));
    if (*Buffer == NULL)
    {
        return -1;
    }

    if (read (File_Asm, *Buffer, size_t (*Size_File)) < *Size_File)
    {
        return -1;
    }

    close (File_Asm);

    return 0;
}

int Comparison_Name_Label (const label_k* const Array_Labels, const size_t Counter_Label, const char* const Name)
{
    for (size_t i = 0; i < Counter_Label; i++)
    {
        if (strcmp (Array_Labels[i].Name_Label, Name) == 0)
        {
            return int (i);
        }
    }

    return -1;
}
