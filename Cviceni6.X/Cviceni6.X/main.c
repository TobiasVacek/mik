// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC  // Power-up default value for COSC bits (EXTOSC operating per FEXTOSC bits (device manufacturing default))

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // Master Clear Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power up timer disabled)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_2P45 // Brown Out Reset Voltage selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config DEBUG = OFF      // Debugger Enable bit (Background debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)


#pragma config LVP = OFF        // Low Voltage Programming Enable bit (HV on MCLR/VPP must be used for programming)

#define GLCD_DataPort LATD

#define GLCD_CS1 LATBbits.LATB0
#define GLCD_CS2 LATBbits.LATB1
#define GLCD_RS  LATBbits.LATB2
#define GLCD_RW  LATBbits.LATB3
#define GLCD_EN  LATBbits.LATB4
#define GLCD_RST LATBbits.LATB5

#include <xc.h>
#include <stdint.h>
#include <pic18f47k40.h>
#include "font5x7.h"

#define _XTAL_FREQ 8000000

void Odesli(void);
void Send_Command12(unsigned char cmd);
void Send_Data12(unsigned char dat);
void Send_char_font5x7(char ch);

void Odesli(void)
{
    GLCD_EN = 1;
    __delay_us(1);
    GLCD_EN = 0;
}

void Send_Command12(unsigned char cmd)
{
    GLCD_CS1 = 0;
    GLCD_CS2 = 0;
    GLCD_RW = 0;
    GLCD_RS = 0;
    __delay_us(3);
     // priprava dat na datovou sbernici
    LATD = cmd;
    Odesli();
    __delay_ms(2);
}

void Send_Data12(unsigned char dat)
{
    GLCD_CS1 = 0;
    GLCD_CS2 = 0;
    GLCD_RW = 0;
    GLCD_RS = 1;
    __delay_us(3);
    
     // priprava dat na datovou sbernici
    LATD = dat;
    Odesli();
    __delay_ms(2);
 }

void Send_char_font5x7(char ch) 
{
	uint8_t i;
    for (i= 1; i < 7; i++)
	{
		Send_Data12(font5x7[(ch-32)*6+i]);
        
	}
}


void main(void) 
{
    uint8_t m,i;  

    ANSELB = 0;                        // Configure PORTB pins as digital I/O
    ANSELD = 0;                        // Configure PORTD pins as digital I/O
    TRISB  = 0;
    TRISD  = 0;
    GLCD_RST = 1;
    Send_Command12(0b00111111);// LCD ON
    Send_Command12(0b10111000);// Set page
    Send_Command12(0b01000000);// Set address    

    for (m=1;m<9;m++)                 // vykresli vodorovne linky na LCD
    {    
        for (i=0;i<64;i++)
        {
            //Send_Data12(0b01010101); 
            Send_Data12(0);
        }
        Send_Command12(0b10111000 + m);       
    }
    
    Send_Command12(0b10111000);
    for(int j = 1; j<9; j++){
    for(int i = 0; i<10;i++){
    Send_Command12(0b01000000 | i*6);
    Send_char_font5x7('!'+i + (j-1)*10);} 
    Send_Command12(0b10111000 | j);} 
    
    while(1);
    return;
}
