#include "rs485.h"
#include "sapi.h"
#define ACTUAL_UART UART_RS485
static uint8_t[SIZE_BUFFER] buffer;
static uint8_t pos = 0;
static uint8_t flag = 0;

static callBackFuncPtr_t interrupcion(void){
	dato=uartRxRead( ACTUAL_UART );
	if(dato==FIN_DE_COMANDO){
		buffer[pos++] = '\0';
        flag = 1;
        pos = 0;
	}
	else{
        if (!flag){
            buffer[pos++] = dato;
        }
	}
}
uint8_t RS485_Flag(){
    return flag;
}
void    RS485_GetBuffer     (uint8_t[SIZE_BUFFER] command){
    for(uint8_t i = 0; i < SIZE_BUFFER; i++)
    {
        command[i] = buffer[i];
    }
    flag = 0;
}
void    RS485_SetState      (estado_t state);
    if (state == Primario)
    {
        uartRxInterruptSet(ACTUAL_UART, ON );
	    uartRxInterruptCallbackSet(ACTUAL_UART ,&interrupcion);  // pointer to function
    }
    else
    {
        uartRxInterruptSet(ACTUAL_UART, OFF );
    }
}
void    RS485_SetBaudRate   (uint8_t baudRate){
    uartConfig(ACTUAL_UART,baudRate);
}
void    RS485_Write         (uint8_t[SIZE_BUFFER] data){
    if (state != Apagado)
    {
        
        for(uint8_t i = 0; (i < SIZE_BUFFER) && data[i] != '\0' ; i++)
        {
            uartTxWrite( ACTUAL_UART, data[i]);
        }
        uartTxWrite( ACTUAL_UART, '\r');
        uartTxWrite( ACTUAL_UART, '\n');
    }
}