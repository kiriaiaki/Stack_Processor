CALL :Start

:Main
    IN
    POPREG Color // удаление в ненужный регистр

    CALL :Check_Correct_Input

    :Next_Main
        PUSHREG Direction
        PUSH 107 // k - end
        JE :Finish

        PUSHREG Direction
        CALL :Move

        CALL :Check_Rip_Border

        CALL :Check_Kick_Yourself

        PUSHREG X_1           // check apple
        PUSHREG X_A           //
        JE :Conditional_Apple //

        JMP :Main

:Finish
    CALL :Paint_Rip
    DRAW
    HLT

:Check_Correct_Input
    PUSHREG Color
    PUSH 100 // d
    JE :Verification

    PUSHREG Color
    PUSH 119 // w
    JE :Verification

    PUSHREG Color
    PUSH 115 // s
    JE :Verification

    PUSHREG Color
    PUSH 97 // a
    JE :Verification

    PUSHREG Color
    PUSH 107 // k
    JE :Verification

    RET

:Verification
    PUSHREG Color      / check reverse
    PUSHREG Direction  /
    PUSH 3             /
    SUB                /
    JE :Next_Main      /

    PUSHREG Color      /
    PUSHREG Direction  /
    PUSH 3             /
    ADD                /
    JE :Next_Main      /

    PUSHREG Color      /
    PUSHREG Direction  /
    PUSH 4             /
    SUB                /
    JE :Next_Main      /

    PUSHREG Color      /
    PUSHREG Direction  /
    PUSH 4             /
    ADD                /
    JE :Next_Main      /

    PUSHREG Color
    POPREG Direction
    JMP :Next_Main

:Conditional_Apple
    PUSHREG Y_1
    PUSHREG Y_A
    JE :Change_Apple

    JMP :Main

:Change_Apple
    PUSHREG Score
    PUSH 1
    ADD
    POPREG Score

    PUSHREG Score
    PUSH 29
    JE :Print_Win

    PUSHREG Len
    PUSH 1
    ADD
    POPREG Len

    PUSH 7200     / new
    PUSHREG Len   /
    PUSH 2        /
    MUL           /
    ADD           /
    PUSH 3        /
    SUB           /
    POPREG Color  /

    PUSHMEM Color /

    PUSHREG Color /
    PUSH 2        /
    ADD           /
    POPREG Color  /

    POPMEM Color  /

    PUSHREG Color /
    PUSH 1        /
    SUB           /
    POPREG Color  /

    PUSHMEM Color /

    PUSHREG Color /
    PUSH 2        /
    ADD           /
    POPREG Color  /

    POPMEM Color  /

    :Repeat_Change_Apple
    PUSH 16
    RANDOM
    POPREG X_A

    PUSH 9
    RANDOM
    POPREG Y_A

    CALL :Check_Bad_Apple

    JMP :Main

