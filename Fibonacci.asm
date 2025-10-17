IN

CALL :Fibonacci
PUSHREG AX
OUT

HLT

:Fibonacci
    POPREG AX

    PUSHREG AX
    PUSH 1
    JB :Return_Err

    PUSHREG AX
    PUSH 1
    JE :Return_1

    PUSHREG AX
    PUSH 2
    JE :Return_2

    PUSHREG AX
    PUSH 1
    SUB

    CALL :Fibonacci

    PUSHREG AX
    PUSHREG BX
    ADD
    PUSHREG AX
    POPREG BX
    POPREG AX

    RET

    :Return_2
    PUSH 1
    POPREG AX
    PUSH 1
    POPREG BX

    RET

    :Return_1

    RET

    :Return_Err
    PUSH 336
    POPREG AX

    RET
