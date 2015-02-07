/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include <stdint.h>          /* For uint32_t definition */
#include <stdbool.h>         /* For true/false definition */

#include "user.h"            /* variables/params used by user.c */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

/* TODO Initialize User Ports/Peripherals/Project here */

void InitApp(void)
{
    /* Setup analog functionality and port direction */
    AD1PCFGL	 =	0xFFFF;	 //set to all digital I/O
    TRISB	 =	0xFFFF;	 //configure all PortB as input
    TRISA = 0;
    TRISC = 0;

    LATAbits.LATA4 = 0;
    /* Initialize peripherals */
}
void delay_ms(int time)
{
    static long timel = 0;
    timel = time * 1000l;
    for( ; timel; timel--);// no initial condition, while time is >0, decrement time each loop
}