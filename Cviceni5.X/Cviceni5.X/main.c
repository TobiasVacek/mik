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



#include <xc.h>
#include <stdint.h>
#include <pic18f47k40.h>
#include "lcd_PIC18F47K40.h"

#define _XTAL_FREQ 8000000




void main(void) 
{
    ANSELB = 0b00000000;
    TRISB  = 0b00000000;
    LATB   = 0b00000000;
   
 // Inicializace radice LCD - str. 46 v lcd_hitachi44780.pdf
    Send_Command (0b00000011);
    Send_Command (0b00000011);
    Send_Command (0b00000011);
    Send_Command (0b00000010);
    Send_Command (0b00101000);
    Send_Command (0b00001000);
    Send_Command (0b00000001);
    Send_Command (0b00000110);
 // Nastavení parametru a zobrazení znaku - str. 43 v lcd_hitachi44780.pdf
    Send_Command (0b00101000);          //krok 2  bit 4 = 0  4-bit komunikace
    Send_Command (0b00001110);          //krok 3
    Send_Command (0b00000110);          //krok 4
          
    Send_Data ('H');
    Send_Data ('e');
    Send_Data ('l');
    Send_Data ('l');
    Send_Data ('o');
    
    Send_Command (0b01000000);
    Send_Data (0b00000000);
    Send_Data (0b00001010);
    Send_Data (0b00001010);
    Send_Data (0b00000000);
    Send_Data (0b00010001);
    Send_Data (0b00001110);
    Send_Data (0b00000000);
    Send_Data (0b00000000);
    
    Send_Command (0b11000000);
    Send_Data(0);
    while(1)
    {
        
    }
    
    return;
}
