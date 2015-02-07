/* 
 * File:   uart1.h
 * Author: Admin
 *
 * Created on December 3, 2014, 8:52 PM
 */

#ifndef UART1_H
#define	UART1_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif
/*
Engscope
UART
April 16, 2008
Author: JL
*/

//prototypes

//Initiation
extern void UART1Init(int BAUDRATEREG1);

//UART transmit function
extern void  UART1PutChar(char Ch);

//UART receive function
extern char UART1GetChar();

extern void UART2Init(int BAUDRATEREG1);

//UART transmit function
extern void  UART2PutChar(char Ch);

//UART receive function
extern char UART2GetChar();

#endif	/* UART1_H */

