#include <msp430.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


volatile int letterDone = 0;
char letter[10];
volatile int index = 0;
void UART_setup(void) {
//P3SEL |= BIT3 | BIT4; // Set UC0TXD and UC0RXD to transmit and receive data
    P4SEL |= BIT4 + BIT5; // Set USCI_A1 RXD/TXD to receive/transmit data
    UCA1CTL1 |= UCSWRST; // Set software reset during initialization
    UCA1CTL0 = 0; // USCI_A1 control register
    UCA1CTL1 |= UCSSEL_2; // Clock source SMCLK
    UCA1BR0 = 0x09; // 1048576 Hz / 115200 lower byte
    UCA1BR1 = 0x00; // upper byte
    UCA1MCTL = 0x02; // Modulation (UCBRS0=0x01, UCOS16=0)
    UCA1CTL1 &= ~UCSWRST; // Clear software reset to initialize USCI state machine
}

void UART_sendChar(char bip)
{
    while (!(UCA1IFG&UCTXIFG)); // Wait for previous character to transmit
    UCA1TXBUF = bip;
}

void waitForDash(void)
{
    int isDash = 0; //Assume it's a dot at first
    __delay_cycles(500000);
    if((P2IN&BIT1) == 0)
    {
        isDash = 1; //If switch is still held after 1 second, count it as a dash
    }

    if(isDash == 1)
    {
        letter[index] = '2';    //Add a 2 to represent a dash
        P4OUT |= BIT7;
        P1OUT &= ~BIT0;
    }
    else{
        letter[index] = '1';    //Add a 1 to represent a dot
        P4OUT &= ~BIT7;
        P1OUT |= BIT0;
    }
    index++;
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    UART_setup();

    P2DIR &= ~BIT1;  //Configure SW1 as input
    P1DIR &= ~BIT1; //Configure SW2 as input
    P2REN |= BIT1;  //Pull up resistor
    P1REN |= BIT1;
    P1OUT |= BIT1;  //Needed for proper I/O
    P2OUT |= BIT1;

    P1DIR |= BIT0;  //Configure LED1 as output
    P4DIR |= BIT7;  //Configure LED2 as output
    P1OUT &= ~BIT0; //Initialize LEDs as off
    P4OUT &= ~BIT7;

    _EINT();    //Enable interrupts
    P2IES |= BIT1;  //Trigger when switch pressed
    P2IFG &= ~BIT1; //Clear interrupt flag
    P2IE |= BIT1;   //Enable interrupt
    P1IES |= BIT1;  //Trigger when switch pressed
    P1IFG &= ~BIT1; //Clear interrupt flag
    P1IE |= BIT1;   //Enable interrupt

    while(1){

        while(letterDone == 0);   //Delay until letter is finished
        if(letterDone == 1)   //If SW2 was pressed
        {
            letter[index] = '\0';   //Terminate the string
            index = 0;  //Reset string index

            if(strcmp(letter, "12") == 0)
            {
                UART_sendChar('A');
            }
            else if(strcmp(letter, "2111") == 0)
            {
                UART_sendChar('B');
            }
            else if(strcmp(letter, "2121") == 0)
                       {
                           UART_sendChar('C');
                       }
            else if(strcmp(letter, "211") == 0)
                       {
                           UART_sendChar('D');
                       }

            else if(strcmp(letter, "1") == 0)
                       {
                           UART_sendChar('E');
                       }
            else if(strcmp(letter, "1121") == 0)
                       {
                           UART_sendChar('F');
                       }
            else if(strcmp(letter, "221") == 0)
                       {
                           UART_sendChar('G');
                       }
            else if(strcmp(letter, "1111") == 0)
                       {
                           UART_sendChar('H');
                       }
            else if(strcmp(letter, "11") == 0)
                       {
                           UART_sendChar('I');
                       }
            else if(strcmp(letter, "1222") == 0)
                       {
                           UART_sendChar('J');
                       }
            else if(strcmp(letter, "212") == 0)
                       {
                           UART_sendChar('K');
                       }
            else if(strcmp(letter, "1211") == 0)
                       {
                           UART_sendChar('L');
                       }
            else if(strcmp(letter, "22") == 0)
                       {
                           UART_sendChar('M');
                       }
            else if(strcmp(letter, "21") == 0)
                       {
                           UART_sendChar('N');
                       }
            else if(strcmp(letter, "222") == 0)
                       {
                           UART_sendChar('O');
                       }
            else if(strcmp(letter, "1221") == 0)
                       {
                           UART_sendChar('P');
                       }
            else if(strcmp(letter, "2212") == 0)
                       {
                           UART_sendChar('Q');
                       }
            else if(strcmp(letter, "121") == 0)
                       {
                           UART_sendChar('R');
                       }
            else if(strcmp(letter, "111") == 0)
                       {
                           UART_sendChar('S');
                       }
            else if(strcmp(letter, "2") == 0)
                       {
                           UART_sendChar('T');
                       }
            else if(strcmp(letter, "112") == 0)
                       {
                           UART_sendChar('U');
                       }
            else if(strcmp(letter, "1112") == 0)
                       {
                           UART_sendChar('V');
                       }
            else if(strcmp(letter, "122") == 0)
                       {
                           UART_sendChar('W');
                       }
            else if(strcmp(letter, "2112") == 0)
                       {
                           UART_sendChar('X');
                       }
            else if(strcmp(letter, "2122") == 0)
                       {
                           UART_sendChar('Y');
                       }
            else if(strcmp(letter, "2211") == 0)
                       {
                           UART_sendChar('Z');
                       }
            else if(strcmp(letter, "12222") == 0)
                       {
                           UART_sendChar('1');
                       }
            else if(strcmp(letter, "11222") == 0)
                       {
                           UART_sendChar('2');
                       }
            else if(strcmp(letter, "11122") == 0)
                       {
                           UART_sendChar('3');
                       }
            else if(strcmp(letter, "11112") == 0)
                       {
                           UART_sendChar('4');
                       }
            else if(strcmp(letter, "11111") == 0)
                       {
                           UART_sendChar('5');
                       }
            else if(strcmp(letter, "21111") == 0)
                       {
                           UART_sendChar('6');
                       }
            else if(strcmp(letter, "22111") == 0)
                       {
                           UART_sendChar('7');
                       }
            else if(strcmp(letter, "22211") == 0)
                       {
                           UART_sendChar('8');
                       }
            else if(strcmp(letter, "22221") == 0)
                       {
                           UART_sendChar('9');
                       }
            else if(strcmp(letter, "22222") == 0)
                       {
                           UART_sendChar('0');
                       }
            else if(strcmp(letter, "121212") == 0)
                       {
                           UART_sendChar('.');
                       }
            else if(strcmp(letter, "221122") == 0)
                       {
                           UART_sendChar(',');
                       }
            else if(strcmp(letter, "112211") == 0)
                       {
                           UART_sendChar('?');
                       }

            }
            letterDone = 0; //Reset the letterDone variable
            memset(letter, 0, sizeof(letter));

        }
    }



//SW1 ISR
#pragma vector=PORT2_VECTOR
__interrupt void SW1_ISR(void)
    {

        P2IFG &= ~BIT1; //Reset interrupt flag
        if((P2IN&BIT1) == 0)
        {
            unsigned int i;
            for(i = 2000; i > 0; i--);  //Debounce
            if((P2IN&BIT1) == 0)
            {
                waitForDash();
            }
        }


    }
//SW2 ISR
    #pragma vector=PORT1_VECTOR
    __interrupt void SW2_ISR(void)
    {
        P1IFG &= ~BIT1; //Reset interrupt flag
        if((P1IN&BIT1) == 0)
        {
            unsigned int i;
            for(i = 2000; i > 0; i--);  //Debounce
            if((P1IN&BIT1) == 0)
            {
                letterDone = 1; //If SW2 is still held, assume the user is marking the letter as finished

            }
        }

    }

