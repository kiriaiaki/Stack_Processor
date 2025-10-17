#include "Disassembler.h"

int main ()
{
    int* Byte_Code = Receiving_Byte_Code ();
    if (Byte_Code == NULL)
    {
        printf ("\n\033[31m!NOT START DISASSEMBLER!\n\033[0m\n");
        return 0;
    }
    if (Verifier_Byte_Code (Byte_Code) == There_Are_Errors)
    {
        printf ("\n\033[31m!NOT START DISASSEMBLER!\n\033[0m\n");
        return 0;
    }

    FILE* File_ASM = fopen ("disassembler.asm", "w");
    if (File_ASM == NULL)
    {
        printf ("\n\033[31m!NOT START DISASSEMBLER\n\033[0m!\n Error opening file for asm\n");
        return 0;

    }

    struct array_labels_k Array_Labels = {};

    if (Disassembly (Byte_Code, &Array_Labels, File_ASM) == There_Are_Errors)
    {
        printf ("\n\033[31m!NOT FINISH DISASSEMBLER!\n\033[0m\n");
        return 0;
    }

    if (fseek (File_ASM, 0L, SEEK_SET) != 0)
    {
        printf ("\n\033[31m!NOT FINISH DISASSEMBLER!\n\033[0m\n Error moving in file for asm\n");
        return 0;
    }

    if (Disassembly (Byte_Code, &Array_Labels, File_ASM) == There_Are_Errors)
    {
        printf ("\033[31m!NOT FINISH DISASSEMBLER!\033[0m\n");
        return 0;
    }

    printf ("\033[32mDecompilation was successful!\033[0m (in file disassembler.asm)\n");
    fclose (File_ASM);
    Array_Labels_Dtor (&Array_Labels);
    return 0;
}

