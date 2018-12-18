



#include "stdint.h"                /* <= Standar Integer data types header */
#include "chip.h"                  /* <= LPCopen header */
#include "sapi.h"
#include "keypad.h"


#define SIZE_BUFFER_IN 3

static uint16_t buffer[SIZE_BUFFER_IN];
static unsigned char newState = 0;
static unsigned char lastState = 0;
static unsigned char bufferRead = 0;
static uint16_t  lastKeyRead = 0;
static keypad_t keypad;
/***********************************************************************
 * Prop�sito de la funci�n: Establece qu� pines ser�n de salida y cu�les de entrada. Activa resistencias de pull-up para los pines de entrada. Pone todos los bits del puerto que controla al keypad en 1.
 ***********************************************************************/
void KEYPAD_Init(void) {
	gpioMap_t columnas[]={T_FIL3,T_FIL2,T_COL0,T_FIL1};
	gpioMap_t filas[]={CAN_RD,CAN_TD,T_COL1,T_FIL0};
	keypadConfig(&keypad,filas,4,columnas,4 );
}

/***********************************************************************
 * Prop�sito de la funci�n: Vaciar contenido del buffer
 * Variables locales y su significado:
 *	Unsigned char i, [0;SIZE_BUFFER_IN -1]. �ndice necesario para estructura for
 ***********************************************************************/
void KEYPAD_Buffer_Clear(void) {
	unsigned char i;
	for (i = 0; i < SIZE_BUFFER_IN - 1; i++) {
		buffer[i]=0;
	}
}
/***********************************************************************
 * Prop�sito de la funci�n: Mover el contenido del buffer interno de lectura al buffer externo indicado.
 * Par�metros de entrada:
 *  	unsigned char outBuffer[SIZE_BUFFER_IN]
 * Variables locales y su significado :
 *	Unsigned char i, [0;SIZE_BUFFER_IN -1]. �ndice necesario para estructura for
 ***********************************************************************/
void KEYPAD_Read_Buffer(uint16_t outBuffer[SIZE_BUFFER_IN]) {
	unsigned char i = 0;
	for (i = 0; i < SIZE_BUFFER_IN; i++) {
		outBuffer[i] = buffer[i];
		buffer[i] = 0;
	}
}


/***********************************************************************
 * Prop�sito de la funci�n: Informa si hay algo nuevo para leer en el buffer de lectura. En caso afirmativo indica qu�.
 * Par�metros de salida (tipo, rango y formato) :
 *	Unsigned char, [0;1]
 ***********************************************************************/
uint16_t KEYPAD_LastKey(void) {
	if (lastKeyRead == 1) {
		lastKeyRead = 0;
		return buffer[SIZE_BUFFER_IN - 1];
	} else {
		return 0;
	}

}
/***********************************************************************
 * Prop�sito de la funci�n: Agrega un valor le�do al buffer de lectura interno
 * Par�metros de entrada::
 * 	Unsigned char, [0,255]
 * Variables locales y su significado:
 *	Unsigned char i, [0;SIZE_BUFFER_IN -1]. �ndice necesario para estructura for
 ***********************************************************************/
static void KEYPAD_Buffer_Write_Key(uint16_t key) {
	unsigned char i;
	for (i = 0; i < SIZE_BUFFER_IN - 1; i++) {
		buffer[i]=buffer[i+1];
	}
	buffer[SIZE_BUFFER_IN - 1] = key;
	bufferRead = 1;
	lastKeyRead = 1;
}


/***********************************************************************
 * Prop�sito de la funci�n: C�digo ejecutado cada vez que se recibe una interrupci�n del RTC. Controla si desde la misma interrupci�n anterior se registr� que dejaron de presionar una tecla. En base a este control pueden presentarse distintas situaciones: 1) Si de una interrupci�n a otra se detect� que se solt� el pulsador, entonces hay que tomar el car�cter actual. 2) Si alg�n pulsador qued� presionado y el valor actual es id�ntico al le�do en la interrupci�n anterior, no hay que tomarlo. 3) Si alg�n pulsador qued� presionado pero el valor actual es distinto al �ltimo le�do, se debe tomar.
 * Variables locales y su significado:
 *	Unsigned char key. Almacena el valor del caracter le�do por el teclado
 ***********************************************************************/

void KEYPAD_Interrupt(void) {
	uint16_t key;
	lastState = newState;
	newState = keypadRead(&key);
	if (newState != 0) {
		if (newState == lastState) {
			if (buffer[SIZE_BUFFER_IN - 1] != key) {
				KEYPAD_Buffer_Write_Key(key);
			}
		} else {
			KEYPAD_Buffer_Write_Key(key);
		}
	}
}



