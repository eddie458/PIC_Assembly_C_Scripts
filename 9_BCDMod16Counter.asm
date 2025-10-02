;***************************************************************
; Sistemas Digitales II		11-13		23 Febrero 2020.
; Programa #3. Contador Modulo 16.
; Realizado por Jesus Nunez  
;*************************************************************** 
    list p=16f877A			;Usaremos pic 16f877a. 
    include "p16f877A.inc"		;Agrega la definición de registros. 
;--------------------Declarar las variables--------------------
    Cblock 0x20 
	Centenas
	Decenas
	Unidades
    endc 
;--------------------Palabra de Configuración-------------------- 
  __CONFIG _CP_OFF & _DEBUG_OFF & _WRT_OFF & _CPD_OFF & _LVP_OFF & _BODEN_ON & _PWRTE_ON & _WDT_OFF & _HS_OSC 
    radix   hex				;Usa numeros en hexadecimal. 
NUMERO	EQU	.123
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
    movlw 0x00
    movwf TRISD				;Puerto D es salida.
;--------------------Selecciona el banco 0--------------------
    bcf STATUS, RP1
    bcf STATUS, RP0
 
;--------------------Empieza el programa--------------------
Principal	
;	movlw	NUMERO
	movf	PORTC,W
	call BIN_BCD
	
	movwf	PORTB					; Se visualiza por el puerto de salida.
	movf	Centenas,W
	movwf	PORTD
	goto Principal
;	sleep						; Queda permanentemente en reposo.
	
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
	RETURN
	END						; Fin del programa.
	
							