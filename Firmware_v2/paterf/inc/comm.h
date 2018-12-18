#ifndef COMM_H_
#define COMM_H_




#include "C:\CIAA\Git_TDP1\Firmware_v2\modules\lpc4337_m4\sapi\inc\sapi.h" // NO ME COMPILA LA SAPI

#include "string.h"


#define SIZE_BUFFER 20

enum estado_t { Primario, Secundario, Apagado };

static uint8_t buffer[SIZE_BUFFER];

void COMM_Init();
void COMM_CheckSerials();
void COMM_UsbCheckCommand(uint8_t v[SIZE_BUFFER]);
void COMM_Rs232CheckCommand(uint8_t v[SIZE_BUFFER]);
void COMM_Rs485CheckCommand(uint8_t v[SIZE_BUFFER]);

#endif
