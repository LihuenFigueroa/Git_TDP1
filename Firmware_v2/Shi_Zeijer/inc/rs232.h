#ifndef _RS232_H_

#define _RS232_H_

#include "comm.h"

uint8_t RS232_Flag();
void    RS232_GetBuffer     (uint8_t buffer[SIZE_BUFFER]);
void    RS232_SetState      (estado_t state);
void    RS232_SetBaudRate   (uint32_t baudRate);
void    RS232_Write         (uint8_t *data);

#endif
