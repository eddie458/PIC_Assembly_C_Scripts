/*
 * File:   FinalProject_1.c
 * Author: nunez
 *
 * Created on May 1, 2021, 3:45 PM
 */


#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000 //OSCILADOR INTERNO FRECUENCIA 4 MHz
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
// set up the timing for the LCD delays
#define LCD_delay 5 // ~5mS
#define LCD_Startup 15 // ~15mS

// Command set for Hitachi 44780U LCD display controller
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_CURSOR_BACK 0x10
#define LCD_CURSOR_FWD 0x14
#define LCD_PAN_LEFT 0x18
#define LCD_PAN_RIGHT 0x1C
#define LCD_CURSOR_OFF 0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_CURSOR_BLINK 0x0F
#define LCD_CURSOR_LINE2 0xC0

// display controller setup commands from page 46 of Hitachi datasheet
#define FUNCTION_SET 0x28 // 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE 0x06 // increment mode
#define DISPLAY_SETUP 0x0C // display on, cursor off, blink offd

#define LCDLine1() LCDPutCmd(LCD_HOME) // legacy support
#define LCDLine2() LCDPutCmd(LCD_CURSOR_LINE2) // legacy support
#define shift_cursor() LCDPutCmd(LCD_CURSOR_FWD) // legacy support
#define cursor_on() LCDPutCmd(LCD_CURSOR_ON) // legacy support
#define DisplayClr() LCDPutCmd(LCD_CLEAR) // Legacy support

// These #defines create the pin connections to the LCD in case they are changed on a future demo board
#define LCD_PORT PORTC
#define LCD_PWR PORTCbits.RC7 // LCD power pin
#define LCD_EN PORTCbits.RC6 // LCD enable
#define LCD_RW PORTCbits.RC5 // LCD read/write line
#define LCD_RS PORTCbits.RC4 // LCD register select line

#define NB_LINES 2 // Number of display lines
#define NB_COL 16 // Number of characters per line

void LCD_Initialize(void);
void LCDPutChar(char ch);
void LCDPutCmd(char ch);
void LCDPutStr(const char *); 
void LCDWriteNibble(char ch, char rs);
void LCDGoto(char pos, char ln);

// single bit for selecting command register or data register
#define instr 0
#define data 1

void LCD_Initialize()
{
    // clear latches before enabling TRIS bits
    LCD_PORT = 0;

//    TRISD = 0x00;
    
    // power up the LCD
    LCD_PWR = 1;

    // required by display controller to allow power to stabilize
    __delay_ms(LCD_Startup);

    // required by display initialization
    LCDPutCmd(0x32);

    // set interface size, # of lines and font
    LCDPutCmd(FUNCTION_SET);

    // turn on display and sets up cursor
    LCDPutCmd(DISPLAY_SETUP);

    DisplayClr();

    // set cursor movement direction
    LCDPutCmd(ENTRY_MODE);

}

void LCDWriteNibble(char ch, char rs)
{
    // always send the upper nibble
    ch = (ch >> 4);

    // mask off the nibble to be transmitted
    ch = (ch & 0x0F);

    // clear the lower half of LCD_PORT
    LCD_PORT = (LCD_PORT & 0xF0);

    // move the nibble onto LCD_PORT
    LCD_PORT = (LCD_PORT | ch);

    // set data/instr bit to 0 = insructions; 1 = data
    LCD_RS = rs;

    // RW - set write mode
    LCD_RW = 0;

    // set up enable before writing nibble
    LCD_EN = 1;

    // turn off enable after write of nibble
    LCD_EN = 0;
}

void LCDPutChar(char ch)
{
    __delay_ms(LCD_delay);

    //Send higher nibble first
    LCDWriteNibble(ch,data);

    //get the lower nibble
    ch = (ch << 4);

    // Now send the low nibble
    LCDWriteNibble(ch,data);
}

void LCDPutCmd(char ch)
{
    __delay_ms(LCD_delay);

    //Send the higher nibble
    LCDWriteNibble(ch,instr);

    //get the lower nibble
    ch = (ch << 4);

    __delay_ms(1);

    //Now send the lower nibble
    LCDWriteNibble(ch,instr);
}


void LCDPutStr(const char *str)
{
    char i=0;

    // While string has not been fully traveresed
    while (str[i])
    {
    // Go display current char
    LCDPutChar(str[i++]);
    }

}

void LCDGoto(char pos,char ln)
{
    // if incorrect line or column
    if ((ln > (NB_LINES-1)) || (pos > (NB_COL-1)))
    {
    // Just do nothing
    return;
    }

    // LCD_Goto command
    LCDPutCmd((ln == 1) ? (0xC0 | pos) : (0x80 | pos));

    // Wait for the LCD to finish
    __delay_ms(LCD_delay);
}


//#pragma config FEXTOSC = OFF // Oscillator Selection bits (HS oscillator)
//#pragma config RSTOSC = HFINT32 
//#pragma config FCMEN = OFF  // when external osc fail , turn on the internal osc monitor
//#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
//#pragma config PWRTS = OFF // Power-up Timer Enable bit (PWRT disabled)
//#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
//#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming
//#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//#pragma config CSWEN = ON       //clock switch writing enable bit


void main(void) 
{
                            // Activa el oscilador interno a 4 MHZ    

    OSCCON1 = 0x60;     // NOSC HFINTOSC; NDIV 1; 

    OSCCON3 = 0x00;     // CSWHOLD may proceed; SOSCPWR Low power; 

    OSCEN = 0x00;       // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled 

    OSCFRQ = 0x02;      // HFFRQ 4 MHz 

                        // ---- configura puerto 1 entrada 0 salida 

    TRISA = 0x00;       // Configura PUERTO A con salida 

    TRISB = 0x00;       // Configura PUERTO B con salida 

    TRISC = 0x00;       // Configura PUERTO C con salida     

    //TRISA = 0b00000000;

    //TRISB = 0b00000000;

                        // -------- habilita (1) o desabilita (0) entradas analogicas  

                        // analog selector register to set PORTA pins to digit 

    ANSELA = 0x00;      // Desabilita las entradas analogicas conectadas al puerto A 

    ANSELB = 0x00;      // Desabilita las entradas analogicas conectadas al puerto B     

    ANSELC = 0x00;      // Desabilita las entradas analogicas conectadas al puerto C 

    // Inicializar puertos para salida usar LATx, entrada PORTx 

    LATA =0x00;         // Inicializa el puerto A en ceros, envia 0 al PUERTO A 

    LATB =0x00;         // Inicializa el puerto B en ceros, envia 0 al PUERTO B  

    LATC =0x00;         // Inicializa el puerto C en ceros, envia 0 al PUERTO C 




    LCD_Initialize();
    LCDPutStr(" Hello World!"); //Display String "Hello World"
    LCDGoto(8,1); //Go to column 8 of second line
    LCDPutChar('1'); //Display character '1'
    DisplayClr(); // Clear the display

    LCDPutStr(" LCD Display"); // Display a string "LCD Display"
    LCDGoto(0,1); //Go to second line 
    LCDPutStr("Micro Lab"); //Display String "Micro Lab" 
    while (1)
        {
        // Add your application code
        }
        
    return;
}