:Move
    POPREG Direction

    PUSHREG Direction
    PUSH 100 // d
    JE :Right

    PUSHREG Direction
    PUSH 119 // w
    JE :Up

    PUSHREG Direction
    PUSH 115 // s
    JE :Down

    PUSHREG Direction
    PUSH 97 // a
    JE :Left

    RET

    :Mini_Move

    PUSH 34 // синий
    CALL :Paint_All_Dot

    PUSH 32 // зеленый
    CALL :Paint_Field

    PUSHREG X_A
    PUSHREG Y_A
    PUSH 3
    PUSH 31 // красный
    CALL :Paint_Circle

    PUSHREG X_1
    PUSHREG Y_1
    PUSH 3
    PUSH 33 // желтый
    CALL :Paint_Circle

    PUSHREG X_1
    PUSHREG Y_1
    PUSH 2
    PUSH 37 // белый
    CALL :Paint_Circle

    PUSHREG X_2
    PUSHREG Y_2
    PUSH 3
    PUSH 33 // желтый
    CALL :Paint_Circle

    PUSHREG X_3
    PUSHREG Y_3
    PUSH 3
    PUSH 33 // желтый
    CALL :Paint_Circle

    CALL :Paint_Ram_Len

    PUSHREG Score
    PUSH 10
    DIV
    POPREG AX

    PUSHREG Score
    PUSHREG AX
    PUSH 10
    MUL
    SUB
    POPREG DX

    PUSH 0
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 78
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 48
    PUSHREG AX
    ADD
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // Number 1

    PUSH 0
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 79
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 48
    PUSHREG DX
    ADD
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // Number 2


    DRAW

    RET

    :Right
        CALL :For_Len_Reverse

        PUSHREG X_2
        POPREG X_3

        PUSHREG Y_2
        POPREG Y_3

        PUSHREG X_1
        POPREG X_2

        PUSHREG Y_1
        POPREG Y_2

        PUSHREG X_1
        PUSH 5
        ADD
        POPREG X_1

        PUSH 7200
        PUSH 1
        ADD
        POPREG Color
        PUSHREG X_3
        POPMEM Color

        PUSHREG Color
        PUSH 1
        ADD
        POPREG Color
        PUSHREG Y_3
        POPMEM Color

        JMP :Mini_Move

    :Left
        CALL :For_Len_Reverse

        PUSHREG X_2
        POPREG X_3

        PUSHREG Y_2
        POPREG Y_3

        PUSHREG X_1
        POPREG X_2

        PUSHREG Y_1
        POPREG Y_2

        PUSHREG X_1
        PUSH 5
        SUB
        POPREG X_1

        PUSH 7200
        PUSH 1
        ADD
        POPREG Color
        PUSHREG X_3
        POPMEM Color

        PUSHREG Color
        PUSH 1
        ADD
        POPREG Color
        PUSHREG Y_3
        POPMEM Color

        JMP :Mini_Move

    :Up
        CALL :For_Len_Reverse

        PUSHREG X_2
        POPREG X_3

        PUSHREG Y_2
        POPREG Y_3

        PUSHREG X_1
        POPREG X_2

        PUSHREG Y_1
        POPREG Y_2

        PUSHREG Y_1
        PUSH 5
        SUB
        POPREG Y_1

        PUSH 7200
        PUSH 1
        ADD
        POPREG Color
        PUSHREG X_3
        POPMEM Color

        PUSHREG Color
        PUSH 1
        ADD
        POPREG Color
        PUSHREG Y_3
        POPMEM Color

        JMP :Mini_Move

    :Down
        CALL :For_Len_Reverse

        PUSHREG X_2
        POPREG X_3

        PUSHREG Y_2
        POPREG Y_3

        PUSHREG X_1
        POPREG X_2

        PUSHREG Y_1
        POPREG Y_2

        PUSHREG Y_1
        PUSH 5
        ADD
        POPREG Y_1

        PUSH 7200
        PUSH 1
        ADD
        POPREG Color
        PUSHREG X_3
        POPMEM Color

        PUSHREG Color
        PUSH 1
        ADD
        POPREG Color
        PUSHREG Y_3
        POPMEM Color

        JMP :Mini_Move

:Start
    PUSH 16
    RANDOM
    POPREG X_A

    PUSH 9
    RANDOM
    POPREG Y_A

    PUSH 34 // синий
    CALL :Paint_All_Dot

    PUSH 32 // зеленый
    CALL :Paint_Field

    PUSH 12
    PUSH 42
    PUSH 3
    PUSH 33 // желтый
    CALL :Paint_Circle

    PUSHREG X_A
    PUSHREG Y_A
    PUSH 3
    PUSH 31 // красный
    CALL :Paint_Circle

    PUSH 12
    PUSH 42
    PUSH 2
    PUSH 37 // белый
    CALL :Paint_Circle

    PUSH 7
    PUSH 42
    PUSH 3
    PUSH 33 // желтый
    CALL :Paint_Circle

    PUSH 2
    PUSH 42
    PUSH 3
    PUSH 33 // желтый
    CALL :Paint_Circle

    DRAW

    PUSH 12
    POPREG X_1
    PUSH 42
    POPREG Y_1

    PUSH 7
    POPREG X_2
    PUSH 42
    POPREG Y_2

    PUSH 2
    POPREG X_3
    PUSH 42
    POPREG Y_3

    PUSH 100
    POPREG Direction

    PUSH 1
    POPREG Len

    PUSH 7201
    POPREG Color
    PUSHREG X_3
    POPMEM Color

    PUSH 7202
    POPREG Color
    PUSHREG Y_3
    POPMEM Color

    PUSH 0
    POPREG Score

    RET

