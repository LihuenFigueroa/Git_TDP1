#include "aten.h"
static uint8_t actualAten;
void Aten_Init() {
	//poner aten en 127
	gpioConfig(ATEN_1, GPIO_OUTPUT);
	gpioConfig(ATEN_2, GPIO_OUTPUT);
	gpioConfig(ATEN_4, GPIO_OUTPUT);
	gpioConfig(ATEN_8, GPIO_OUTPUT);
	gpioConfig(ATEN_16, GPIO_OUTPUT);
	gpioConfig(ATEN_32, GPIO_OUTPUT);
	gpioConfig(ATEN_64, GPIO_OUTPUT);

	Aten_SetValue(127);
}

static void Aten_Write(uint8_t value) {

	actualAten = 0;

//	ACLARACI0N: Nunca "valor" tendra un valor mayor a 127. Esto se asegura en la funcion
//	"Aten_SetValue", justo antes de llamar a "Aten_Write"
//
//	if (valor & 10000000) {
//
//	} else {
//	}

	if (value & 0b1000000) {
		actualAten += 64;
		gpioWrite(ATEN_64, ON);
	} else {
		gpioWrite(ATEN_64, OFF);
	}

	if (value & 0b100000) {
		actualAten += 32;
		gpioWrite(ATEN_32, ON);
	} else {
		gpioWrite(ATEN_32, OFF);
	}

	if (value & 0b10000) {
		actualAten += 16;
		gpioWrite(ATEN_16, ON);
	} else {
		gpioWrite(ATEN_16, OFF);
	}

	if (value & 0b1000) {
		actualAten += 8;
		gpioWrite(ATEN_8, ON);
	} else {
		gpioWrite(ATEN_8, OFF);
	}

	if (value & 0b100) {
		actualAten += 4;
		gpioWrite(ATEN_4, ON);
	} else {
		gpioWrite(ATEN_4, OFF);
	}

	if (value & 0b10) {
		actualAten += 2;
		gpioWrite(ATEN_2, ON);
	} else {
		gpioWrite(ATEN_2, OFF);
	}

	if (value & 0b1) {
		actualAten += 1;
		gpioWrite(ATEN_1, ON);
	} else {
		gpioWrite(ATEN_1, OFF);
	}
}

uint8_t Aten_SetValue(uint16_t value) {
	if ((value > 127) || (value<0)) {
		return 1;
	} else {
		Aten_Write(value);
	}
	return 0;
}

uint8_t Aten_Plus (){
	return Aten_SetValue(actualAten+1);
}
uint8_t Aten_Minus (){
	return Aten_SetValue(actualAten-1);
}

uint8_t Aten_Get_Actual_Aten(void){
	return actualAten;
}

void Aten_Get_Actual_Aten_String(uint8_t * rta){
	uint8_t aux = actualAten;
	uint8_t i = 0;
	while (aux != 0) {
		rta[2 - i] = (aux % 10) + 0x30;
		aux = aux / 10;
		i++;
	}
	rta[3] = '\0';
}
