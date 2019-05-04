#ifndef _COMM_H
#define _COMM_H

#define SIZE_BUFFER 20
#define FIN_DE_COMANDO '.'
#include "sapi.h"
typedef enum { Primario, Secundario, Apagado } estado_t;

void COMM_Init();
void COMM_CheckSerials();
void COMM_UsbCheckCommand(uint8_t v[SIZE_BUFFER]);
void COMM_Rs232CheckCommand(uint8_t v[SIZE_BUFFER]);
void COMM_Rs485CheckCommand(uint8_t v[SIZE_BUFFER]);

#endif
