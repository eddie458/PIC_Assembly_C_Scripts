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

#define LCD_RS LATAbits.LATA2
#define LCD_EN LATAbits.LATA4
#define LCD_D4 LATAbits.LATA5
#define LCD_D5 LATBbits.LATB5
#define LCD_D6 LATCbits.LATC3
#define LCD_D7 LATCbits.LATC4

#define LCD_RS_Direction TRISAbits.TRISA2
#define LCD_EN_Direction TRISAbits.TRISA4
#define LCD_D4_Direction TRISAbits.TRISA5
#define LCD_D5_Direction TRISBbits.TRISB5
#define LCD_D6_Direction TRISCbits.TRISC3
#define LCD_D7_Direction TRISCbits.TRISC4

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

void main(void)
{
    SYSTEM_Initialize();

    LCD_Init();
    LCD_Clear();
    
    int Promedio_ADCC0;
    int Promedio_ADCC1;
    int Promedio_ADCC2;
    float PromedioFloat0;
    float PromedioFloat1;
    float PromedioFloat2;
    float VoltajeEntrada0;
    float VoltajeEntrada1;
    float VoltajeEntrada2;
    float TemperaturaReal;
    float Temperatura;
    float Humedad;

    while (1)
    {
        ADCC_StartConversion(channel_ANC0);
        while (ADCC_IsConversionDone()==false);
        Promedio_ADCC0 = ADCC_GetFilterValue();
        PromedioFloat0 = Promedio_ADCC0;
        VoltajeEntrada0 = ((PromedioFloat0*5)/4095);
        Temperatura = ((VoltajeEntrada0*100)/8.33);
        
        ADCC_StartConversion(channel_ANC1);
        while (ADCC_IsConversionDone()==false);
        Promedio_ADCC1 = ADCC_GetFilterValue();
        PromedioFloat1 = Promedio_ADCC1;
        VoltajeEntrada1 = ((PromedioFloat1*5)/4095);
        Humedad = ((VoltajeEntrada1*100)/5);
        
        ADCC_StartConversion(channel_ANC2);
        while (ADCC_IsConversionDone()==false);
        Promedio_ADCC2 = ADCC_GetFilterValue();
        PromedioFloat2 = Promedio_ADCC2;
        VoltajeEntrada2 = ((PromedioFloat2*5)/4095);
        TemperaturaReal = ((VoltajeEntrada2*100)/3.22);
        
        printf("-----------------------------------------------------------------------------------------\n\r"); 
//        printf("Codigo del ADC 0: %d          Codigo del ADC 1: %d      Codigo del ADC 2: %d\n\r",Promedio_ADCC0,Promedio_ADCC1, Promedio_ADCC2); 
        printf("Temperatura:        %5.2f°C \n\r",Temperatura); 
        printf("Humedad Relativa:   %5.2f%% \n\r",Humedad); 
        printf("Temperatura Real:   %5.2f°C \n\r",TemperaturaReal); 
        
        // Control de Temperatura usando Lámpara.
        if(Temperatura<15)
        {
            IO_RC7_SetHigh(); //Lámpara
        }
        else
        {
            IO_RC7_SetLow(); //Lámpara
        }
        
        // Control de Humedad Usando Extractor y Bomba de Agua
        if(Humedad>40)
        {
            IO_RC5_SetHigh(); //Abanico
            IO_RC6_SetLow(); //Bomba
        }
        else if(Humedad<10)
        {
            IO_RC5_SetLow(); //Abanico
            IO_RC6_SetHigh(); //Bomba   
        }
        else
        {
            IO_RC5_SetLow(); //Abanico
            IO_RC6_SetLow(); //Bomba
        }  
        //__delay_ms(1000);
        IO_RA2_Toggle();
        
//        LCD_gotoxy_putc(1,1,"Invernadero-UACJ");
//        LCD_gotoxy_putc(2,1,"Sist. Digitales");
//        __delay_ms(1000);
//        LCD_Clear();
//        
        sprintf(LCD_Buffer,"Temp: %4.2f%cC     ",Temperatura,223);
        LCD_gotoxy_putc(1,1,LCD_Buffer);
        sprintf(LCD_Buffer,"Humedad: %5.2f%%   ",Humedad);
        LCD_gotoxy_putc(2,1,LCD_Buffer);
        __delay_ms(100);
//        LCD_Clear();
        
    }
}
