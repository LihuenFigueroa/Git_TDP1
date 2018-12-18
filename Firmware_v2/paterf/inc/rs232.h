#ifndef _RS232_H

#define _RS232_H

#include "comm.h"


uint8_t RS232_Flag();
void    RS232_GetBuffer     (uint8_t[SIZE_BUFFER] buffer);
void    RS232_SetState      (estado_t state);
void    RS232_SetBaudRate   (uint8_t baudRate);
void    RS232_Write         (uint8_t[SIZE_BUFFER] data);
#endif