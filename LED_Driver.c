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

#include "led_driver.h"
#include "user.h"

/************************
 ************************
 ************************
 ************************/
#define LED_EN LATAbits.LATA8
#define LED_Value LATC

void LED_write(char x)
{
    LED_EN = 1;
    delay_ms(1);
    LED_Value = x;
    delay_ms(1);
    LED_EN = 0;
}

void LED_Dance_1(void)
{
    char Dance_1_Array[] = {0xE0, 0xD0, 0xC8, 0xC4, 0xC2, 0xC1, 0xA1, 0x91, 0x89, 0x85, 0x83, 0x43, 0x23, 0x13, 0x0B, 0x07};
    char Dir = 0;
    char count1 = 0;
    while(Dir < 2){
        if(Dir == 0)
        {
            LED_write(Dance_1_Array[count1]);
            delay_ms(100);
            count1++;
        }
        if(Dir == 1)
        {
            LED_write(Dance_1_Array[count1]);
            delay_ms(100);
            count1--;
        }
        if(count1 == 0)
        {
            Dir = 0;
        }
        if(count1 == 15)
        {
            Dir = 1;
        }
    }
}