int Disassembly (const int* const Byte_Code, array_labels_k* const Array_Labels, FILE* const File_ASM)
{
    size_t i = 3;

    while (i < size_t (Len_Byte_Code ()))
    {
        int a = Comparison_Programme_Counter_Label (Array_Labels, int (i));
        if (a != -1)
        {
            fprintf (File_ASM, "\n:%s\n", Array_Labels->Ptr_Array_Labels[a].Name_Label);
        }

        switch (Byte_Code[i])
        {
            case PUSH:
                i++;
                fprintf (File_ASM, "PUSH %d\n", Byte_Code[i]);
                break;
            case ADD:
                fprintf (File_ASM, "ADD\n");
                break;
            case SUB:
                fprintf (File_ASM, "SUB\n");
                break;
            case MUL:
                fprintf (File_ASM, "MUL\n");
                break;
            case DIV:
                fprintf (File_ASM, "DIV\n");
                break;
            case OUT:
                fprintf (File_ASM, "OUT\n");
                break;
            case PUSHREG:
                i++;
                fprintf (File_ASM, "PUSHREG ");
                if (Compare_Registers (Byte_Code[i], File_ASM) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case POPREG:
                i++;
                fprintf (File_ASM, "PUSHREG ");
                if (Compare_Registers (Byte_Code[i], File_ASM) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case JB:
                i++;
                fprintf (File_ASM, "JB :");
                if (Print_Label (File_ASM, Array_Labels, Byte_Code[i]) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case JBE:
                i++;
                fprintf (File_ASM, "JBE :");
                if (Print_Label (File_ASM, Array_Labels, Byte_Code[i]) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case JA:
                i++;
                fprintf (File_ASM, "JA :");
                if (Print_Label (File_ASM, Array_Labels, Byte_Code[i]) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case JAE:
                i++;
                fprintf (File_ASM, "JAE :");
                if (Print_Label (File_ASM, Array_Labels, Byte_Code[i]) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case JE:
                i++;
                fprintf (File_ASM, "JE :");
                if (Print_Label (File_ASM, Array_Labels, Byte_Code[i]) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case JNE:
                i++;
                fprintf (File_ASM, "JNE :");
                if (Print_Label (File_ASM, Array_Labels, Byte_Code[i]) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case JMP:
                i++;
                fprintf (File_ASM, "JMP :");
                if (Print_Label (File_ASM, Array_Labels, Byte_Code[i]) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case SQRT:
                fprintf (File_ASM, "SQRT\n");
                break;
            case IN:
                fprintf (File_ASM, "IN\n");
                break;
            case CALL:
                i++;
                fprintf (File_ASM, "CALL :");
                if (Print_Label (File_ASM, Array_Labels, Byte_Code[i]) == There_Are_Errors)
                {
                    return There_Are_Errors;
                }
                break;
            case RET:
                fprintf (File_ASM, "\nRET\n");
                break;
            case HLT:
                fprintf (File_ASM, "HLT\n");
                break;
            default:
                printf ("Command with number <%d> does not exist\n", Byte_Code[i]);
                return There_Are_Errors;
        }

        i++;
    }

    return 0;
}

int Len_Byte_Code ()
{
    struct stat Data_File_Byte_Code = {};

    if (stat (Name_File_Byte_Code, &Data_File_Byte_Code) != 0)
    {
        printf ("Error with stat file byte code\n");
        return There_Are_Errors;
    }

    int Len_Byte_Code = int (size_t (Data_File_Byte_Code.st_size) / sizeof(int));

    return Len_Byte_Code;
}

int* Receiving_Byte_Code ()
{
    if (Len_Byte_Code () == There_Are_Errors)
    {
        return NULL;
    }
    size_t Len = size_t (Len_Byte_Code ());

    int* Byte_Code = (int*) calloc (Len, sizeof (int));
    if (Byte_Code == NULL)
    {
        printf ("Error with allocation memory for byte code\n");
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

int Verifier_Byte_Code (const int* const Byte_Code)
{
    if (Byte_Code[0] != Password)
    {
        printf ("!START ERROR DISASSEMBLER! This byte code created not my assembler\n");
        return There_Are_Errors;
    }

    if (Byte_Code[1] != Version)
    {
        printf ("!START ERROR DISASSEMBLER! This byte code created not my assembler\n");
        return There_Are_Errors;
    }

    if (Byte_Code[2] > Number_Version_Disassembler)
    {
        printf ("!START ERROR DISASSEMBLER! Version Assembler newer than version Disassembler\n");
        return There_Are_Errors;
    }
    else if (Byte_Code[2] < Number_Version_Disassembler)
    {
        printf ("!POSSIBLE BUGS! Version Disassembler newer than version Assembler\n");
    }

    return 0;
}

int Compare_Registers (const int Number_Register, FILE* const File_ASM)
{
    switch (Number_Register)
    {
        case AX:
            fprintf (File_ASM, "AX\n");
            break;
        case BX:
            fprintf (File_ASM, "BX\n");
            break;
        case CX:
            fprintf (File_ASM, "CX\n");
            break;
        case DX:
            fprintf (File_ASM, "DX\n");
            break;
        default:
            printf ("Register with number <%d> does not exist\n", Number_Register);
            return There_Are_Errors;
    }

    return 0;
}

int Append_Label (array_labels_k* const Array_Labels, const int Programme_Counter)
{
    if (Array_Labels_Check_Reserve (Array_Labels) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    char* Name_New_Label = (char*) calloc (20, sizeof (char));
    if (Name_New_Label == NULL)
    {
        printf ("!ERROR IN DISASSEMBLER! Error allocating memory for name new label\n");
        return There_Are_Errors;

    }
    char* String_With_Number = (char*) calloc (17, sizeof (char));
    if (String_With_Number == NULL)
    {
        printf ("!ERROR IN DISASSEMBLER! Error allocating memory for string with number\n");
        return There_Are_Errors;

    }

    char Word[] = "Label_";
    itoa_k (int (Array_Labels->Counter_Array_Labels) + 1, String_With_Number);
    size_t Number = strlen (String_With_Number);

    for (size_t i = 0; i < 6; i++)
    {
        Name_New_Label[i] = Word[i];
    }
    for (size_t i = 6; i < Number + 6; i++)
    {
        Name_New_Label[i] = String_With_Number[i - 6];
    }

    Array_Labels->Ptr_Array_Labels[Array_Labels->Counter_Array_Labels].Name_Label = Name_New_Label;
    Array_Labels->Ptr_Array_Labels[Array_Labels->Counter_Array_Labels].Programme_Counter = size_t (Programme_Counter);
    Array_Labels->Counter_Array_Labels++;

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
            printf ("!ERROR IN DISASSEMBLER! Error allocating memory for array labels\n");
            return There_Are_Errors;
        }
    }

    return 0;
}

int Comparison_Programme_Counter_Label (const array_labels_k* const Array_Labels, const int Programme_Counter)
{
    for (size_t i = 0; i < Array_Labels->Counter_Array_Labels; i++)
    {
        if (Array_Labels->Ptr_Array_Labels[i].Programme_Counter == size_t (Programme_Counter))
        {
            return int (i);
        }
    }

    return -1;
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

int Reverse_Str (char* const Str)
{
    size_t i = 0;
    size_t j = strlen (Str) - 1;

    while (i < j)
    {
        char Symbol = Str[i];
        Str[i] = Str[j];
        Str[j] = Symbol;
        i++;
        j--;
    }

    return 0;
}

char* itoa_k (int Number, char* const Str)
{
    size_t i = 0;

    if (Number == 0)
    {
        Str[i] = '0';
        i++;

        Str[i] = '\0';

        return Str;
    }

    while (Number != 0)
    {
        int Rem = Number % 10;

        Str[i] = char (Rem) + '0';
        i++;

        Number = Number / 10;
    }

    Str[i] = '\0';

    Reverse_Str (Str);

    return Str;
}

int Print_Label (FILE* const File_ASM, array_labels_k* const Array_Labels, const int Programme_Counter)
{
    int Number_Label = Comparison_Programme_Counter_Label (Array_Labels, Programme_Counter);

    if (Number_Label == -1)
    {
        if (Append_Label (Array_Labels, Programme_Counter) == There_Are_Errors)
        {
            return There_Are_Errors;
        }

        fprintf (File_ASM, "%s\n\n", Array_Labels->Ptr_Array_Labels[size_t (Comparison_Programme_Counter_Label (Array_Labels, Programme_Counter))].Name_Label);
    }

    else
    {
        fprintf (File_ASM, "%s\n\n", Array_Labels->Ptr_Array_Labels[Number_Label].Name_Label);
    }

    return 0;
}
