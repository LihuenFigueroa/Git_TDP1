
#ifndef ATEN_H_
#define ATEN_H_

#include "sapi.h"

//REVISAR EL MAPEO DE LOS GPIO

//Escritos en forma de U, de izquierda a derecha

#define ATEN_64 GPIO0
#define ATEN_32 GPIO2
#define ATEN_16 GPIO4
#define ATEN_8 GPIO6
#define ATEN_4 GPIO1
#define ATEN_2 GPIO3
#define ATEN_1 GPIO5

static uint8_t actualAten;

void Aten_Init();
uint8_t Aten_SetValue (uint8_t value);
uint8_t AtenPlus ();
uint8_t AtenMinus ();

#endif
