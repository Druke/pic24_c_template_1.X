
#include "GPS.h"
#include "xc.h"
#include "uart1.h"
#include "lcd_driver.h"
#include "user.h"

char* LAT[10];
char NSind;
char* msgID[5];
char* UTCTime[10];
char* LON[10];

void getline(void) {
    char start = 0;
    char i = 0;
    U1STAbits.OERR = 0;
    LED_write(0xAA);
    while(start != '$'){
        start = UART1GetChar();    // wait for the start of a line
    }
    i=0;
    while (i<5){
        msgID[i]=UART1GetChar();
        i++;
    }
    i=0;
    if(msgID[3]=='G'){
        char info = 'z';
        while (info !=','){
            info = UART1GetChar();
            UTCTime[i] = info
            //UART2PutChar(info);
            i++;
        }
        i=0;
        info = 'z';
        while (info != ','){
            info = UART1GetChar();
            LAT[i] = info;
            i++;
        }
        i=0;
        info = 'z';
        while (info != ','){
            info = UART1GetChar();
            NSind = info;
            i++;
        }
        i=0;
        info = 'z';
        while (info != ','){
            info = UART1GetChar();
            LON[i] = info;
            i++;
        }
    }
}
displayLAT(){
    char i = 0;
    new_line(3);
    while(i<9){
       writedata(LAT[i]);
       i++;
    }
}
displayTime(){
    char i = 0;
    new_line(3);
    while(i<10){
        writedata(UTCTime[i]);
        i++;
    }
}


