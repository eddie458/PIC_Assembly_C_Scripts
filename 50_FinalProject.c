#include "mcc_generated_files/mcc.h"

void main(void)
{

    SYSTEM_Initialize();
//    uint16_t Promedio_ADCC;
    int Promedio_ADCC;
    float PromedioFloat;
    float VoltajeEntrada;
    float Temperatura;

    while (1)
    {
        ADCC_StartConversion(channel_ANC0);
        while (ADCC_IsConversionDone()==false);
        Promedio_ADCC = ADCC_GetFilterValue();
        PromedioFloat = Promedio_ADCC;
        VoltajeEntrada = ((PromedioFloat*5)/4095);
        Temperatura = ((VoltajeEntrada*100)/3.22);
        
//      printf("Valor promedio medido ADCC: %04u\n\r",Promedio_ADCC);
        printf("Codigo del ADC: %d          Voltaje: %f         Temperatura: %f\n\r",Promedio_ADCC, VoltajeEntrada, Temperatura);
        
        if(PIR1bits.ADTIF==1)
        {
            LED_SetHigh();
            PIR1bits.ADTIF=0;
            
        }
        else
        {
            LED_SetLow();
            
        }
//        __delay_ms(100);
        IO_RA2_Toggle();
        
        if(PORTCbits.RC1==1) // Lampara
        {
            LATCbits.LATC4 = 1;
//            __delay_ms(100); 
        }
        if(PORTCbits.RC1==0) // Lampara 
        {
            LATCbits.LATC4 = 0;
//            __delay_ms(100); 
        }
        if(PORTCbits.RC2==1) // Bomba
        {
            LATCbits.LATC5= 1;
//            __delay_ms(100); 
        }
        if(PORTCbits.RC2==0) // Bomba
        {
            LATCbits.LATC5 = 0;
//            __delay_ms(100); 
        }
        if(PORTCbits.RC3==1) // Abanico
        {
            LATCbits.LATC6 = 1;
//            __delay_ms(100); 
        }
        if(PORTCbits.RC3==0) // Abanico
        {
            LATCbits.LATC6 = 0;
//            __delay_ms(100); 
        }
        
        if(Temperatura>40)
        {
            LATCbits.LATC5= 1; // Bomba
            LATCbits.LATC6= 1; // Abanico

        }
        if(Temperatura<15)
        {
            LATCbits.LATC4 = 1; // Lampara 

        }
        
    }
}
