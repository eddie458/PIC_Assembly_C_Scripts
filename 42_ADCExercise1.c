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
        // Add your application code
        ADCC_StartConversion(channel_ANC0);
        while (ADCC_IsConversionDone()==false);
        Promedio_ADCC = ADCC_GetFilterValue();
        PromedioFloat = Promedio_ADCC;
        VoltajeEntrada = ((PromedioFloat*5)/4095);
        Temperatura = ((VoltajeEntrada*100)/5);
        
//        printf("Valor promedio medido ADCC: %04u\n\r",Promedio_ADCC);
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
        __delay_ms(500);
        IO_RA2_Toggle();
    }
}
/**
 End of File
*/