#include "rs232.h"
#include "comm.h"
#include "sapi.h"
#include "eeprom.h"
#define ACTUAL_UART UART_232

static uint8_t buffer[SIZE_BUFFER];
static uint8_t pos = 0;
static uint8_t flag = 0;

static callBackFuncPtr_t interrupcion232(void){
	uint8_t dato;
	dato=uartRxRead( ACTUAL_UART );
	if(dato == FIN_DE_COMANDO){
		buffer[pos++] = '\0';
        flag = 1;
        pos = 0;
	}
	else{
        if (!flag){
            buffer[pos++] = dato;
            if (pos == SIZE_BUFFER)
            {
            	buffer[SIZE_BUFFER-1] = '\0';
            	flag = 1;
            	pos = 0;
            }
        }
	}
}
uint8_t RS232_Flag(){
    return flag;
}

void    RS232_GetBuffer     (uint8_t command[SIZE_BUFFER]){
    for(uint8_t i = 0; i < SIZE_BUFFER; i++)
    {
        command[i] = buffer[i];
    }
    flag = 0;
}
void    RS232_Init		  	(estado_t state, uint32_t baudRate ){
    uartConfig(ACTUAL_UART,baudRate);
    if (state == Primario)
    {
        uartRxInterruptSet(ACTUAL_UART, ON );
	    uartRxInterruptCallbackSet(ACTUAL_UART ,&interrupcion232);  // pointer to function
    }
    else
    {
        uartRxInterruptSet(ACTUAL_UART, OFF );
    }
}

void    RS232_Write         (uint8_t *data){
    if (EEPROM_GetRS232State() != Apagado)
    {
        
        for(uint8_t i = 0; (i < SIZE_BUFFER) && data[i] != '\0' ; i++)
        {
            uartTxWrite( ACTUAL_UART, data[i]);
        }
        uartTxWrite( ACTUAL_UART, '\r');
        uartTxWrite( ACTUAL_UART, '\n');
    }
}
