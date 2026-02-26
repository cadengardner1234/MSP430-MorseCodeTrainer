# MSP430-MorseCodeTrainer
  A C program written for the MSP430 microcontroller that translates morse code input by the user into English letters and uses UART to
send the letters to a terminal.

  Whenever SW1 is pressed, the interrupt service routine for Port 1 is called. The ISR debounces
and checks the switch again to ensure it’s really pressed.The ISR then calls the function
waitForDash.

  The waitForDash function initializes the int isDash as 0, assuming the user desired to input a
“dot”. The __delay_cycles(500000) function is called, which delays the program by 0.5 seconds.

  After this delay, SW1 is checked again. If it is still held down, the isDash variable is set to 1 and
LED2 is turned on. An if/else statement is then called, adding a 1 to letter[index] (letter being a
global character array) if isDash is 0, and a 2 to letter[index] if isDash is 1; The global int index
is then incremented by 1.

  Whenever SW2 is pressed, the interrupt service routine for Port 2 is called. The ISR debounces
and checks the switch again to ensure it’s really pressed. The ISR then sets the global int
letterDone (initialized as 0) to 1.

  In the main function, the program first configures the ports, enables interrupts, and calls the
UART_setup() function. Then, within an infinite while loop, the program waits until letterDone is 1. 
Once this happens, the null terminator is added to letter[index], and index is reset to 0. Then,
a series of if/else if statements use the strcmp function to determine which character the user
wants to send, and then send that character to the terminal using UART. Finally, letterDone is
reset to 0, the character array is cleared (filled in with 0s using memset), and the program
returns to the beginning of the loop, waiting for the next character.
