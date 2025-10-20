IN // a * x^2
POPREG AX

IN // b * x^1
POPREG BX

IN // c * x^0
POPREG CX

PUSHREG AX
PUSH 0
JE :A_Null

CALL :Discriminant

PUSHREG DX
PUSH 0
JE :One_Solve

PUSHREG DX
PUSH 0
JB :Zero_Solve

PUSHREG DX
PUSH 0
JA :Two_Solve

:One_Solve
    PUSH 1
    OUT
    PUSH -1
    PUSHREG BX
    MUL
    PUSHREG AX
    PUSH 2
    MUL
    DIV
    OUT
    JMP :Finish

:Zero_Solve
    PUSH 0
    OUT
    JMP :Finish

:Two_Solve
    PUSH 2
    OUT
    PUSH -1
    PUSHREG BX
    MUL
    PUSHREG DX
    SQRT
    SUB
    PUSH 2
    PUSHREG AX
    MUL
    DIV
    OUT
    PUSH -1
    PUSHREG BX
    MUL
    PUSHREG DX
    SQRT
    ADD
    PUSH 2
    PUSHREG AX
    MUL
    DIV
    OUT
    JMP :Finish

:A_Null
    PUSHREG BX
    PUSH 0
    JE :B_Null

    PUSH 1
    OUT
    PUSH -1
    PUSHREG CX
    MUL
    PUSHREG BX
    DIV
    OUT
    JMP :Finish

:B_Null
    PUSHREG CX
    PUSH 0
    JE :C_Null

    PUSH -1
    OUT
    JMP :Finish

:C_Null
    PUSH 8
    OUT
    JMP :Finish

:Discriminant
    PUSHREG BX
    PUSHREG BX
    MUL
    PUSH 4
    PUSHREG AX
    PUSHREG CX
    MUL
    MUL
    SUB
    POPREG DX
    RET

:Finish
    HLT
