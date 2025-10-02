#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include <stdio.h>
#include <stdint.h>

#define _LCD_FIRST_ROW          0x80     //Mueve el cursor a la 1ra columna
#define _LCD_SECOND_ROW         0xC0     //Mueve el cursor a la 2da columna
#define _LCD_THIRD_ROW          0x94     //Mueve el cursor a la 3ra columna
#define _LCD_FOURTH_ROW         0xD4     //Mueve el cursor a la 4ta columna
#define _LCD_CLEAR              0x01     //Limpia pantalla LCD
#define _LCD_RETURN_HOME        0x02     //Return cursor to home position, returns a
                                         //shifted display to its original position.
                                         //Display data RAM is unaffected.
#define _LCD_CURSOR_OFF         0x0C     //Desactiva el cursor
#define _LCD_UNDERLINE_ON       0x0E     //Habilita el guion bajo del cursor
#define _LCD_BLINK_CURSOR_ON    0x0F     //Habilita el blink del cursor
#define _LCD_MOVE_CURSOR_LEFT   0x10     //Move cursor left without changing
                                         //display data RAM
#define _LCD_MOVE_CURSOR_RIGHT  0x14     //Move cursor right without changing
                                         //display data RAM
#define _LCD_TURN_ON            0x0C     //Turn Lcd display on
#define _LCD_TURN_OFF           0x08     //Turn Lcd display off
#define _LCD_SHIFT_LEFT         0x18     //Shift display left without changing
                                         //display data RAM
#define _LCD_SHIFT_RIGHT        0x1E     //Shift display right without changing
                                         //display data RAM

#define LCD_RS LATCbits.LATC2
#define LCD_EN LATCbits.LATC3
#define LCD_D4 LATCbits.LATC4
#define LCD_D5 LATCbits.LATC5
#define LCD_D6 LATCbits.LATC6
#define LCD_D7 LATCbits.LATC7

#define LCD_RS_Direction TRISCbits.TRISC2
#define LCD_EN_Direction TRISCbits.TRISC3
#define LCD_D4_Direction TRISCbits.TRISC4
#define LCD_D5_Direction TRISCbits.TRISC5
#define LCD_D6_Direction TRISCbits.TRISC6
#define LCD_D7_Direction TRISCbits.TRISC7

#define EN_DELAY 200
#define LCD_STROBE {LCD_EN = 1; __delay_us(EN_DELAY); LCD_EN = 0; __delay_us(EN_DELAY);};

void LCD_Cmd(char out_char) {
    LCD_RS = 0;

    LCD_D4 = (out_char&0x10)?1:0;
    LCD_D5 = (out_char&0x20)?1:0;
    LCD_D6 = (out_char&0x40)?1:0;
    LCD_D7 = (out_char&0x80)?1:0;
    LCD_STROBE

    LCD_D4 = (out_char&0x01)?1:0;
    LCD_D5 = (out_char&0x02)?1:0;
    LCD_D6 = (out_char&0x04)?1:0;
    LCD_D7 = (out_char&0x08)?1:0;
    LCD_STROBE

    if(out_char == 0x01)__delay_ms(2);
}

void LCD_Clear ( void)
{
    LCD_Cmd(_LCD_CLEAR);
}

void LCD_Chr(char row, char column, char out_char)
{
    switch(row) {
        case 1:
            LCD_Cmd(0x80 + (column - 1));
            break;
        case 2:
            LCD_Cmd(0xC0 + (column - 1));
            break;
        case 3:
            LCD_Cmd(0x94 + (column - 1));
            break;
        case 4:
            LCD_Cmd(0xD4 + (column - 1));
            break;
    }

    LCD_RS = 1;

    LCD_D4 = (out_char & 0x10)?1:0;
    LCD_D5 = (out_char & 0x20)?1:0;
    LCD_D6 = (out_char & 0x40)?1:0;
    LCD_D7 = (out_char & 0x80)?1:0;
    LCD_STROBE

    LCD_D4 = (out_char & 0x01)?1:0;
    LCD_D5 = (out_char & 0x02)?1:0;
    LCD_D6 = (out_char & 0x04)?1:0;
    LCD_D7 = (out_char & 0x08)?1:0; 
    LCD_STROBE
}

void LCD_Chr_Cp(char out_char) 
{
    LCD_RS = 1;

    LCD_D4 = (out_char & 0x10)?1:0;
    LCD_D5 = (out_char & 0x20)?1:0;
    LCD_D6 = (out_char & 0x40)?1:0;
    LCD_D7 = (out_char & 0x80)?1:0;
    LCD_STROBE

    LCD_D4 = (out_char & 0x01)?1:0;
    LCD_D5 = (out_char & 0x02)?1:0;
    LCD_D6 = (out_char & 0x04)?1:0;
    LCD_D7 = (out_char & 0x08)?1:0; 
    LCD_STROBE
}

void LCD_Init () 
{
    __delay_ms(200);

    LCD_RS_Direction = 0;
    LCD_EN_Direction = 0;
    LCD_D4_Direction = 0;
    LCD_D5_Direction = 0;
    LCD_D6_Direction = 0;
    LCD_D7_Direction = 0;
 
    ANSELA = 0x00;  // Desabilita las entradas analogicas conectadas al puerto A 
    ANSELB = 0x00;  // Desabilita las entradas analogicas conectadas al puerto B     
    ANSELC = 0x00;  // Desabilita las entradas analogicas conectadas al puerto C 
    
    LCD_RS = 0;
    LCD_EN = 0;
    LCD_D4 = 0;
    LCD_D5 = 0;
    LCD_D6 = 0;
    LCD_D7 = 0; 
    __delay_ms(30);
    LCD_D4 = 1;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    LCD_STROBE
    __delay_ms(30);
    LCD_D4 = 1;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    LCD_STROBE
    __delay_ms(30);
    LCD_D4 = 1;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    LCD_STROBE
    __delay_ms(30);
    LCD_D4 = 0;
    LCD_D5 = 1;
    LCD_D6 = 0;
    LCD_D7 = 0;
    LCD_STROBE
    __delay_ms(30);
    LCD_Cmd(0x28);
    LCD_Cmd(0x06);
    LCD_Cmd(_LCD_CURSOR_OFF);
}

void LCD_gotoxy_putc(char row, char col, char *text) {
    while(*text)
         LCD_Chr(row, col++, *text++);
}

void LCD_Out_Cp(char *text) {
    while(*text)
         LCD_Chr_Cp(*text++);
}

char LCD_Buffer [20];
float Decimal   = 0.78;
uint16_t Entero = 427;

void main(void)
{
    SYSTEM_Initialize();
    LCD_Init();
    LCD_Clear();
    
    while (1)
    {
        LCD_gotoxy_putc(1,1,"Sistemas 2021 :D");
        LCD_gotoxy_putc(2,1,"Curiosity Nano  ");

        __delay_ms(1000);
        LCD_Clear();
        sprintf(LCD_Buffer,"Valor Int: %03u", Entero);
        LCD_gotoxy_putc(1,1,LCD_Buffer);
        sprintf(LCD_Buffer,"Valor Dec: %03.2f", Decimal);
        LCD_gotoxy_putc(2,1,LCD_Buffer);
        __delay_ms(1000);
        LCD_Clear();
    }
}
