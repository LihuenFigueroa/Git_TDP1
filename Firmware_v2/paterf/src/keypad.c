



#include "stdint.h"                /* <= Standar Integer data types header */
#include "chip.h"                  /* <= LPCopen header */
#include "sapi.h"
#include "keypad.h"


#define SIZE_BUFFER_IN 3


static unsigned char buffer[SIZE_BUFFER_IN];
static unsigned char newState = 0;
static unsigned char lastState = 0;
static unsigned char bufferRead = 0;
static unsigned char lastKeyRead = 0;
/***********************************************************************
 * Prop�sito de la funci�n: Establece qu� pines ser�n de salida y cu�les de entrada. Activa resistencias de pull-up para los pines de entrada. Pone todos los bits del puerto que controla al keypad en 1.
 ***********************************************************************/
void KEYPAD_Init(void) {
	//Configuro puerto B Los altos entradas y los bajos salidas
	PTBDD = 0x0F;
	//Configuro puerto B Resistencias de pull up en entradas
	PTBPE = 0xF0;
	//Pongo t o d o   1
	PTBD = 0xFF;

}

/***********************************************************************
 * Prop�sito de la funci�n: Interpretar qu� tecla est� presionada (0-9,A-D), si es que hay alguna y la informa
 * Par�metros de entrada:
 *	Puntero a unsigned char
 * Par�metros de salida (tipo, rango y formato):
 * 	Unsigned char, [0;1]
 * Variables locales y su significado:
 *	Unsigned char i, [0;3]. Indice necesario para estructura for
 *	Unsigned char out []. Arreglo que contiene valores de las posibles salidas
 ***********************************************************************/
static unsigned char KEYPAD_Scan(unsigned char * key) {
	unsigned char i;
	unsigned char out[] = { 0b00001110, 0b00001101, 0b00001011, 0b00000111 };
	for (i = 0; i < 4; i++) {
		PTBD = out[i];
		switch (PTBD) {
			case 0b11101110: (*key) = '1'; return 1;
			case 0b11011110: (*key) = '2'; return 1;
			case 0b10111110: (*key) = '3'; return 1;
			case 0b01111110: (*key) = 'a'; return 1;
			case 0b11101101: (*key) = '4'; return 1;
			case 0b11011101: (*key) = '5'; return 1;
			case 0b10111101: (*key) = '6'; return 1;
			case 0b01111101: (*key) = 'b'; return 1;
			case 0b11101011: (*key) = '7'; return 1;
			case 0b11011011: (*key) = '8'; return 1;
			case 0b10111011: (*key) = '9'; return 1;
			case 0b01111011: (*key) = 'c'; return 1;
			case 0b11100111: (*key) = '*'; return 1;
			case 0b11010111: (*key) = '0'; return 1;
			case 0b10110111: (*key) = '#'; return 1;
			case 0b01110111: (*key) = 'd'; return 1;
		}
	}
	return 0;
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
void KEYPAD_Read_Buffer(unsigned char outBuffer[SIZE_BUFFER_IN]) {
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
unsigned char KEYPAD_LastKey(void) {
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
static void KEYPAD_Buffer_Write_Key(unsigned char key) {
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
	unsigned char key;
	lastState = newState;
	newState = KEYPAD_Scan(&key);
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