:Paint_All_Dot
    POPREG Color

    PUSH 2
    POPREG DX

    CALL :For_BX

    PUSH 0
    POPREG DX

    RET

:Paint_Circle
    POPREG Color

    POPREG Rad

    POPREG Center_Y

    POPREG Center_X

    PUSH 1
    POPREG DX

    CALL :For_BX

    PUSH 0
    POPREG DX

    RET

:Paint_Field
    POPREG Color

    PUSH 3
    POPREG DX

    CALL :For_BX

    PUSH 0
    POPREG DX

    RET

:For_BX
    PUSHREG BX
    PUSH 45
    JE :Exit_BX

    CALL :For_AX

    PUSHREG BX
    PUSH 1
    ADD
    POPREG BX

    JMP :For_BX

    :Exit_BX
    PUSH 0
    POPREG BX
    RET

:For_AX
    PUSHREG AX
    PUSH 80
    JE :Exit_AX

    PUSH 1
    PUSHREG DX
    JE :Call_Circle

    PUSH 2
    PUSHREG DX
    JE :Call_All_Dot

    PUSH 3
    PUSHREG DX
    JE :Call_Field

    :Next
    PUSHREG AX
    PUSH 1
    ADD
    POPREG AX
    JMP :For_AX

    :Exit_AX
    PUSH 0
    POPREG AX
    RET

    :Call_Circle
    CALL :Condition_Circle
    JMP :Next

    :Call_All_Dot
    CALL :Paint_Dot
    JMP :Next

    :Call_Field
    CALL :Condition_Field
    JMP :Next

:Condition_Field
    PUSHREG BX

    PUSHREG BX
    PUSH 5
    DIV

    PUSH 5
    MUL

    SUB

    PUSH 0
    JE :Paint_Net

    PUSHREG AX

    PUSHREG AX
    PUSH 5
    DIV

    PUSH 5
    MUL

    SUB

    PUSH 0
    JE :Paint_Net

    RET

    :Paint_Net
    CALL :Paint_Dot
    RET

:Condition_Circle
    PUSHREG Center_Y
    PUSHREG BX
    SUB
    PUSHREG Center_Y
    PUSHREG BX
    SUB
    MUL

    PUSHREG Center_X
    PUSHREG AX
    SUB
    PUSHREG Center_X
    PUSHREG AX
    SUB
    MUL

    ADD

    PUSHREG Rad
    PUSHREG Rad
    MUL

    JB :Fun_Circle

    RET

    :Fun_Circle
    CALL :Paint_Lattice
    RET

:Paint_Lattice
    PUSHREG BX
    PUSH 80
    PUSH 2
    MUL
    MUL

    PUSHREG AX
    PUSH 2
    MUL

    ADD

    POPREG CX
    PUSH 35
    POPMEM CX

    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSHREG Color
    POPMEM CX

    RET

:Paint_Dot
    PUSHREG BX
    PUSH 80
    PUSH 2
    MUL
    MUL

    PUSHREG AX
    PUSH 2
    MUL

    ADD

    POPREG CX
    PUSH 46
    POPMEM CX

    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSHREG Color
    POPMEM CX

    RET

:For_Len_Reverse
    PUSHREG Len
    POPREG Rad

    :Again_For_Len_Reverse
    PUSHREG Rad
    PUSH 1
    JE :End_For_Len_Reverse

    PUSH 7200
    PUSHREG Rad
    PUSH 2
    MUL
    ADD
    PUSH 1
    SUB
    POPREG Color

    PUSHREG Color
    PUSH 2
    SUB
    POPREG Color
    PUSHMEM Color
    PUSHREG Color
    PUSH 2
    ADD
    POPREG Color

    POPMEM Color

    PUSHREG Color
    PUSH 1
    ADD
    POPREG Color

    PUSHREG Color
    PUSH 2
    SUB
    POPREG Color
    PUSHMEM Color
    PUSHREG Color
    PUSH 2
    ADD
    POPREG Color

    POPMEM Color

    PUSHREG Rad
    PUSH 1
    SUB
    POPREG Rad
    JMP :Again_For_Len_Reverse

    :End_For_Len_Reverse
    RET

