;***************************************************************
; Sistemas Digitales II.		11-13.		09 Marzo 2020.
; Programa. Hacer un programa para generar una señal cuadrada de 1 segundo.
; Realizado por Jesus Nunez.  
;*************************************************************** 
    list p=16f877A			;Usaremos pic 16f877a. 
    include "p16f877A.inc"		;Agrega la definición de registros. 
;--------------------Declarar las variables--------------------
    Cblock 0x20 
	VAR1
	VAR2
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
    movlw   0x00
    movwf   TRISD			;Puerto D es salida. 
;--------------------Selecciona el banco 0--------------------
    bcf	    STATUS, RP1
    bcf	    STATUS, RP0
 
;--------------------Empieza el programa--------------------
CICLO
    bsf	    PORTD, RD5
    call    RETARDO_1s			;Prender el bit 5 del PORTB.
    bcf	    PORTD, RD5
    call    RETARDO_1s			;Apagar el bit 5 del puerto B.
    goto    CICLO
    
      
;||||||||||||||||||||Zona de Subrutinas||||||||||||||||||||
     
;--------------------Subrutina de Retardo--------------------       
RETARDO_1s
    movlw   .16
    movwf   Veces

SECUENCIA
    movlw   .11
    movwf   TMR0 
ESPERA					;Polling que espera el overflow de la bandera. 
    btfss   INTCON, TMR0IF		;Timer TMR0IF = 1
    goto    ESPERA
    bcf	    INTCON, TMR0IF
    
    decfsz  Veces, F
    goto    SECUENCIA
    
    return
    
;--------------------Subrutina de Retardo--------------------
    
;||||||||||||||||||||Termino de Subrutinas||||||||||||||||||||
    end