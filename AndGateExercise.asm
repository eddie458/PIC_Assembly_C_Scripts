;***************************************************************
; Sistemas Digitales II		11-13		18 Febrero 2020.
; Programa #3. Compuerta AND y salida con PUERTO B.
; Realizado por Jesus Nunez  
;*************************************************************** 
    list p=16f877A			;Usaremos pic 16f877a. 
    include "p16f877A.inc"		;Agrega la definición de registros. 
;--------------------Declarar las variables--------------------
    Cblock 0x20 
;--------------------Agregar las variables -------------------- 
    endc 
;--------------------Palabra de Configuración-------------------- 
  __CONFIG _CP_OFF & _DEBUG_OFF & _WRT_OFF & _CPD_OFF & _LVP_OFF & _BODEN_ON & _PWRTE_ON & _WDT_OFF & _HS_OSC 
    radix   hex				;Usa numeros en hexadecimal. 
;--------------------Configura origen del programa--------------------
    org      0x00			;El origen del programa comienza aquí si hay un reset. 
    goto    INICIO			;Salva el vector de interrupción. 
    org      0x05			;Origen del código del programa. 
;--------------------Selecciona el banco 1--------------------
INICIO  
    bsf STATUS, RP0
    bcf STATUS, RP1

;--------------------Configura registros--------------------
    movlw 0xFF
    movwf TRISC				;Puerto C es entrada.
    movlw 0x00
    movwf TRISB				;Puerto B es salida. 
;--------------------Selecciona el banco 0--------------------
    bcf STATUS, RP1
    bcf STATUS, RP0
 
;--------------------Empieza el programa--------------------
CICLO
    movf PORTC, W			;PORTC -> W	
    andlw 0x0F				;W AND 0x0F -> W
    movwf PORTB				;W -> PORTB
    goto CICLO
    end
