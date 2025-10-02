/*
 * File:   FinalProject_4.c
 * Author: nunez
 *
 * Created on May 1, 2021, 9:50 PM
 */


#include <xc.h>
//#define LED_VERDE RA2
//#define LED_ROJO RB5

void main(void) 
{
    OSCCON1 = 0x60;     // NOSC HFINTOSC; NDIV 1; 
    OSCCON3 = 0x00;     // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCEN = 0x00;       // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled 
    OSCFRQ = 0x02;      // HFFRQ 4 MHz 
                        // ---- configura puerto 1 entrada 0 salida 
    TRISA = 0x00;       // Configura PUERTO A con salida
    TRISB = 0x00;       // Configura PUERTO B con salida 
    TRISC = 0x00;       // Configura PUERTO C con salida     
                        // -------- habilita (1) o desabilita (0) entradas analogicas  
    ANSELA = 0x00;      // Desabilita las entradas analogicas conectadas al puerto A 
    ANSELB = 0x00;      // Desabilita las entradas analogicas conectadas al puerto B     
    ANSELC = 0x00;      // Desabilita las entradas analogicas conectadas al puerto C 
                        // Inicializar puertos para salida usar LATx, entrada PORTx 
    LATA =0x00;         // Inicializa el puerto A en ceros, envia 0 al PUERTO A 
    LATB =0x00;         // Inicializa el puerto B en ceros, envia 0 al PUERTO B  
    LATC =0x00;         // Inicializa el puerto C en ceros, envia 0 al PUERTO C  
    
    while (1) 
    {
        LATA0 = 0x01; 
        
    }
    
    return;
}
