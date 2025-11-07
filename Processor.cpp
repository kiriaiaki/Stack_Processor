#include "Processor.h"

#include <termios.h> // Для работы с терминалом
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
// Глобальная переменная для хранения исходных настроек терминала
struct termios orig_termios;
// Функция для сброса настроек терминала при выходе из программы
void reset_terminal_mode()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void set_conio_mode()
{
    struct termios new_termios;

    // Получаем текущие настройки терминала
    tcgetattr(STDIN_FILENO, &orig_termios);

    // Устанавливаем функцию сброса настроек при завершении программы
    atexit(reset_terminal_mode);

    // Копируем текущие настройки в новый набор
    new_termios = orig_termios;

    // Отключаем канонический режим (ICANON) и эхо-режим (ECHO)
    new_termios.c_lflag &= ~(ICANON | ECHO);

    // Устанавливаем минимальное количество символов для чтения (1)
    new_termios.c_cc[VMIN] = 1;
    // Устанавливаем таймаут (0, так как select() сам обрабатывает время)
    new_termios.c_cc[VTIME] = 0;

    // Применяем новые настройки немедленно (TCSANOW)
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

int timed_getchar_no_enter (int milliseconds)
{
    fd_set set;
    struct timeval timeout;
    struct timeval start_time, current_time;
    long elapsed_ms, remaining_ms;
    int rv;
    char buffer;
    int result_char = 0; // 0 или символ

    // Запоминаем время начала операции
    gettimeofday(&start_time, NULL);

    // Устанавливаем время ожидания для select() равное общему времени
    timeout.tv_sec = milliseconds / 1000;
    timeout.tv_usec = (milliseconds % 1000) * 1000;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    // Ожидание ввода с таймаутом
    // select() изменит структуру timeout, показав оставшееся время при успешном вводе
    rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

    if (rv > 0)
    {
        // Ввод успешен, читаем символ
        if (read(STDIN_FILENO, &buffer, 1) == 1)
        {
            result_char = (int)buffer;
        }
    }
    // Если rv <= 0 (таймаут или ошибка), buffer не читается

    // --- Логика принудительной задержки до общего времени ---

    // Получаем текущее время после select() и потенциального чтения
    gettimeofday(&current_time, NULL);

    // Вычисляем, сколько времени прошло в миллисекундах
    elapsed_ms = (current_time.tv_sec - start_time.tv_sec) * 1000L +
                 (current_time.tv_usec - start_time.tv_usec) / 1000L;

    // Вычисляем оставшееся время
    remaining_ms = milliseconds - elapsed_ms;

    // Если осталось время, делаем паузу
    if (remaining_ms > 0) {
        // Используем usleep (мкс) или nanosleep (нс)
        usleep(remaining_ms * 1000L);
    }

    // Возвращаем результат ввода (0 если не было ввода, или символ)
    return result_char;
}

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

    // TODO костыль общий массив структур почему так? не знаю как по другому (тк требует функцию!) (попробовать переместить)
    // TODO квадратные скобки у функций с памятью (проблема с массивом структур)
    // TODO рабочий файл через командную строку
    // TODO хеширование подшарить шаблоный класс спросить андрюху
    // TODO библиотека дифайнов

    printf ("\033[32mProcessor worked successful!\033[0m\n");
    Processor_Dtor (&Processor);
    return 0;
}

int Run (processor_k* const Processor)
{
    int Current_Number_Command = Processor->Array_Byte_Code[Processor->Programme_Counter];

    while (Current_Number_Command != HLT)
    {
        int Value = 0;

        if (Array_Command[Current_Number_Command].Fun_Processor != NULL)
        {
           if ((*Array_Command[Current_Number_Command].Fun_Processor) (Processor, Current_Number_Command) == There_Are_Errors)
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
    }

    return Not_Error_Processor;
}


int Processor_Ctor (processor_k* const Processor)
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

    return Not_Error_Processor;
}

int Processor_Error (const processor_k* const Processor)
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

int Processor_Dump (const processor_k* const Processor)
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

int Processor_Dtor (processor_k* const Processor)
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