:Paint_Ram_Len
    PUSH 1
    POPREG For

    :Again_Paint_Ram_Len
    PUSHREG For
    PUSHREG Len
    JE :End_Paint_Ram_Len

    PUSH 7200
    PUSHREG For
    PUSH 1
    ADD
    PUSH 2
    MUL
    ADD
    PUSH 1
    SUB
    POPREG DX

    PUSHMEM DX

    PUSHREG DX
    PUSH 1
    ADD
    POPREG DX

    PUSHMEM DX

    PUSH 3
    PUSH 33 // желтый
    CALL :Paint_Circle

    PUSHREG For
    PUSH 1
    ADD
    POPREG For
    JMP :Again_Paint_Ram_Len

    :End_Paint_Ram_Len
    RET

:Check_Kick_Yourself
    PUSH 1
    POPREG For

    :Again_Check_Kick_Yourself
    PUSHREG For
    PUSHREG Len
    JE :End_Check_Kick_Yourself

    PUSH 7200
    PUSHREG For
    PUSH 1
    ADD
    PUSH 2
    MUL
    ADD
    PUSH 1
    SUB
    POPREG DX

    PUSHMEM DX
    PUSHREG X_1
    JE :Conditional_Check_Kick_Yourself

    PUSHREG For
    PUSH 1
    ADD
    POPREG For
    JMP :Again_Check_Kick_Yourself

    :End_Check_Kick_Yourself
    RET

    :Conditional_Check_Kick_Yourself
    PUSHREG DX
    PUSH 1
    ADD
    POPREG DX

    PUSHMEM DX
    PUSHREG Y_1
    JE :Finish

    PUSHREG For
    PUSH 1
    ADD
    POPREG For
    JMP :Again_Check_Kick_Yourself

:Check_Rip_Border
    PUSHREG X_1
    PUSH 77
    JA :Finish

    PUSHREG X_1
    PUSH 2
    JB :Finish

    PUSHREG Y_1
    PUSH 42
    JA :Finish

    PUSHREG Y_1
    PUSH 2
    JB :Finish

    RET

:Check_Bad_Apple

    PUSHREG X_1
    PUSHREG X_A
    JE :Conditional_Check_Bad_Apple_1

    PUSHREG X_2
    PUSHREG X_A
    JE :Conditional_Check_Bad_Apple_2

    PUSHREG X_3
    PUSHREG X_A
    JE :Conditional_Check_Bad_Apple_3

    :Continue
    PUSH 1
    POPREG For

    :Again_Check_Bad_Apple
    PUSHREG For
    PUSHREG Len
    JE :End_Check_Bad_Apple

    PUSH 7200
    PUSHREG For
    PUSH 1
    ADD
    PUSH 2
    MUL
    ADD
    PUSH 1
    SUB
    POPREG DX

    PUSHMEM DX
    PUSHREG X_A
    JE :Conditional_Check_Bad_Apple

    PUSHREG For
    PUSH 1
    ADD
    POPREG For
    JMP :Again_Check_Bad_Apple

    :End_Check_Bad_Apple
    RET

    :Conditional_Check_Bad_Apple
    PUSHREG DX
    PUSH 1
    ADD
    POPREG DX

    PUSHMEM DX
    PUSHREG Y_A
    JE :Repeat_Change_Apple

    PUSHREG For
    PUSH 1
    ADD
    POPREG For
    JMP :Again_Check_Bad_Apple

    :Conditional_Check_Bad_Apple_1
    PUSHREG Y_1
    PUSHREG Y_A
    JE :Repeat_Change_Apple
    JMP :Continue

    :Conditional_Check_Bad_Apple_2
    PUSHREG Y_2
    PUSHREG Y_A
    JE :Repeat_Change_Apple
    JMP :Continue

    :Conditional_Check_Bad_Apple_3
    PUSHREG Y_3
    PUSHREG Y_A
    JE :Repeat_Change_Apple
    JMP :Continue

