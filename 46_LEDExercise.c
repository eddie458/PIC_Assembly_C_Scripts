/*
 * File:   PuertosC.c
 * Author: nunez
 *
 * Created on April 22, 2021, 12:05 PM
 */

#include <xc.h>
#define _XTAL_FREQ 4000000 //OSCILADOR INTERNO FRECUENCIA 4 MHz
#define LED_VERDE 2
#define LED_ROJO 5

void main(void) { 

                          // Activa el oscilador interno a 4 MHZ    

        OSCCON1 = 0x60;   // NOSC HFINTOSC; NDIV 1; 

        OSCCON3 = 0x00;   // CSWHOLD may proceed; SOSCPWR Low power; 

        OSCEN = 0x00;     // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled 

        OSCFRQ = 0x02;    // HFFRQ 4 MHz 

                         // ---- configura puerto 1 entrada 0 salida 

        TRISA = 0x00;    // Configura PUERTO A con salida 

        TRISB = 0x00;    // Configura PUERTO B con salida 

        TRISC = 0x00;    // Configura PUERTO C con salida     

                // -------- habilita (1) o desabilita (0) entradas analogicas  

        ANSELA = 0x00;  // Desabilita las entradas analogicas conectadas al puerto A 

        ANSELB = 0x00;  // Desabilita las entradas analogicas conectadas al puerto B     

        ANSELC = 0x00;  // Desabilita las entradas analogicas conectadas al puerto C 

        // Inicializar puertos para salida usar LATx, entrada PORTx 

        LATA =0x00;    // Inicializa el puerto A en ceros, envia 0 al PUERTO A 

        LATB =0x00;    // Inicializa el puerto B en ceros, envia 0 al PUERTO B  

        LATC =0x00;    // Inicializa el puerto C en ceros, envia 0 al PUERTO C 

         

        // ----- inicia el programa ---- 

        LATC = 0x01;
        while (1) 

        { 
            LATC = (LATC>>1) | (LATC<<7);
            __delay_ms(1000);

        }

         

    return; 

} 