int Processor_Pushs (processor_k* const Processor, const int Number_Command)
{
    Processor->Programme_Counter++;
    int Value = Processor->Array_Byte_Code[Processor->Programme_Counter];

    switch (Number_Command)
    {
        case PUSH:
            if (Stack_Push (&Processor->Stack, Value) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;

        case PUSHREG:
            if (Stack_Push (&Processor->Stack, Processor->Array_Register[Value]) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;

        case PUSHMEM:
            int Cell_Ram = Processor->Array_Register[Value];
            int Element_Cell_Ram = Processor->Random_Access_Memory[Cell_Ram];

            if (Stack_Push (&Processor->Stack, Element_Cell_Ram) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
    }

    return Not_Error_Processor;
}

int Processor_Pops (processor_k* const Processor, const int Number_Command)
{
    Processor->Programme_Counter++;
    int Number_Register = Processor->Array_Byte_Code[Processor->Programme_Counter];

    int Value = Stack_Pop (&Processor->Stack);
    if (Value == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int Cell_Ram = 0;

    switch (Number_Command)
    {
        case POPMEM:
            Cell_Ram = Processor->Array_Register[Number_Register];
            Processor->Random_Access_Memory[Cell_Ram] = Value;
            break;

        case POPREG:
            Processor->Array_Register[Number_Register] = Value;
            break;
    }

    return Not_Error_Processor;
}

int Processor_Math (processor_k* const Processor, const int Number_Command)
{
    int A2 = Stack_Pop (&Processor->Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Pop (&Processor->Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    switch (Number_Command)
    {
        case ADD:
            if (Stack_Push (&Processor->Stack, A1 + A2) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;

        case SUB:
            if (Stack_Push (&Processor->Stack, A1 - A2) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;

        case MUL:
            if (Stack_Push (&Processor->Stack, A1 * A2) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;

        case DIV:
            if (A2 == 0)
            {
                printf ("Error in command DIV division by zero\n");
                return There_Are_Errors;
            }

            if (Stack_Push (&Processor->Stack, A1 / A2) == There_Are_Errors)
            {
                return There_Are_Errors;
            }
            break;
    }

    return Not_Error_Processor;
}

int Processor_Sqrt (processor_k* const Processor, const int Number_Command)
{
    int A1 = Stack_Pop (&Processor->Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    if (Stack_Push (&Processor->Stack, int (sqrt (A1))) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return Not_Error_Processor;
}

int Processor_Conditional_Jump (processor_k* const Processor, const int Number_Command)
{
    int A2 = Stack_Pop (&Processor->Stack);
    if (A2 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int A1 = Stack_Pop (&Processor->Stack);
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
                Jump (&Processor->Programme_Counter, Location_Jump);
            }
            break;

        case JBE:
            if (A1 <= A2)
            {
                Jump (&Processor->Programme_Counter, Location_Jump);
            }
            break;

        case JA:
            if (A1 > A2)
            {
                Jump (&Processor->Programme_Counter, Location_Jump);
            }
            break;

        case JAE:
            if (A1 >= A2)
            {
                Jump (&Processor->Programme_Counter, Location_Jump);
            }
            break;

        case JE:
            if (A1 == A2)
            {
                Jump (&Processor->Programme_Counter, Location_Jump);
            }
            break;

        case JNE:
            if (A1 != A2)
            {
                Jump (&Processor->Programme_Counter, Location_Jump);
            }
            break;
    }

    return Not_Error_Processor;
}

int Processor_Jump (processor_k* const Processor, const int Number_Command)
{
    Processor->Programme_Counter++;
    int Location_Jump = Processor->Array_Byte_Code[Processor->Programme_Counter];

    Jump (&Processor->Programme_Counter, Location_Jump);

    return Not_Error_Processor;
}

int Processor_In (processor_k* const Processor, const int Number_Command)
{
//     char Value[150];
//
//     printf ("Value : ");
//     scanf ("%[^\n]", Value);
//     getchar ();
//
//     while (Check_Input (Value) != 0)
//     {
//         printf ("Value : ");
//         scanf ("%[^\n]", Value);
//         getchar ();
//     }

    set_conio_mode();

    int timeout_millisec = 70;

    int Value = timed_getchar_no_enter(timeout_millisec);

    if (Stack_Push (&Processor->Stack, Value) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return Not_Error_Processor;
}

int Processor_Out (processor_k* const Processor, const int Number_Command)
{
    int A1 = Stack_Pop (&Processor->Stack);
    if (A1 == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    printf ("%d\n", A1);

    return Not_Error_Processor;
}

int Processor_Call (processor_k* const Processor, const int Number_Command)
{
    Processor->Programme_Counter++;
    int Location_Function = Processor->Array_Byte_Code[Processor->Programme_Counter];

    if (Stack_Push (&Processor->Return_Stack, Processor->Programme_Counter + 1) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Processor->Programme_Counter = Location_Function - 1;

    return Not_Error_Processor;
}

int Processor_Return (processor_k* const Processor, const int Number_Command)
{
    int Location_Return = Stack_Pop (&Processor->Return_Stack);
    if (Location_Return == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    Jump (&Processor->Programme_Counter, Location_Return);

    return Not_Error_Processor;
}

int Processor_Draw (processor_k* const Processor, const int Number_Command)
{
    printf ("\033[H\033[J");
    fflush(stdout);

    for (size_t i = 0; i < 9*5 * 16*5 * 2; i+=2)
    {
        printf ("\033[%dm%c \033[0m", Processor->Random_Access_Memory[i + 1], Processor->Random_Access_Memory[i]);

        if (i % (80 * 2) == 79 * 2)
        {
            printf ("\n");
        }
    }

    usleep (30000);

    return 0;
}

int Processor_Random (processor_k* const Processor, const int Number_Command)
{
    srand(time(NULL));

    int Size = Stack_Pop (&Processor->Stack);
    if (Size == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    int Value = 2 + ((rand() % Size) * 5); // (число от 0 до Size)*5 + 2

    if (Stack_Push (&Processor->Stack, Value) == There_Are_Errors)
    {
        return There_Are_Errors;
    }

    return Not_Error_Processor;
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

int Delete_Ram (int* const Random_Access_Memory)
{
    free (Random_Access_Memory);
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

int Jump (size_t* const Programme_Counter , const size_t Location_Jump)
{
    *Programme_Counter = Location_Jump - 1;

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

int Verifier_Byte_Code (const processor_k* const Processor)
{
    if (Processor->Array_Byte_Code[0] != Password_Processor)
    {
        printf ("Password doesn't work\n Likely this byte code created not my assembler\n");
        return There_Are_Errors;
    }

    if (Processor->Array_Byte_Code[1] != Version_Processor)
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