:Paint_Rip
    PUSH 31 // красный
    CALL :Paint_All_Dot

    PUSH 12              // R start
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 13
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 14
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 15
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 17
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 18
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 19
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 20
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 21
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 22
    POPREG BX
    PUSH 10
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 12
    POPREG BX
    PUSH 11
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 12
    POPREG BX
    PUSH 12
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 12
    POPREG BX
    PUSH 13
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 12
    POPREG BX
    PUSH 14
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 13
    POPREG BX
    PUSH 15
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 14
    POPREG BX
    PUSH 15
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 15
    POPREG BX
    PUSH 15
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 14
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 13
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 12
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 11
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 17
    POPREG BX
    PUSH 13
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 18
    POPREG BX
    PUSH 14
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 19
    POPREG BX
    PUSH 15
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 20
    POPREG BX
    PUSH 15
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 21
    POPREG BX
    PUSH 15
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 22
    POPREG BX
    PUSH 15
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice   // R end

    PUSH 12             // I start
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 13
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 14
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 15
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 17
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 18
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 19
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 20
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 21
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 22
    POPREG BX
    PUSH 19
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice // I end

    PUSH 12             // P start
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 13
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 14
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 15
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 17
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 18
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 19
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 20
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 21
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 22
    POPREG BX
    PUSH 23
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 12
    POPREG BX
    PUSH 24
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 12
    POPREG BX
    PUSH 25
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 12
    POPREG BX
    PUSH 26
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 12
    POPREG BX
    PUSH 27
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 13
    POPREG BX
    PUSH 28
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 14
    POPREG BX
    PUSH 28
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 15
    POPREG BX
    PUSH 28
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 27
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 26
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 25
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice

    PUSH 16
    POPREG BX
    PUSH 24
    POPREG AX
    PUSH 37
    POPREG Color
    CALL :Paint_Lattice // P end


    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 55
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 83
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // S

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 56
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 67
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // C

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 57
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 79
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // O

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 58
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 82
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // R

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 59
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 69
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // E

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 60
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 58
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // :

    PUSHREG Score
    PUSH 10
    DIV
    POPREG AX

    PUSHREG Score
    PUSHREG AX
    PUSH 10
    MUL
    SUB
    POPREG DX


    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 62
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 48
    PUSHREG AX
    ADD
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // Number 1

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 63
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 48
    PUSHREG DX
    ADD
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // Number 2

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 55
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 84
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // T

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 56
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 82
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // R

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 57
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 89
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // Y

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 59
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 65
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // A

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 60
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 71
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // G

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 61
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 65
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // A

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 62
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 73
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // I

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 63
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 78
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // N


    RET

:Print_Win
    PUSH 32 // green
    CALL :Paint_All_Dot

    PUSH 29
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 55
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 87
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // W

    PUSH 29
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 56
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 73
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // I

    PUSH 29
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 57
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 78
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // N

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 55
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 83
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // S

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 56
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 67
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // C

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 57
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 79
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // O

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 58
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 82
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // R

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 59
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 69
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // E

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 60
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 58
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // :

    PUSHREG Score
    PUSH 10
    DIV
    POPREG AX

    PUSHREG Score
    PUSHREG AX
    PUSH 10
    MUL
    SUB
    POPREG DX

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 62
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 48
    PUSHREG AX
    ADD
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // Number 1

    PUSH 30
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 63
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 48
    PUSHREG DX
    ADD
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // Number 2

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 55
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 89
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // Y

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 56
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 79
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // O

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 57
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 85
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // U

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 59
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 71
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // G

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 60
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 82
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // R

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 61
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 69
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // E

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 62
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 65
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // A

    PUSH 32
    PUSH 80
    PUSH 2
    MUL
    MUL
    PUSH 63
    PUSH 2
    MUL
    ADD
    POPREG CX
    PUSH 84
    POPMEM CX
    PUSH 1
    PUSHREG CX
    ADD
    POPREG CX
    PUSH 37
    POPMEM CX   // T

    DRAW
    HLT

