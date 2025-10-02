;***************************************************************
; Sistemas Digitales II		11-13		18 Febrero 2020.
; Programa #2. Manejo de puertos, suma 5 al puerto C.
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
PRINCIPAL
    movf    PORTC, W
    andlw   b'00000111'
    addwf   PCL, F
TABLA
    goto    Configuracion0
    goto    Configuracion1
    goto    Configuracion2
    goto    Configuracion3
    goto    Configuracion4
    goto    Configuracion5
    goto    Configuracion6
    goto    Configuracion7
    
Configuracion0
    movlw   b'00000000'
    goto    ActivaSalida		;(Configuracion 0).
Configuracion1
    movlw   b'00000001'
    goto    ActivaSalida		;(Configuracion 1).
Configuracion2
    movlw   b'00000011'
    goto    ActivaSalida		;(Configuracion 2).
Configuracion3
    movlw   b'00000111'
    goto    ActivaSalida		;(Configuracion 3).
Configuracion4
    movlw   b'00001111'
    goto    ActivaSalida		;(Configuracion 4).
Configuracion5
    movlw   b'00011111'
    goto    ActivaSalida		;(Configuracion 5).
Configuracion6
    movlw   b'00111111'
    goto    ActivaSalida		;(Configuracion 6).
Configuracion7
    movlw   b'01111111'
    goto    ActivaSalida		;(Configuracion 7).
ActivaSalida
    movwf   PORTB
    goto    PRINCIPAL			;Visualiza por el puerto de salida.
    
    END
