#ifndef _USB_H

#define _USB_H
#include "comm.h"


uint8_t USB_Flag();
void    USB_GetBuffer     (uint8_t[SIZE_BUFFER] buffer);
void    USB_SetState      (estado_t state);
void    USB_SetBaudRate   (uint8_t baudRate);
void    USB_Write         (uint8_t[SIZE_BUFFER] data);
#endif