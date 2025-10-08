#include "Assembler.h"

int main ()
{
    char* Buffer = (char*) calloc (1, sizeof (char));
    size_t Size_Source = 0;

    if (Open_File_And_Copying_In_Buffer (&Buffer, &Size_Source) != 0)
    {
        return 0;
    }

    int Quantity_Line_Source = Counter_Symbol_In_Str (Buffer, '\n');
    int* Buffer_With_Byte_Code = (int*) calloc (Quantity_Line_Source * 2, sizeof (int));
    size_t Position_Last_Slash_N = 0;
    size_t Position_In_Buffer_With_Byte_Code = 0;

    for (int i = 0; i < Quantity_Line_Source; i++)
    {
        int Value = 0;
        int Number_Command = -1;

        char* Current_Line = Str_From_Buffer_Based_On_Slash_N (Buffer, &Position_Last_Slash_N, Size_Source);
        Number_Command = Read_Task (Current_Line, &Value);

        switch (Number_Command)
        {
            case Bad_Input:
                break;
            default:
                Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Number_Command;
                Position_In_Buffer_With_Byte_Code++;

                switch (Number_Command)
                {
                    case PUSH:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                    case PUSHREG:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                    case POPREG:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                    case JB:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                    case JBE:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                    case JA:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                    case JAE:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                    case JE:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                    case JNE:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                    case JMP:
                        Buffer_With_Byte_Code[Position_In_Buffer_With_Byte_Code] = Value;
                        Position_In_Buffer_With_Byte_Code++;
                        break;
                }
        }

        free (Current_Line);
    }

    FILE* File_Source = fopen (Name_File_Byte_Code, "w");
    fwrite (Buffer_With_Byte_Code, sizeof (int), Quantity_Line_Source * 2, File_Source);
    fclose (File_Source);

    free (Buffer);
    free (Buffer_With_Byte_Code);

    return 0;
}

int Read_Task (char* Str_With_Task_And_Value, int *Value)
{
    char Str_With_Task[30] = " ";
    char Str_With_Register[30] = " ";
    sscanf (Str_With_Task_And_Value, "%s %d", Str_With_Task, Value);
    sscanf (Str_With_Task_And_Value, "%s %s", Str_With_Task, Str_With_Register);
    //TODO very bad protect input!
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
            *Value = AX;
            return PUSHREG;
       }
       else if (strcmp (Str_With_Register, "BX") == 0)
       {
            *Value = BX;
            return PUSHREG;
       }
       else if (strcmp (Str_With_Register, "CX") == 0)
       {
            *Value = CX;
            return PUSHREG;
       }
       else if (strcmp (Str_With_Register, "DX") == 0)
       {
            *Value = DX;
            return PUSHREG;
       }
    }
    else if (strcmp (Str_With_Task, "POPREG") == 0)
    {
       if (strcmp (Str_With_Register, "AX") == 0)
       {
            *Value = AX;
            return POPREG;
       }
       else if (strcmp (Str_With_Register, "BX") == 0)
       {
            *Value = BX;
            return POPREG;
       }
       else if (strcmp (Str_With_Register, "CX") == 0)
       {
            *Value = CX;
            return POPREG;
       }
       else if (strcmp (Str_With_Register, "DX") == 0)
       {
            *Value = DX;
            return POPREG;
       }
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
    else
    {
        return Bad_Input;
    }
    return 0;
}

char* Str_From_Buffer_Based_On_Slash_N (char* Buffer, size_t *Position_Last_Slash_N, const size_t Size_Source)
{
    char* Now_Line = (char*) calloc (100, sizeof(char));
    size_t Position_In_Now_Line = 0;

    for (size_t j = *Position_Last_Slash_N; j < Size_Source; j++)
        {
            if (Buffer[j] == '\n')
            {
                *Position_Last_Slash_N = j + 1;
                break;
            }

            Now_Line[Position_In_Now_Line] = Buffer[j];
            Position_In_Now_Line++;
        }

    return Now_Line;
}

int Counter_Symbol_In_Str (const char* const Str, const char Symbol)
{
    size_t i = 0;
    int Counter = 0;

    while (Str[i] != '\0')
    {
        if (Str[i] == Symbol)
        {
            Counter++;
        }

        i++;
    }

    return Counter;
}

int Open_File_And_Copying_In_Buffer (char** Buffer, size_t* Size_Source)
{
    struct stat Data_Source = {};

    if (stat (Name_File_Assembler, &Data_Source) != 0)
    {
        return -1;
    }

    *Size_Source = Data_Source.st_size;

    const int File_Source = open (Name_File_Assembler, O_RDONLY);

    *Buffer = (char*) calloc (*Size_Source, sizeof (char));

    if (read (File_Source, *Buffer, *Size_Source) < *Size_Source)
    {
        return -1;
    }

    close (File_Source);

    return 0;
}

