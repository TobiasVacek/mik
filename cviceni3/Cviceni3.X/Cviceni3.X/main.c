
// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC  // Power-up default value for COSC bits (EXTOSC operating per FEXTOSC bits (device manufacturing default))

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

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
#include <stdbool.h>
#include <math.h>
#define _XTAL_FREQ 8000000

uint16_t i;

char getKey(){
    LATB = 0xFF;
    char key = 'q'; //default char if nothing is pressed
    short idx = 0;
    bool pressed = false;
    char keys[4][4] = {
        {'1', '4', '7', '*'},
        {'2', '5', '8', '0'},
        {'3', '6', '9', '#'},
        {'A','B','C','D'}
    };
    short row = -1;
    short col = -1;
    while(idx<4){
        if(PORTB & 1<<(idx+4)){
            row = idx;
            pressed = true;
            break;
        }
        idx++;
    }

    if(pressed){
        idx = 0;
        while(idx<4){  
            LATB |= 0x0F;
            LATB = LATB & ~(1<<idx);
            if(!(PORTB & (1<<row+4))){
                col = idx;
                break;
            }
            idx++;
            
        
           
        }
        return keys[col][row]; 
    }
    return key;
}
void showTime(short *time){
    int num = 0;
    for(int j = 0; j<4; j++){
        num = time[j];
        LATA = 1<<j;
        switch(num){
        case 0:
            LATD = 0b00111111;
            break;
            
        case 1:
            LATD = 0b00000110;
            break;
        case 2:
            LATD = 0b01011011;
            break;
        case 3:
            LATD = 0b01001111;
            break;
        case 4:
            LATD = 0b01100110;
            break;
        case 5:
            LATD = 0b01101101;
            break;
        case 6:
            LATD = 0b01111101;
            break;
        case 7:
            LATD = 0b00000111;
            break;
        case 8:
            LATD = 0b01111111;
            break;
        case 9:
            LATD = 0b01101111;
            break;
            
            
    }__delay_ms(1);
    }
           
    }

void main() 
{
    short i = 0;
    short time = 0;
    char key = 'q';
    char last_key = 'q';
    short nums[] = {0,0,0,0};
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    TRISA  = 0b00000000;
    TRISB  = 0b11110000;
    TRISC  = 0;
    TRISD  = 0;
    LATA   = 0xFF;
    LATB   = 0x0F;
    LATC   = 0b10000001;
    LATD   = 0;
    
    while (1) 
    {
        
        key = getKey();
        if(key >= '0' && key <= '9' && last_key != key){
            for(i = 3; i>0; i--){
                nums[i] = nums[i-1];
            }
            nums[0] = key -'0';
            
            i++;
            
        }
        last_key = key;
        showTime(&nums);
        __delay_ms(1);
        
}
}