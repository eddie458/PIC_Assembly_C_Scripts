;***************************************************************
; Sistemas Digitales II.		11-13.		Marzo 2020.
; Programa #0. 
; Realizado por Jesus Nunez.  
;*************************************************************** 
    list p=16f877A			;Usaremos pic 16f877a. 
    include "p16f877A.inc"		;Agrega la definición de registros. 
;--------------------Declarar las variables--------------------
    Cblock 0x20 
    Veces	
    endc 
;--------------------Palabra de Configuración-------------------- 
    __CONFIG _CP_OFF & _DEBUG_OFF & _WRT_OFF & _CPD_OFF & _LVP_OFF & _BODEN_ON & _PWRTE_ON & _WDT_OFF & _HS_OSC 
    radix   hex				;Usa numeros en hexadecimal. 
;--------------------Configura origen del programa--------------------
    org     0x00			;El origen del programa comienza aquí si hay un reset. 
    goto    INICIO			;Salva el vector de interrupción. 
    org	    0x05			;Origen del código del programa. 
;--------------------Selecciona el banco 1--------------------
INICIO  
    bsf	    STATUS, RP0
    bcf	    STATUS, RP1

;--------------------Configura registros--------------------
    movlw   0x87
    movwf   OPTION_REG
    movlw   0xFF
    movwf   TRISC				;Puerto C es entrada.
    movlw   0x00
    movwf   TRISB				;Puerto B es salida. 
;--------------------Selecciona el banco 0--------------------
    bcf	    STATUS, RP1
    bcf	    STATUS, RP0
 ;--------------------Empieza el programa--------------------
PRINCIPAL
    clrf    PORTB
    movf    PORTC, W
    andlw   b'00000100'
    addwf   PCL, F
Opcion
    goto    Opcion0
    goto    Opcion1
    
Opcion0 
    clrf    PORTB
    goto    Salida		;(Configuracion 0).
Opcion1
    clrf    PORTB
    bsf	    PORTB, RD2
    call    RETARDO1		;Prender el bit 2 del PORTB.
    bcf	    PORTB, RD2
    call    RETARDO2		;Apagar el bit 2 del PORTB.
    goto    Salida		;(Configuracion 1).
Salida
    
    goto    PRINCIPAL		
    
    
      
;||||||||||||||||||||Zona de Subrutinas||||||||||||||||||||
  
;--------------------Subrutina de Retardo-------------------- 
RETARDO1
    movlw   .16
    movwf   Veces

SECUENCIA1
    movlw   .11
    movwf   TMR0 
ESPERA1					;Polling que espera el overflow de la bandera. 
    btfss   INTCON, TMR0IF		;Timer TMR0IF = 1
    goto    ESPERA1
    bcf	    INTCON, TMR0IF
    
    decfsz  Veces, F
    goto    SECUENCIA1
    
    return
;--------------------Subrutina de Retardo-------------------- 
    
;--------------------Subrutina de Retardo-------------------- 
RETARDO2
    movlw   .40
    movwf   Veces

SECUENCIA2
    movlw   .1
    movwf   TMR0 
ESPERA2					;Polling que espera el overflow de la bandera. 
    btfss   INTCON, TMR0IF		;Timer TMR0IF = 1
    goto    ESPERA2
    bcf	    INTCON, TMR0IF
    
    decfsz  Veces, F
    goto    SECUENCIA2
    
    return
;--------------------Subrutina de Retardo-------------------- 
        
;||||||||||||||||||||Termino de Subrutinas||||||||||||||||||||
    end