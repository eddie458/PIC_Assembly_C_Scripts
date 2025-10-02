;*************************************************************** 
;    Sistemas Digitales II     9-11         18 febrero 2021 
; Programa # 2  realizado por LIDIA   
; MANEJO DE timer como contedor de eventos externos
;*************************************************************** 
    list p=16f877A                     ;usaremos pic 16f877a 

    include "p16f877A.inc"        ; agrega la definición de registros 

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
    org       0x04
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
    movlw   0x06
    movwf   ADCON1
    
    movlw   0xFF
    movwf   TRISA
    movlw 0x00
    movwf TRISD   ;Puerto D salida
    movlw 0x90
    movwf INTCON  ; configura interrupcion RB0
    bcf OPTION_REG,INTEDG  ; Activa transición negativa  
    bsf PORTB,RB0  ; RB0 entrada
 ;---------------------   selecciona el banco 0   --------------------- 
    bcf STATUS,RP1
    bcf STATUS,RP0
;--------- Empieza el programa ------- 
    call LCD_Inicializa  ;  es la primera instruccion del programa
    clrf CUENTA
CICLO
    call LCD_Linea1
    movlw Mensaje0
    call LCD_Mensaje
    
    call LCD_Linea2
    movf CUENTA,W
    call BIN_a_BCD  ; Convierte de binario a BCD 25
    call LCD_Byte
     
    call Retardo_200ms
    call LCD_Borra
    call Retardo_200ms
  
  goto CICLO  
  
  ; zona de mesages ----
Mensajes
     addwf PCL,F
Mensaje0
     DT "Interrupcion RB0",0x00
Mensaje1
     DT "   ",0x00
FinMensajes
 ;----- zona de interrupción ---
INTERRUP
    movwf WTEMP     ; RESPALDA W 
    movf STATUS,W    ; respalda STATUS
    movwf STATUSTEMP
   ; poner lo que hacer la interrupción 
  
    incf CUENTA,F
;    call LCD_Linea2
;    movf CUENTA,W
;    call BIN_a_BCD  ; Convierte de binario a BCD 25
;    call LCD_Byte

    bcf INTCON,INTF  ; Borra la bandera
    movf STATUSTEMP,W
    movwf STATUS
    movf WTEMP,W
    retfie
 
 ;-- terminan la interrupcion--
 
; --- zona de subrutinas --

 ;--- termina subrutina ---   
 
 ;---- Zona de include---
    include "LCD_4BIT.INC"   
    include "RETARDOS.INC"
    include "BIN_BCD.INC"
    include "LCD_MENS.INC"
    end



