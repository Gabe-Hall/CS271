// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed,
// the screen should be cleared.

//// Replace this comment with your code.

// Fills the screen with black when a key is pressed, white when no key is pressed.

(START)
    @24576       // Load the keyboard memory address (KBD)
    D=M          // D = contents of KBD (0 if no key pressed, non-zero if key pressed)
    @BLACK
    D;JNE        // If a key is pressed (D != 0), jump to BLACK
    @WHITE
    0;JMP        // Otherwise, jump to WHITE

(BLACK)
    @16384       // Start of the screen memory (SCREEN)
    D=A          // D = SCREEN base address
    @SCREEN_FILL // Set a marker for the screen fill loop
    M=D          // Initialize the starting address
(FILL_BLACK)
    @SCREEN_FILL // Load current address from marker
    A=M
    M=-1         // Set pixel to black
    @SCREEN_FILL
    M=M+1        // Move to the next screen address
    @24576       // End of screen memory
    D=A          // Set D to the last address in screen memory
    @SCREEN_FILL
    D=D-M        // Check if we've reached the end
    @FILL_BLACK
    D;JGT        // If not yet at the end, continue filling
    @START
    0;JMP        // Return to start to check keyboard state

(WHITE)
    @16384       // Start of the screen memory (SCREEN)
    D=A          // D = SCREEN base address
    @SCREEN_FILL // Set a marker for the screen fill loop
    M=D          // Initialize the starting address
(FILL_WHITE)
    @SCREEN_FILL // Load current address from marker
    A=M
    M=0          // Set pixel to white
    @SCREEN_FILL
    M=M+1        // Move to the next screen address
    @24576       // End of screen memory
    D=A          // Set D to the last address in screen memory
    @SCREEN_FILL
    D=D-M        // Check if we've reached the end
    @FILL_WHITE
    D;JGT        // If not yet at the end, continue filling
    @START
    0;JMP        // Return to start to check keyboard state
