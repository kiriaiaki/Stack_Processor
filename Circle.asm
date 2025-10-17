IN
POPREG DX

PUSH 0
POPREG AX

PUSH 0
POPREG BX

CALL :For_BX

DRAW
HLT

:For_BX
    PUSHREG BX
    PUSH 27
    JE :Exit_BX

    PUSHREG BX
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
    PUSH 48
    JE :Exit_AX

    PUSH 24
    PUSHREG AX
    SUB
    PUSH 24
    PUSHREG AX
    SUB
    MUL
    PUSH 14
    PUSHREG BX
    SUB
    PUSH 14
    PUSHREG BX
    SUB
    MUL
    ADD
    PUSHREG DX
    PUSHREG DX
    MUL
    JBE :Paint_Lattice

    JMP :Paint_Dot

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


:Paint_Lattice
    PUSHREG BX
    PUSH 48
    MUL
    PUSHREG AX
    ADD
    POPREG CX
    PUSH 35
    POPMEM [CX]
    JMP :Next

:Paint_Dot
    PUSHREG BX
    PUSH 48
    MUL
    PUSHREG AX
    ADD
    POPREG CX
    PUSH 46
    POPMEM [CX]
    JMP :Next
