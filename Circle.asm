CALL :Paint_All_Dot
DRAW

PUSH 7
PUSH 7
PUSH 7
CALL :Paint_Circle
DRAW

PUSH 7
PUSH 18
PUSH 7
CALL :Paint_Circle
DRAW

PUSH 18
PUSH 12
PUSH 7
CALL :Paint_Circle
DRAW

PUSH 25
PUSH 12
PUSH 7
CALL :Paint_Circle
DRAW

PUSH 32
PUSH 12
PUSH 7
CALL :Paint_Circle
DRAW

PUSH 40
PUSH 12
PUSH 7
CALL :Paint_Circle
DRAW

HLT

:Paint_All_Dot
    PUSH 2
    POPREG DX

    CALL :For_BX

    PUSH 0
    POPREG DX

    RET

:Paint_Circle
    POPREG Rad
    POPREG Center_Y
    POPREG Center_X

    PUSH 1
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
    PUSH 33
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

    RET

