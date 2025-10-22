#define _XTAL_FREQ 8000000

#define LCD_RS LATBbits.LATB4
#define LCD_EN LATBbits.LATB5
#define LCD_DATA LATB

void Send_Command (char cmd);
void Send_Data (char dat);
