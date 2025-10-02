;***************************************************************
; Sistemas Digitales II		11-13		23 Febrero 2020.
; Programa #3. Diseñar un contador descendente modulo 16, cuenta del 15 al 0, y vuelve a empezar. Mostrar los datos en el puerto B.
; Realizado por Jesus Nunez  
;*************************************************************** 
    list p=16f877A			;Usaremos pic 16f877a. 
    include "p16f877A.inc"		;Agrega la definición de registros. 
;--------------------Declarar las variables--------------------
    Cblock 0x20 
	CONTADOR
	VECES
	CASOS
	VAR1
	VAR2
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
    movlw   .16
    movwf   CONTADOR
CICLO
    decfsz  CONTADOR, F			;Decrementar el contador por uno, salta si el resultado es 0. 
    goto    MOSTRAR			;Contador diferente de 0. 
REINICIA				;Contador = 0.
    movf    CONTADOR, W
    movwf   PORTB
    movlw   0x0F			;Asigna un 15 al contador.
    movwf   CONTADOR
MOSTRAR
    movf    CONTADOR, W
    movwf   PORTB
    call    RETARDO
    goto    CICLO
    
        
;||||||||||||||||||||Zona de Subrutinas||||||||||||||||||||
  
;--------------------Subrutina de Retardo--------------------       
RETARDO
    movlw   .255
    movwf   VAR2
ESPV2
    movlw   .255
    movwf   VAR1
ESPERA
    decfsz  VAR1,F			;Decrementa y el resultado lo pone en VAR1.
    goto    ESPERA
    decfsz  VAR2,F
    goto    ESPV2  
    return
;--------------------Subrutina de Retardo--------------------
        
;||||||||||||||||||||Termino de Subrutinas||||||||||||||||||||
    end