#ifndef _COMM_H
#define _COMM_H

#define SIZE_BUFFER 20
#define FIN_DE_COMANDO '.'
#include "sapi.h"
typedef enum { Primario, Secundario, Apagado } estado_t;

void COMM_Init();
uint8_t COMM_CheckSerials(uint8_t **param) ;

#endif