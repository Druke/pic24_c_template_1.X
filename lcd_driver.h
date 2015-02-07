/* 
 * File:   lcd_driver.h
 * Author: Admin
 *
 * Created on November 9, 2014, 8:25 PM
 */

#ifndef LCD_DRIVER_H
#define	LCD_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

void writecmd(unsigned char);
void writedata(char);
void lcdinit(void);
void write_menu(char[]);
void new_line(char);
void clear_screen(void);
char ascii_convert(char);
void display_address(int);
void display_long(long);
void write_start_menu(void);
void write_Mem_menu(void);
void write_Timer_menu(void);
void display_contents(char);
void Search_menu(char);
void clear_line(char);

#endif	/* LCD_DRIVER_H */

