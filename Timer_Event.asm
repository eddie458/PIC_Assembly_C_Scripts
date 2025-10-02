;***************************************************************
; Sistemas Digitales II.		11-13.		16 Marzo 2020.
; Programa. Hacer un programa para contar eventos externos alimentados por RA4. Que registros se requieren?
; Realizado por Jesus Nunez.  
;*************************************************************** 
    list p=16f877A			;Usaremos pic 16f877a. 
    include "p16f877A.inc"		;Agrega la definición de registros. 
;--------------------Declarar las variables--------------------
    Cblock 0x20 
	VAR1
	VAR2
    endc 
;--------------------Palabra de Configuración-------------------- 
    __CONFIG _CP_OFF & _DEBUG_OFF & _WRT_OFF & _CPD_OFF & _LVP_OFF & _BODEN_ON & _PWRTE_ON & _WDT_OFF & _HS_OSC 
    radix   hex				;Usa numeros en hexadecimal. 
;--------------------Configura origen del programa--------------------
    org     0x00			;El origen del programa comienza aquí si hay un reset. 
    goto    INICIO			;Salva el vector de interrupción. 
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
    movlw   0x06
    movwf   ADCON1
    
    movlw   0xFF
    movwf   TRISA
    
    movlw   0x00
    movwf   TRISB
        
    movlw   0xB8
    movwf   OPTION_REG		 
    
;--------------------Selecciona el banco 0--------------------
    bcf	    STATUS, RP1
    bcf	    STATUS, RP0
 
;--------------------Empieza el programa--------------------
    clrf    TMR0
    
    CICLO
    movf    TMR0, W
    movwf   PORTB
    goto    CICLO
    
      
;||||||||||||||||||||Zona de Subrutinas||||||||||||||||||||
 

   
;--------------------Subrutina de Retardo--------------------       
RETARDO_65
    movlw   0x02
    movwf   TMR0
ESPERA					;Polling que espera el overflow de la bandera. 
    btfss   INTCON, TMR0IF		;Timer TMR0IF = 1
    goto    ESPERA
    bcf	    INTCON, TMR0IF
    return
;--------------------Subrutina de Retardo--------------------
    

    
;||||||||||||||||||||Termino de Subrutinas||||||||||||||||||||
    end