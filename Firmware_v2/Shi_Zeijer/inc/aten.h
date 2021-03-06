
#ifndef ATEN_H_
#define ATEN_H_

#include "sapi.h"

//REVISAR EL MAPEO DE LOS GPIO

//Escritos en forma de U, de izquierda a derecha

#define ATEN_64 GPIO5
#define ATEN_32 GPIO3
#define ATEN_16 GPIO1
#define ATEN_8 GPIO6
#define ATEN_4 GPIO4
#define ATEN_2 GPIO2
#define ATEN_1 GPIO0


void Aten_Init();
uint8_t Aten_SetValue(uint16_t value);
uint8_t Aten_Plus ();
uint8_t Aten_Minus ();
uint8_t Aten_Get_Actual_Aten(void);

#endif
