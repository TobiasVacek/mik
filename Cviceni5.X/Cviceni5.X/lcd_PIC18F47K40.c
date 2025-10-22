#include <xc.h>
#include "lcd_PIC18F47K40.h"

void Send()  
{
  LCD_EN = 1;
  __delay_us(1);
  LCD_EN = 0;
}

void Send_Command (char cmd)
{  
  LCD_DATA = cmd>>4;
  LCD_RS = 0;
  Send();
  LCD_DATA &= 0xF0;
  LCD_DATA |= (cmd&0x0F);
  LCD_RS = 0;
  Send();
  __delay_ms(2);
}

void Send_Data (char dat)
{
  LCD_DATA = dat>>4;  
  LCD_RS = 1;
  Send();
  LCD_DATA &=0xF0;
  LCD_DATA |= (dat&0x0F);  
  LCD_RS = 1;
  Send();
  __delay_us(50);
}


