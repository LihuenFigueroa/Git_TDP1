
#include "aten.h"

void Aten_Init(void){
	//poner aten en 1
}

void Aten_Write(uint8_t value){
	if(value & 10000000){

	}
	else{}

	if(value & 01000000){

	}
	else{}

	if(value & 00100000){

	}
	else{}

	if(value & 00010000){

	}
	else{}

	if(value & 00001000){

	}
	else{}

	if(value & 00000100){

	}
	else{}

	if(value & 00000010){

	}
	else{

	}
}


uint8_t Aten_SetValue (uint8_t value){
	if(value>127){
		return 0;
	}else{
		Aten_Write(value);
	}

	return 1;
}

