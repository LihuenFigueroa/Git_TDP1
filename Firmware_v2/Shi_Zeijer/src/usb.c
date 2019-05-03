#include "usb.h"
#include "sapi.h"
#include "comm.h"
#include "eeprom.h"
#define ACTUAL_UART UART_USB
static uint8_t buffer[SIZE_BUFFER] ;
static uint8_t pos = 0;
static uint8_t flag = 0;

static callBackFuncPtr_t interrupcionUSB(void){
	uint8_t dato;
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
uint8_t USB_Flag(){
    return flag;
}
void    USB_GetBuffer     (uint8_t command[SIZE_BUFFER] ){
    for(uint8_t i = 0; i < SIZE_BUFFER; i++)
    {
        command[i] = buffer[i];
    }
    flag = 0;
}
void    USB_SetState      (estado_t state){
    if (state == Primario)
    {
        uartRxInterruptSet(ACTUAL_UART, ON );
	    uartRxInterruptCallbackSet(ACTUAL_UART ,&interrupcionUSB);  // pointer to function
    }
    else
    {
        uartRxInterruptSet(ACTUAL_UART, OFF );
    }
}
void    USB_SetBaudRate   (uint32_t baudRate){
    uartConfig(ACTUAL_UART,baudRate);
}
void    USB_Write         (uint8_t *data ){
    if (EEPROM_GetUSBState() != Apagado)
    {
        
        for(uint8_t i = 0; (i < SIZE_BUFFER) && data[i] != '\0' ; i++)
        {
            uartTxWrite( ACTUAL_UART, data[i]);
        }
        uartTxWrite( ACTUAL_UART, '\r');
        uartTxWrite( ACTUAL_UART, '\n');
    }
}
