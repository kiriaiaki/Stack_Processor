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
    int* Buffer_With_Bite_Code = (int*) calloc (Quantity_Line_Source * 2, sizeof (int));
    size_t Position_Last_Slash_N = 0;
    size_t Position_In_Buffer_With_Bite_Code = 0;

    for (int i = 0; i < Quantity_Line_Source; i++)
    {
        int Value = 0;
        int Number_Command = -1;

        char* Current_Line = Str_From_Buffer_Based_On_Slash_N (Buffer, &Position_Last_Slash_N, Size_Source);
        Number_Command = Read_Task (Current_Line, &Value);

        if (Number_Command == 1)
        {
            Buffer_With_Bite_Code[Position_In_Buffer_With_Bite_Code] = Number_Command;
            Position_In_Buffer_With_Bite_Code++;

            Buffer_With_Bite_Code[Position_In_Buffer_With_Bite_Code] = Value;
            Position_In_Buffer_With_Bite_Code++;
        }

        if (Number_Command != 1 && Number_Command != -1)
        {
            Buffer_With_Bite_Code[Position_In_Buffer_With_Bite_Code] = Number_Command;
            Position_In_Buffer_With_Bite_Code++;
        }

        free (Current_Line);
    }

    FILE* File_Source = fopen ("Bite_Code.txt", "w");
    fwrite (Buffer_With_Bite_Code, sizeof (int), Quantity_Line_Source * 2, File_Source);
    fclose (File_Source);
    
    free (Buffer);
    free (Buffer_With_Bite_Code);

    return 0;
}

int Read_Task (char* Str_With_Task, int *Value)
{
    //TODO very bad protect input!
    if (Str_With_Task[0] == 'P' && Str_With_Task[1] == 'U' && Str_With_Task[2] == 'S' && Str_With_Task[3] == 'H')
    {
       *Value = atoi (&Str_With_Task[5]);
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
    else
    {
        return Bad_Input;
    }
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

    if (stat ("Source.asm", &Data_Source) != 0)
    {
        return -1;
    }

    *Size_Source = Data_Source.st_size;

    const int File_Source = open ("Source.asm", O_RDONLY);

    *Buffer = (char*) calloc (*Size_Source, sizeof (char));

    if (read (File_Source, *Buffer, *Size_Source) < *Size_Source)
    {
        return -1;
    }

    close (File_Source);

    return 0;
}

