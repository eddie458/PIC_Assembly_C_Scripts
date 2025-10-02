;***************************************************************
; Sistemas Digitales II.		11-13.		Marzo 2020.
; Programa #0. Diseñe un programa que encienda el LED 60ms y lo apague 60ms, mostrarlo en el pin RD5.
; Valor a cargar en el timer para 60ms es de .22
; Realizado por Jesus Nunez.  
;*************************************************************** 
    list p=16f877A			;Usaremos pic 16f877a. 
    include "p16f877A.inc"		;Agrega la definición de registros. 
;--------------------Declarar las variables--------------------
    Cblock 0x20 
	WTEMP
	STATUSTEMP
	CUENTA
    endc 
;--------------------Palabra de Configuración-------------------- 
    __CONFIG _CP_OFF & _DEBUG_OFF & _WRT_OFF & _CPD_OFF & _LVP_OFF & _BODEN_ON & _PWRTE_ON & _WDT_OFF & _HS_OSC 
    radix   hex				;Usa numeros en hexadecimal. 
;--------------------Configura origen del programa--------------------
    org     0x00			;El origen del programa comienza aquí si hay un reset. 
    goto    INICIO			;Salva el vector de interrupción. 
    org	    0x04
    goto    INTERRUPT			;Salta a la rutina de servicio de interrupcion.
    org	    0x05			;Origen del código del programa. 
;--------------------Selecciona el banco 0--------------------
INICIO  
    
    bcf	    STATUS, RP1
    bcf	    STATUS, RP0
    clrf    PORTA

    ;--------------------Selecciona el banco 1--------------------
    bsf	    STATUS, RP0
    bcf	    STATUS, RP1
    
;--------------------Configura registros--------------------
    movlw   0xC0
    movwf   INTCON		    ;Configura interrupcion RB0.
    
    movlw   0x01
    bsf	    PIE1, TMR1IE
    
    bcf	    PIR1, TMR1IF
    
    movlw   0x35
    movwf   T1CON
    
    movlw   0x00
    movwf   TRISB
    
    movlw   0xFF
    movwf   TRISA
    
    movlw   0x00
    movwf   TRISD
    
    movlw   0x87   
    movwf   OPTION_REG
       
 		 
    
;--------------------Selecciona el banco 0--------------------
    bcf	    STATUS, RP1
    bcf	    STATUS, RP0
 
;--------------------Empieza el programa--------------------

    clrf    CUENTA
    
;||||||||||||||||||||Zona de Mensajes||||||||||||||||||||

;||||||||||||||||||||Termino de Mensajes||||||||||||||||||||   
    
;||||||||||||||||||||Zona de Interrupciones||||||||||||||||||||       
INTERRUPT
    movwf   WTEMP		; RESPALDA W 
    movf    STATUS,W	; Respalda STATUS
    movwf   STATUSTEMP

    call    Retardo_20ms
    


    bcf	    PIR1,TMR1IF	; Borra la bandera
    movf    STATUSTEMP,W
    movwf   STATUS
    movf    WTEMP,W
    retfie
        
;||||||||||||||||||||Termino de Interrupciones||||||||||||||||||||   
    
;||||||||||||||||||||Zona de Subrutinas||||||||||||||||||||
 
;||||||||||||||||||||Termino de Subrutinas||||||||||||||||||||    
    
;--------------------Zona De Includes--------------------
    include "LCD_4BIT.INC"    
    include "RETARDOS.INC"   
    include "BIN_BCD.INC"
    include "LCD_MENS.inc"  
        
;--------------------Zona De Includes--------------------
    

    end