PUSH 1 // a * x^2
POPREG AX
PUSH -6 // b * x^1
POPREG BX
PUSH 5 // c * x^0
POPREG CX
PUSHREG BX
PUSHREG BX
MUL
PUSH 4
PUSHREG AX
PUSHREG CX
MUL
MUL
SUB
POPREG DX // discriminant
PUSHREG DX
PUSH 0
JE 46 // if discriminant = 0
PUSHREG DX
PUSH 0
JB 63 // if discriminant < 0
PUSHREG DX
PUSH 0
JA 68 // else (if discriminant > 0)
PUSH 1 // programme counter - 46 47 (1 solve)
OUT
PUSH -1
PUSHREG BX
MUL
PUSHREG AX
PUSH 2
MUL
DIV
OUT
JMP 105 // finish
PUSH 0 // programme counter - 63 64 (0 solve)
OUT
JMP 105 // finish
PUSH 2 // programme counter - 68 69 (2 solve)
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
JMP 105 // finish
HLT // programme counter - 105 (end)
