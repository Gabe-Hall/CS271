// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// Multiplies R0 and R1 and stores the result in R2.
// R0 = multiplicand, R1 = multiplier, R2 = product

    @2
    M=0         // Initialize R2 (product) to 0
    @0
    D=M         // D = R0 (multiplicand)
    @i
    M=D         // Store multiplicand in a temporary variable 'i'

    @1
    D=M         // D = R1 (multiplier)
    @count
    M=D         // Store multiplier in 'count' for tracking loops

(LOOP)
    @count
    D=M         // D = current value of 'count'
    @END
    D;JEQ       // If count == 0, jump to END

    @i
    D=M         // D = multiplicand
    @2
    M=D+M       // Add multiplicand to product in R2

    @count
    M=M-1       // Decrement count
    @LOOP
    0;JMP       // Repeat the loop

(END)
    @END
    0;JMP       // End of program, loop indefinitely
