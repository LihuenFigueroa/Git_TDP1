#ifndef _USB_H

#define _USB_H
#include "comm.h"


uint8_t USB_Flag();
void    USB_GetBuffer     (uint8_t buffer[SIZE_BUFFER] );
void    USB_Init		  (estado_t state, uint32_t baudRate );
void    USB_Write         (uint8_t *data );
#endif
