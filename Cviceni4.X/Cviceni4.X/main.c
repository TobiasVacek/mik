
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

#define _XTAL_FREQ 8000000

void __interrupt() INTERRUPTS(void) // Funkce obsluhy prerusen�
{
    if (TMR0IF)        // Prerusen� od casovace TMR0?
    {                           
        LATD=~LATD;
        TMR0IF=0;      // Nulov�n� TMR0 interrupt flag bitu
    }
    if(INT0IF){
        LATD = 0;
        INT0IF = 0;
    }
    if(INT1IF){
        LATD = 0xF0;
        INT1IF = 0;
    }
    if(INT2IF){
        LATD = 0b10101010;
        INT2IF = 0;
    }
    return;
}

void main(void) 
{
    ANSELD = 0;
    ANSELB = 0;
    
    TRISB = 0xFF;
    TRISD = 0x00;			// NAstaven� vstupu/v�stupu Portu D 
    LATD =  0xF0;		    // V�stupn� hodnota Portu D
    

    T0CON1 = 0b01000001;       // Nastaven� Timer0 (Fosc/4, synchonized, prescaler)
    T0CON0 = 0b10011111;        // Nastaven� Timer0 (TMR0 enable, 16bit, postscaler)
    
    TMR0IF = 0;        // Clear TMR0 flag bit 
    TMR0IE = 1;        // Set TMR0 enable bit
    GIE = 1;         // Set global interrupt enable bit
    GIEL = 1;
    IOCIE = 1;
    INT0IP = 1;
    INT1IP = 0;
    INT2IP =0;
    
    INT0IE = 1;
    INT1IE = 1;
    INT2IE =1;
    while(1)
    {
    
    }
    
    return;
}
