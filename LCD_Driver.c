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

#include "lcd_driver.h"
#include "led_driver.h"
#include "user.h"

/************************
 ************************
 ************************
 ************************/
#define LCD_RW LATAbits.LATA4   // R ~W for LCD
#define E LATAbits.LATA3     //E pin for LCD
#define RS LATAbits.LATA7     //RS pin for LCD
#define LCD_VAL LATC


void lcdinit(void)
{
  ///////////// Reset process from datasheet /////////
     delay_ms(15);
   writecmd(0x30);
     delay_ms(5);
   writecmd(0x30);
     delay_ms(1);
   writecmd(0x30);
     delay_ms(4);
  /////////////////////////////////////////////////////
   writecmd(0x38);    //function set
		delay_ms(4);
   writecmd(0x38);    //function set again
		delay_ms(4);
   writecmd(0x0C);    //Display on Cursor off blink off
		delay_ms(4);
	 writecmd(0x01); //clear screen
		delay_ms(4);
   writecmd(0x06);    //entry mode, set increment
}

/*===============================================*/
void writecmd(unsigned char z)
{
	LCD_RW = 0;					//Write Host -> LCD
	RS = 0;             // This is command
	E  = 1;             // LCD Enable = 1
	LCD_VAL = z;        //Data transfer
        delay_ms(1);
	E  = 0;             // LCD Disable
}

/*===============================================*/
void writedata(char x)
{
	LCD_RW = 0;				//Write Host -> LCD
	RS = 1;						// High for data register
	E = 1; 						// Enable high
	LCD_VAL = x;
        delay_ms(1);
	E = 0;						//Disable LCD
	RS = 0;						//Don't read

}

/*===============================================*/
void clear_screen(void)
{
		writecmd(0x01);
		delay_ms(2);
		writecmd(0x02); //return home
		delay_ms(2);
}

/*===============================================*/
void new_line(char line)
{
		switch(line){
			case 0:
				writecmd(0x80);
				delay_ms(2);
				break;
			case 1:
				writecmd(0xC0);
				delay_ms(2);
				break;
			case 2:
				writecmd(0x94);
				delay_ms(2);
				break;
			case 3:
				writecmd(0xD4);
				delay_ms(2);
				break;
		}

}
/*===============================================*/
void write_menu(char array[])
{
	char count = 0;
	char current_line = 0;
	while(array[count] != '$') //as long as not end value
	{
			if(array[count] == '%') //new line indicator
			{
				current_line++;
				new_line(current_line);
				count++;
			}
			if(array[count] == '>')//special arrow character
			{
				count++;
				writedata(0x7E);
				delay_ms(1);
			}
			if(array[count] == '<')//special arrow character
			{
				count++;
				writedata(0x7F);
				delay_ms(1);
			}
			if(array[count]=='$') //End print value
			{
				break;
			}
			writedata(array[count]);//display value
			count++; //go to next character
			delay_ms(1);
	}
}

/*===============================================*/
char ascii_convert(char hex)
{
	switch(hex){
		case(0x00):
			return '0';
		case(0x01):
			return '1';
		case(0x02):
			return '2';
		case(0x03):
			return '3';
		case(0x04):
			return '4';
		case(0x05):
			return '5';
		case(0x06):
			return '6';
		case(0x07):
			return '7';
		case(0x08):
			return '8';
		case(0x09):
			return '9';
		case(0x0A):
			return 'A';
		case(0x0B):
			return 'B';
		case(0x0C):
			return 'C';
		case(0x0D):
			return 'D';
		case(0x0E):
			return 'E';
		case(0x0F):
			return 'F';
		case(0x30):
			return ' ';
		default:
			return '.';
	}
}

/*===============================================*/
void write_dash_line(void)
{
	char i = 0;
	while(i<20)
	{
		writedata('-');
		delay_ms(1);
		i++;
	}

}

/*===============================================*/
void write_start_menu(void)
{
	char* class = "------CEEN 4330-----$";
	char* Name = "---WARREN DRUCKER---$";

	new_line(0);
	delay_ms(1);
	write_dash_line();

	delay_ms(2);
	new_line(1);
	delay_ms(1);
	write_menu(class);

	delay_ms(2);
	new_line(2);
	delay_ms(1);
	write_menu(Name);

	delay_ms(2);
	new_line(3);
	delay_ms(1);
	write_dash_line();

	delay_ms(2);
}

/*===============================================*/
void display_address(int addr)
{
	char LLadd = 0;
	char HLadd = 0;
	char LHadd = 0;
	char HHadd = 0;
	int address = 0;


	LLadd = addr & 0x000F;
	address = addr >> 4;
	HLadd = address & 0x000F;
	address = addr >> 8;
	LHadd = address & 0x000F;
	address = addr >> 12;
	HHadd = address & 0x000F;
	writedata(ascii_convert(HHadd));
	delay_ms(2);
	writedata(ascii_convert(LHadd));
	delay_ms(2);
	writedata(ascii_convert(HLadd));
	delay_ms(2);
	writedata(ascii_convert(LLadd));
	delay_ms(2);
}
/*===============================================*/
void display_long(long val)
{
	int Lval = 0;
	int Hval = 0;
	long value = 0;

	Lval = val;
	Hval = val>>16;

	display_address(Hval);
	display_address(Lval);

}
/*===============================================*/
void display_contents(char content)
{
	char Hnibble = 0;
	char Lnibble = 0;

	Hnibble = content >> 4;
	Hnibble = Hnibble & 0x0F;
	Lnibble = content & 0x0F;

	writedata(ascii_convert(Hnibble));
	delay_ms(2);
	writedata(ascii_convert(Lnibble));
	delay_ms(2);
}
/*===============================================*/
void write_Mem_menu(void)
{
	char* Mem_Func_Menu = "1 DUMP%2 MOVE%3 EDIT%4 FIND    5 BACK$";

	write_menu(Mem_Func_Menu);
}
/*===============================================*/
void write_Timer_menu(void)
{
	char* Time_Menu = " Timer Menu  Back=5%1 Set Timer%2 Set Wave$";

	write_menu(Time_Menu);
}
/*===============================================*/
void Search_menu (char x)
{
	char* Search_Address_Prompt = "SEARCH ADDR: $";
	char* search_size_prompt = "BLK(4 HEX #s): $";
	char* What_to_Find_Prompt = "BYTE TO FIND: $";

	if(x == 0)
	{
		write_menu(Search_Address_Prompt);
	}
	if(x==1)
	{
	  	write_menu(search_size_prompt);
	}
	if(x==2)
	{
	  	write_menu(What_to_Find_Prompt);
	}

}

/*===============================================*/
void clear_line(char x)
{
	char i = 0;
	switch(x)
	{
		case(0):
		{
			new_line(0);
			while(i<20)
			{
			   writedata(0x20);
			   delay_ms(1);
			   i++;
			}

		}
		case(1):
		{
			new_line(1);
			while(i<20)
			{
			   writedata(0x20);
			   delay_ms(1);
			   i++;
			}

		}
		case(2):
		{
			new_line(2);
			while(i<20)
			{
			   writedata(0x20);
			   delay_ms(1);
			   i++;
			}
		}
		case(3):
		{
			new_line(3);
			while(i<20)
			{
			  writedata(0x20);
			  delay_ms(1);
			  i++;
			}
		}
	}
}