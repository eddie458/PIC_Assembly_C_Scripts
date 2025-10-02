;***************************************************************
; Sistemas Digitales II.		11-13.		Marzo 2020.
; Programa #0. Diseñe un programa que encienda el LED 60ms y lo apague 60ms, mostrarlo en el pin RD5.
; Valor a cargar en el timer para 60ms es de .22
; Realizado por Jesus Nunez.  
;*************************************************************** 
    list p=16f877A			;usaremos pic 16f877a 

    include "p16f877A.inc"		;agrega la definición de registros 

;---------- Declarar las variables ---------- 
    Cblock 0x20 
;agregar las variables  
     STATUSTEMP
     WTEMP
     CUENTA
    endc 
;-------------------- palabra de configuración  ------------- 
  __CONFIG _CP_OFF & _DEBUG_OFF & _WRT_OFF & _CPD_OFF & _LVP_OFF & _BODEN_ON & _PWRTE_ON & _WDT_OFF & _HS_OSC 
    radix   hex                         ; usa numeros en hexadecimal 
;-------------------- configura origen del programa  ---------- 
    org      0x00                  ; el origen del programa comienza aquí si hay un reset 
    goto    INICIO               ; salva el vector de interrupción 
    org      0x04
    goto    INTERRUP      ;salta a la rutina de servicio de interrupcion 
    org      0x05                  ; origen del código del programa 
; -------------------- Selecciona el banco 1  ------------------- 
INICIO  
 ;---------------------   selecciona el banco 0   --------------------- 
    bcf STATUS,RP1
    bcf STATUS,RP0
 
  
;---- BANCO 1 -----   
    bsf STATUS,RP0
    bcf STATUS,RP1
;--------------------- Configura registros  ------------------------ 
   movlw 0x06
    movwf ADCON1
   movlw 0x00
    movwf TRISD   ;Puerto A entrada
    movlw 0xC8   
    movwf INTCON  ; configura interrupcion RB4 a RB7
 ;---------------------   selecciona el banco 0   --------------------- 
    bcf STATUS,RP1
    bcf STATUS,RP0
;--------- Empieza el programa ------- 
  clrf CUENTA
  movf CUENTA,W
  movwf PORTD
CICLO
     nop

   goto CICLO  
  
  ; zona de mesages ----
Mensajes
     addwf PCL,F
Mensaje0
     DT "Interrupcion RB4",0x00
Mensaje1
     DT "   ",0x00
FinMensajes
 ;----- zona de interrupción ---
INTERRUP
    movwf WTEMP     ; RESPALDA W 
    movf STATUS,W    ; respalda STATUS
    movwf STATUSTEMP
   ; poner lo que hacer la interrupción 
    call	Retardo_20ms		; Espera a que se estabilice el nivel de tensión.
    btfss	PORTB,RB4			; Comprueba si es un rebote.
    goto	incrementa		; Era un rebote y por tanto sale.
    btfss	PORTB,RB5			; Comprueba si es un rebote.
    goto	incrementa		; Era un rebote y por tanto sale.
    btfss	PORTB,RB6			; Comprueba si es un rebote.
    goto	incrementa			; Era un rebote y por tanto sale.
    btfss	PORTB,RB7			; Comprueba si es un rebote.
    goto	incrementa
    goto  FinInterrupcion		; Era un rebote y por tanto sale.

incrementa	
    
    incf CUENTA,F
    movf CUENTA,W
    call BIN_a_BCD  ; Convierte de binario a BCD 25
    movwf PORTD
EsperaDejePulsar
    btfss	PORTB,RB6		; Para que no interrumpa también en el flanco
    goto	EsperaDejePulsar	; de subida cuando suelte el pulsador.    
FinInterrupcion
    bcf	INTCON,RBIF		; Limpia flag de reconocimiento (INTF).
 			
    movf STATUSTEMP,W
    movwf STATUS
    movf WTEMP,W
    retfie ; Retorna y rehabilita las interrupciones (GIE=1).
 
 ;-- terminan la interrupcion--
 
; --- zona de subrutinas --

 ;--- termina subrutina ---   
 
 ;---- Zona de include---
    include "LCD_4BIT.INC"   
    include "RETARDOS.INC"
    include "BIN_BCD.INC"
    include "LCD_MENS.INC"
    end




