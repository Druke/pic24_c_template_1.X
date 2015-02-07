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

#include "system.h"          /* variables/params used by system.c */

/******************************************************************************/
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c                                           */
/*                                                                            */
/******************************************************************************/

/* Refer to the device Family Reference Manual Oscillator section for
information about available oscillator configurations.  Typically
this would involve configuring the oscillator tuning register or clock
switching useing the compiler's __builtin_write_OSCCON functions.
Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
compiler installation directory /doc folder for documentation on the
__builtin functions. */

/* TODO Add clock switching code if appropriate.  An example stub is below.   */
void ConfigureOscillator(void)
{

#if 0

        /* Disable Watch Dog Timer */
        RCONbits.SWDTEN = 0;

        /* When clock switch occurs switch to Prim Osc (HS, XT, EC)with PLL */
        __builtin_write_OSCCONH(0x03);  /* Set OSCCONH for clock switch */
        __builtin_write_OSCCONL(0x01);  /* Start clock switching */
        while(OSCCONbits.COSC != 0b011);

        /* Wait for Clock switch to occur */
        /* Wait for PLL to lock, if PLL is used */
        /* while(OSCCONbits.LOCK != 1); */

#endif
/****************************************************************************/
/* Useful Macros */
#define BITS2WORD(sfrBitfield) ( *((unsigned int*) &sfrBitfield) )
// Convert a bitfield to a word (unsigned int).
#define BITS2BYTEL(sfrBitfield) ( ((unsigned char*) &sfrBitfield)[0] )
// Return the low byte (as a unsigned char) of a bitfield.
#define BITS2BYTEH(sfrBitfield) ( ((unsigned char*) &sfrBitfield)[1] )
// Return the high byte (as a unsigned char) of a bitfield.

/****************************************************************************/
/* User Configurable Definitions */

// If the following line is uncommented the uC will use the internal oscillator,
// comment the line out to use the external oscillator
#define USE_FRC_CLOCK

// Processor clock frequency selection
#define CLOCK_FREQ 32000000ULL // Use 32MHz clock - default for demo board
//#define CLOCK_FREQ 16000000ULL // Use 16MHz clock
//#define CLOCK_FREQ 8000000ULL // Use 8MHz clock
//#define CLOCK_FREQ 4000000ULL // Use 4MHz clock

/*
*
*/
unsigned int pllCounter;
OSCCONBITS OSCCONbitsCopy;

// Copy the current Clock Setup
OSCCONbitsCopy = OSCCONbits;
// Slow output clock down to 4Mhz
CLKDIVbits.CPDIV = 3;
// Enable the PLL - Note: Fuse bits don't do this
CLKDIVbits.PLLEN = 1;
// Wait for the PLL to stabalise
for (pllCounter = 0; pllCounter < 600; pllCounter++);

// Check to see what clock setup is defined - either internal or external
#ifdef USE_FRC_CLOCK
// Setup the uC to use the internal FRCPLL mode
OSCCONbitsCopy.NOSC = 1;
OSCCONbitsCopy.OSWEN = 1;
#else
// Setup the uC to use the external crystal with the PLL
OSCCONbitsCopy.NOSC = 3;
OSCCONbitsCopy.OSWEN = 1;
#endif

// Switch over to the new clock setup
__builtin_write_OSCCONH( BITS2BYTEH( OSCCONbitsCopy ) );
__builtin_write_OSCCONL( BITS2BYTEL( OSCCONbitsCopy ) );
// Wait for this transfer to take place
while (OSCCONbits.COSC != OSCCONbits.NOSC);
// Setup the DIV bits for the FRC, this values means the config word needs to be: PLLDIV_DIV2
CLKDIVbits.RCDIV0 = 0;

// Setup the PLL divider for the correct clock frequency
if (CLOCK_FREQ == 32000000)
{
CLKDIVbits.CPDIV = 0;
}
else if (CLOCK_FREQ == 16000000)
{
CLKDIVbits.CPDIV = 1;
}
else if (CLOCK_FREQ == 8000000)
{
CLKDIVbits.CPDIV = 2;
}
else if (CLOCK_FREQ == 4000000)
{
CLKDIVbits.CPDIV = 3;
}

// Check that the PLL is enabled again and locked properly to the new setup
CLKDIVbits.PLLEN = 1;
// Note - don't want to do this check if we are running in the MPLAB X simulator as it won't work
#ifndef __MPLAB_SIM
while(_LOCK != 1);
#endif
}

