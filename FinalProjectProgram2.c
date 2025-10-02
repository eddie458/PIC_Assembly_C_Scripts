#include "mcc_generated_files/mcc.h"


void main(void)
{
    SYSTEM_Initialize();

    printf("INICIO\n\r");
    uint8_t contador = 0;

    while (1)
    {
        printf("Hola Mundo: %u \n\r",contador++);
        YELLOW_LED_Toggle();
         __delay_ms(1000);
    }
}
