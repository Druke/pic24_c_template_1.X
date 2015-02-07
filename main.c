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

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "led_driver.h"
#include "lcd_driver.h"
#include "GPS.h"
#include "keypad_driver.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    /* TODO <INSERT USER APPLICATION CODE HERE> */
    lcdinit();
    delay_ms(1000);
    write_start_menu();
    delay_ms(1000);
    clear_screen();
    RPINR18bits.U1RXR   =   2;//UART1 receive set to RB2
    RPOR1bits.RP3R	=   3;//UART1 transmit set to RB3
    RPINR19bits.U2RXR   =   0;//UART2 receive set to RB0
    RPOR0bits.RP1R      =   5;//UART2 transmit set to RB1
   //LED_write(0x0F);
   //delay_ms(5000);

   UART1Init(207);	//207 = 4800 baud.....103 = 9800 baud
   UART2Init(103);
   //delay_ms(1000);

   //Main Program Loop, Loop forever
   char count = 0;
   char data;
   char selection = 0;
   char* menu_page1 = "1. Time%2. Update%3. LAT/LOG$";
   char* timeHead = "Time$";
   write_menu(menu_page1);
   new_line(3);
   while(1)
   {
       getline();
       char data;
       data = UART2GetChar();
       LED_write(data);
       if(data == '2'){
           getline();
           displayTime();
           LED_write(0xFA);
       }
       if(data == '3'){
           getline();
           displayLAT();
           LED_write(0xAF);
       }
       UART2PutChar(0x0A);
       UART2PutChar(0x0D);
       //writedata(data);
   }
}