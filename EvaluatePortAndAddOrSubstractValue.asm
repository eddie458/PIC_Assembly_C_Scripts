;***************************************************************
; Sistemas Digitales II.		11-13.		Marzo 2020.
; Programa #0. Dise�ar un programa que evalu� si el bit 2 del puerto C es 1, resta 5, si es cero, suma 5. Mostrar resultados en puerto B.
; Realizado por Jesus Nunez.  
;*************************************************************** 
    list p=16f877A			;Usaremos pic 16f877a. 
    include "p16f877A.inc"		;Agrega la definici�n de registros. 
;--------------------Declarar las variables--------------------
    Cblock 0x20 
	
    endc 
;--------------------Palabra de Configuraci�n-------------------- 
    __CONFIG _CP_OFF & _DEBUG_OFF & _WRT_OFF & _CPD_OFF & _LVP_OFF & _BODEN_ON & _PWRTE_ON & _WDT_OFF & _HS_OSC 
    radix   hex				;Usa numeros en hexadecimal. 
;--------------------Configura origen del programa--------------------
    org     0x00			;El origen del programa comienza aqu� si hay un reset. 
    goto    INICIO			;Salva el vector de interrupci�n. 
    org	    0x05			;Origen del c�digo del programa. 
;--------------------Selecciona el banco 1--------------------
INICIO  
    bsf	    STATUS, RP0
    bcf	    STATUS, RP1

;--------------------Configura registros--------------------
    movlw   0xFF
    movwf   TRISC			;Puerto C es entrada.
    movlw   0x00
    movwf   TRISB			;Puerto B es salida. 
;--------------------Selecciona el banco 0--------------------
    bcf	    STATUS, RP1
    bcf	    STATUS, RP0
 ;--------------------Empieza el programa--------------------
Main
    btfss   PORTC, 2
    goto    Suma5
Resta5
    movlw   0x05    
    subwf   PORTC, W
    movwf   PORTB
    goto    Main
Suma5
    movlw   0x05
    addwf   PORTC, W
    movwf   PORTB
    goto    Main
    
      
;||||||||||||||||||||Zona de Subrutinas||||||||||||||||||||
  
;--------------------Subrutina de Ejemplo--------------------       

;--------------------Subrutina de Ejemplo--------------------
        
;||||||||||||||||||||Termino de Subrutinas||||||||||||||||||||
    end