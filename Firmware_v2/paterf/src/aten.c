#include "aten.h"

void Aten_Init() {
	//poner aten en 127
	Aten_SetValue(127);
}

uint8_t Aten_SetValue(uint8_t valor) {
	if (valor > 127) {
		return 1;
	} else {
		Aten_Write(valor);
	}
	return 0;
}

void Aten_Write(uint8_t valor) {

	actualAten = 0;

//	ACLARACI0N: Nunca "valor" tendra un valor mayor a 127. Esto se asegura en la funcion
//	"Aten_SetValue", justo antes de llamar a "Aten_Write"
//
//	if (valor & 10000000) {
//
//	} else {
//	}

	if (valor & 01000000) {
		actualAten += 64;
		gpioWrite(ATEN_64, ON);
	} else {
		gpioWrite(ATEN_64, OFF);
	}

	if (valor & 00100000) {
		actualAten += 32;
		gpioWrite(ATEN_32, ON);
	} else {
		gpioWrite(ATEN_32, OFF);
	}

	if (valor & 00010000) {
		actualAten += 16;
		gpioWrite(ATEN_16, ON);
	} else {
		gpioWrite(ATEN_16, OFF);
	}

	if (valor & 00001000) {
		actualAten += 8;
		gpioWrite(ATEN_8, ON);
	} else {
		gpioWrite(ATEN_8, OFF);
	}

	if (valor & 00000100) {
		actualAten += 4;
		gpioWrite(ATEN_4, ON);
	} else {
		gpioWrite(ATEN_4, OFF);
	}

	if (valor & 00000010) {
		actualAten += 2;
		gpioWrite(ATEN_2, ON);
	} else {
		gpioWrite(ATEN_2, OFF);
	}

	if (valor & 00000001) {
		actualAten += 1;
		gpioWrite(ATEN_1, ON);
	} else {
		gpioWrite(ATEN_1, OFF);
	}
}

uint8_t AtenPlus (){
	return Aten_SetValue(actualAten+1);
}
uint8_t AtenMinus (){
	return Aten_SetValue(actualAten-1);
}
