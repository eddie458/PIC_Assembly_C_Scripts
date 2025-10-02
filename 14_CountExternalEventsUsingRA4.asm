;***************************************************************
; Sistemas Digitales II.		11-13.		16 Marzo 2020.
; Programa. Hacer un programa para contar eventos externos alimentados por RA4. Que registros se requieren?
; Realizado por Jesus Nunez.  
;*************************************************************** 
    list p=16f877A			;Usaremos pic 16f877a. 
    include "p16f877A.inc"		;Agrega la definición de registros. 
;--------------------Declarar las variables--------------------
    Cblock 0x20 
	Unidades
	Decenas
	Centenas
	
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
        
 		 
    
;--------------------Selecciona el banco 0--------------------
    bcf	    STATUS, RP1
    bcf	    STATUS, RP0
 
;--------------------Empieza el programa--------------------
    call    LCD_Inicializa
    
CICLO
    movlw   'H'
    call    LCD_Caracter
    movlw   'O'
    call    LCD_Caracter
    movlw   'L'
    call    LCD_Caracter
    movlw   'A'
    call    LCD_Caracter
    goto    CICLO
    
      
;||||||||||||||||||||Zona de Subrutinas||||||||||||||||||||
 

   
;--------------------Subrutina Convierte de Binario a BCD--------------------
BIN_BCD
    movwf	Unidades				; Se carga el número binario a convertir.
    clrf	Centenas				; incializa las variables.
    clrf	Decenas					; En principio (Centenas)=0 y (Decenas)=0.
BCD_Resta10
    movlw	.10					; A las unidades se les va restando 10 en 
    subwf	Unidades,W				; cada pasada. (W)=(Unidades)-10.
    btfss	STATUS,C				; ¿(C)=1?, ¿(W) positivo?, ¿(Unidades)>=10?.
    goto 	BIN_BCD_Fin				; No, es menor de 10. Se acabó.
BCD_IncrementaDecenas
    movwf	Unidades				; Recupera lo que queda por restar.
    incf	Decenas,F				; Incrementa las decenas y comprueba si llega 
    movlw	.10					; a 10. Lo hace mediante una resta.
    subwf	Decenas,W				; (W)= (Decenas)-10.
    btfss	STATUS,C				; ¿(C)=1?, ¿(W) positivo?, ¿(Decenas)>=10?.
    goto	BCD_Resta10				; No. Vuelve a dar otra pasada, restándole 10.
BCD_IncrementaCentenas
    clrf	Decenas					; Pone a cero las decenas
    incf	Centenas,F				; e incrementa las centenas.
    goto	BCD_Resta10				; regresa, resta 10 al número a convertir.
BIN_BCD_Fin
    swapf	Decenas,W				; En el nibble alto de W también las decenas.
    addwf	Unidades,W				; Las unidades están en el nibble bajo de W.
    return
;--------------------Subrutina Convierte de Binario a BCD--------------------
    
;--------------------Zona De Includes--------------------
    include "LCD_4BIT.INC"    
    include "RETARDOS.INC"   
;    include "LCD_MENS.incs"  
        
;--------------------Zona De Includes--------------------
    
;||||||||||||||||||||Termino de Subrutinas||||||||||||||||||||
    end