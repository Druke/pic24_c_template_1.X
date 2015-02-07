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

#include"keypad_driver.h"
#include"LED_Driver.h"
#include"user.h"

#define C1   PORTBbits.RB4     //Column1
#define C2   PORTBbits.RB5     //Column2
#define C3   PORTBbits.RB7    //Column3
#define C4   PORTBbits.RB8     //Column4

#define Row1 LATBbits.LATB9    //Row1
#define Row2 LATBbits.LATB13    //Row2
#define Row3 LATBbits.LATB14     //Row3
#define Row4 LATBbits.LATB15     //Row4

char get_key(void)
{
	char key = 'z';
	while(key == 'z')
        {
            key = Read_Switch();
        }
	return key;
}

char check_key(void)
{
	char key = 'Z';
	key = Read_Switch();
	return key; //if nothing was pressed it will return 'Z'.
}
int test = 0xAAAA;
char Read_Switch(void){
	unsigned char shifted = 0;
	unsigned int delayed = 0;
        TRISB = 0x0000;
        LATBbits.LATB8 = 0;
        LATBbits.LATB7 = 0;
        LATBbits.LATB5 = 0;
        LATBbits.LATB4 = 0;
        C1 = 0;
        C2 = 0;
        C3 = 0;
        C4 = 0;
        TRISB = 0x1DFF;
        Row1 = 1;
        Row2 = 0;
        Row3 = 0;
        Row4 = 0;
	if(C1 == 1){delay_ms(25);while(C1 == 1); return 0x01;} //1
	if(C2 == 1){delay_ms(25);while(C2 == 1); return 0x02;} //2
	if(C3 == 1){delay_ms(25);while(C3 == 1); return 0x03;} //3
	if(C4 == 1){delay_ms(25);while(C4 == 1); return 0x0A;} //A
        Row1 = 0;
	Row2 = 1;
        //TRISB = 0xFFFF;
	if(C1 == 1){delay_ms(25);while(C1 == 1); return 0x04;} //4
	if(C2 == 1){delay_ms(25);while(C2 == 1); return 0x05;} //5
	if(C3 == 1){delay_ms(25);while(C3 == 1); return 0x06;} //6
	if(C4 == 1){delay_ms(25);while(C4 == 1); return 0x0B;} //B
        //TRISB = 0x0000;
        Row2 = 0;
	Row3 = 1;
        //TRISB = 0xFFFF;
	if(C1 == 1){delay_ms(25);while(C1 == 1); return 0x07;} //7
	if(C2 == 1){delay_ms(25);while(C2 == 1); return 0x08;} //8
	if(C3 == 1){delay_ms(25);while(C3 == 1); return 0x09;} //9
	if(C4 == 1){delay_ms(25);while(C4 == 1); return 0x0C;} //C
        //TRISB = 0x0000;
        Row3 = 0;
	Row4 = 1;
        //TRISB = 0xFFFF;
        /*
	if(C1 == 1)//  * key used as a shift
		{	Row4 = 1;
			delay_ms(100);
			shifted = 1;
			while(shifted == 1)
			{
				if(delayed > 0x0FFF){LED_write(0xFF);}//flash LEDs to show in shift mode
				else{LED_write(0x0000);}
				if(delayed > 0x1FFF){delayed = 0;}
                                TRISB = 0x0000;
                                Row1 = 0;
                                TRISB = 0xFFFF;
				if(C1 == 0){delay_ms(25);while(C1 == 0); return 0x0E;}//E
				if(C2 == 0){delay_ms(25);while(C2 == 0); return 0x0F;}//F
				if(C3 == 0){delay_ms(25);while(C3 == 0); return 0x20;}//Backspace
				if(C4 == 0){delay_ms(25);while(C4 == 0); return 0x10;}//Exit
                                TRISB = 0x0000;
                                Row1 = 1;
                                TRISB = 0xFFFF;
				delayed++;
			}
		}
         * */
        if(C1 == 1){delay_ms(25);while(C1 == 1); return 0x00;} //0
	if(C2 == 1){delay_ms(25);while(C2 == 1); return 0x00;} //0
	if(C3 == 1){delay_ms(25);while(C3 == 1); return 0x30;} //# key
	if(C4 == 1){delay_ms(25);while(C4 == 1); return 0x0D;} //D
        return 'z';
}
