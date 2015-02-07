/*
Engscope
UART
April 16, 2008
Author: JL
*/

#include "system.h"	//see tutorial below!
#include "uart1.h"
#include "xc.h"
#include "led_driver.h"

//Initiation function
//parameter BAUDRATEREG1 determines baud speed
void UART1Init(int BAUDRATEREG1)
{
   //Set up registers
   U1BRG = BAUDRATEREG1;	//set baud speed
   U1MODE	=	0x8000;	 //turn on module
   U1STA	=	0x8400;	 //set interrupts
   //reset RX interrupt flag
   IFS0bits.U1RXIF = 0;
}
void UART2Init(int BAUDRATEREG1)
{
   //Set up registers
   U2BRG = BAUDRATEREG1;	//set baud speed
   U2MODE	=	0x8000;	 //turn on module
   U2STA	=	0x8400;	 //set interrupts
   //reset RX interrupt flag
   IFS1bits.U2RXIF = 0;
}
//UART transmit function, parameter Ch is the character to send
void UART1PutChar(char Ch)
{
   //transmit ONLY if TX buffer is empty
   while(U1STAbits.UTXBF == 1);
   U1TXREG = Ch;
}

void UART2PutChar(char Ch)
{
   //transmit ONLY if TX buffer is empty
   while(U2STAbits.UTXBF == 1);
   U2TXREG = Ch;
}

//UART receive function, returns the value received.
char UART1GetChar()
{
   char Temp;
   char count = 0;
   //wait for buffer to fill up, wait for interrupt
   while(IFS0bits.U1RXIF == 0);
   Temp = U1RXREG;
   //reset interrupt
   IFS0bits.U1RXIF = 0;
   //return my received byte
   return Temp;
}

char UART2GetChar()
{
   char Temp;
   char count = 0;
   //wait for buffer to fill up, wait for interrupt
   while(IFS1bits.U2RXIF == 0);
   Temp = U2RXREG;
   //reset interrupt
   IFS1bits.U2RXIF = 0;
   //return my received byte
   return Temp;
}