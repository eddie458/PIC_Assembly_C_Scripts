/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18446
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
void main(void)
{

    SYSTEM_Initialize();
//    uint16_t Promedio_ADCC;
    int Promedio_ADCC1;
    int Promedio_ADCC2;
    float PromedioFloat1;
    float PromedioFloat2;
    float VoltajeEntrada1;
    float VoltajeEntrada2;
    float Temperatura;
    float Humedad;

    while (1)
    {
        // Add your application code
        ADCC_StartConversion(channel_ANC0);
        while (ADCC_IsConversionDone()==false);
        Promedio_ADCC1 = ADCC_GetFilterValue();
        PromedioFloat1 = Promedio_ADCC1;
        VoltajeEntrada1 = ((PromedioFloat1*5)/4095);
        Temperatura = ((VoltajeEntrada1*100)/5);
        
        
        
//        printf("Valor promedio medido ADCC: %04u\n\r",Promedio_ADCC);
        
        if(PIR1bits.ADTIF==1)
        {
            LED_SetHigh();
            PIR1bits.ADTIF=0;
            
        }
        else
        {
            LED_SetLow();
            
        }
          
        ADCC_StartConversion(channel_ANC1);
        while (ADCC_IsConversionDone()==false);
        Promedio_ADCC2 = ADCC_GetFilterValue();
        PromedioFloat2 = Promedio_ADCC2;
        VoltajeEntrada2 = ((PromedioFloat2*5)/4095);
        Humedad = ((VoltajeEntrada2*100)/5);   
               
//        printf("Codigo del ADC: %d          Humedad: %f         Temperatura: %f\n\r",Promedio_ADCC, HumedadValor, Temperatura);  
        printf("Codigo del ADC 0: %d          Codigo del ADC 1: %d\n\r",Promedio_ADCC1, Promedio_ADCC2); 
        
        __delay_ms(500);
        IO_RA2_Toggle();
    }
}
/**
 End of File
*/