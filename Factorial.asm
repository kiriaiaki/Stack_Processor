IN

CALL :Factorial
PUSHREG AX
OUT

HLT

:Factorial
    POPREG AX

    PUSHREG AX
    PUSH 1
    JE :Return_1

    PUSHREG AX

    PUSHREG AX
    PUSH 1
    SUB

    CALL :Factorial

    PUSHREG AX
    MUL
    POPREG AX

    RET

    :Return_1
    PUSH 1
    POPREG AX

    RET
