#ifndef _COMM_H
#define _COMM_H

#include "sapi.h"
#include "string.h"

#define SIZE_BUFFER 20
#define FIN_DE_COMANDO .
enum estado_t { Primario, Secundario, Apagado };

static uint8_t buffer [SIZE_BUFFER];

void COMM_Init();
void COMM_CheckSerials();
void COMM_UsbCheckCommand(uint8_t v[SIZE_BUFFER]);
void COMM_Rs232CheckCommand(uint8_t v[SIZE_BUFFER]);
void COMM_Rs485CheckCommand(uint8_t v[SIZE_BUFFER]);

#endif