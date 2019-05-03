/*
 * main_MEF.c

 *  Created on: 18/12/2018
 *      Author: Lihuen
 */

#include "main_MEF.h"
#include "lcd.h"
#include "aten.h"
#include "comm.h"
#include "keypad.h"
#include "buzzer.h"
#include "aten.h"
#include "keypad.h"
#include "com_MEF.h"
#define MAX_ATEN 127
typedef enum{
	STATE_NORMAL,
	STATE_CONFIG_ATEN,
	STATE_CONFIG_COM
} States;
static States state;
static States oldState;
static uint16_t key;
static uint8_t data[32];
static uint32_t value;
static const uint8_t clear[16] = {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};
static void fill_lcd_buffer_normal(uint8_t buffer[16]){
	uint16_t value = Aten_Get_Actual_Aten();
	uint8_t digitos[3] = {0,0,0};
	uint16_t i=0;
	while(value!=0){
		digitos[i]=value % 10;
		value=value /10;
		i++;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	buffer[0] = 'A';
	buffer[1] = 'T';
	buffer[2] = 'E';
	buffer[3] = 'N';
	buffer[4] = 'U';
	buffer[5] = 'A';
	buffer[6] = 'C';
	buffer[7] = 'I';
	buffer[8] = 'O';
	buffer[9] = 'N';
=======
	buffer[0] =	 'A';
	buffer[1] =	 'T';
	buffer[2] =	 'E';
	buffer[3] =	 'N';
	buffer[4] =	 'U';
	buffer[5] =	 'A';
	buffer[6] =	 'C';
	buffer[7] =	 'I';
	buffer[8] =	 'O';
	buffer[9] =  'N';
>>>>>>> parent of 595d1f4... Final Para entregar
	buffer[10] = ' ';
	buffer[11] = ':';
	buffer[12] = ' ';
	buffer[13] = digitos[2]+0x30;
	buffer[14] = digitos[1]+0x30;
	buffer[15] = digitos[0]+0x30;

}
static void fill_lcd_buffer_att(uint8_t buffer[16]){
	uint16_t value = KEYPAD_GetValue(3);
<<<<<<< HEAD
	uint8_t digitos[3] = { 0, 0, 0 };
	uint16_t i = 0;
	while (value != 0) {
=======
typedef enum{
	STATE_NORMAL,
	STATE_CONFIG_ATEN,
	STATE_CONFIG_COM
} States;

static States state;
static States oldState;
static uint16_t key;
static uint8_t data[32];
static uint8_t value;

/*
static void fill_lcd_buffer_normal(uint8_t data[32]){
	uint8_t value = Aten_Get_Actual_Aten();
	char digitos[3];
	int i = 0;
	while(value != 0){
>>>>>>> parent of 9b6704a... AGREGADO MAIN MEF
		digitos[i] = value % 10;
		value = value / 10;
		i++;
	}

<<<<<<< HEAD
	buffer[0] = 'A';
	buffer[1] = 'T';
	buffer[2] = 'E';
	buffer[3] = 'N';
	buffer[4] = 'U';
	buffer[5] = 'A';
	buffer[6] = 'C';
	buffer[7] = 'I';
	buffer[8] = 'O';
	buffer[9] = 'N';
=======
	uint8_t digitos[3] = {0,0,0};
	uint16_t i=0;
	while(value!=0){
		digitos[i]=value % 10;
		value=value /10;
		i++;
	}

	buffer[0] =	 'A';
	buffer[1] =	 'T';
	buffer[2] =	 'E';
	buffer[3] =	 'N';
	buffer[4] =	 'U';
	buffer[5] =	 'A';
	buffer[6] =	 'C';
	buffer[7] =	 'I';
	buffer[8] =	 'O';
	buffer[9] =  'N';
>>>>>>> parent of 595d1f4... Final Para entregar
	buffer[10] = ' ';
	buffer[11] = ':';
	buffer[12] = ' ';
	buffer[13] = digitos[2]+0x30;
	buffer[14] = digitos[1]+0x30;
	buffer[15] = digitos[0]+0x30;

}
<<<<<<< HEAD
static void fill_lcd_buffer_aten_err(uint8_t buffer[16]) {
	uint16_t value = KEYPAD_GetValue(3);
	uint8_t digitos[3] = { 0, 0, 0 };
	uint16_t i = 0;
	while (value != 0) {
		digitos[i] = value % 10;
		value = value / 10;
		i++;
	}
	buffer[0] = ' ';
	buffer[1] = 'A';
	buffer[2] = 'T';
	buffer[3] = 'E';
	buffer[4] = 'N';
	buffer[5] = ' ';
	buffer[6] = 'I';
	buffer[7] = 'N';
	buffer[8] = 'V';
	buffer[9] = 'A';
	buffer[10] = 'L';
	buffer[11] = 'I';
	buffer[12] = 'D';
	buffer[13] = 'A';
	buffer[14] = ' ';
	buffer[15] = ' ';
=======
	data[0] =	 'A';
	data[1] =	 'T';
	data[2] =	 'E';
	data[3] =	 'N';
	data[4] =	 'U';
	data[5] =	 'A';
	data[6] =	 'C';
	data[7] =	 'I';
	data[8] =	 'O';
	data[9] =  'N';
	data[10] = ' ';
	data[11] = ':';
	data[12] = ' ';
	data[13] = digitos[2]+0x30;
	data[14] = digitos[1]+0x30;
	data[15] = digitos[0]+0x30;
	data[16] = ' ';
	data[17] = ' ';
	data[18] = ' ';
	data[19] = ' ';
	data[20] = ' ';
	data[21] = ' ';
	data[22] = ' ';
	data[23] = ' ';
	data[24] = ' ';
	data[25] = ' ';
	data[26] = ' ';
	data[27] = ' ';
	data[28] = ' ';
	data[29] = ' ';
	data[30] = ' ';
	data[31] = ' ';
>>>>>>> parent of 9b6704a... AGREGADO MAIN MEF
=======
static void fill_lcd_buffer_aten_err(uint8_t buffer[16]){
	uint16_t value=KEYPAD_GetValue(3);
	uint8_t digitos[3] = {0,0,0};
		uint16_t i=0;
		while(value!=0){
			digitos[i]=value % 10;
			value=value /10;
			i++;
		}
		buffer[0] = ' ';
		buffer[1] = 'A';
		buffer[2] = 'T';
		buffer[3] = 'E';
		buffer[4] = 'N';
		buffer[5] = ' ';
		buffer[6] = 'I';
		buffer[7] = 'N';
		buffer[8] = 'V';
		buffer[9] = 'A';
		buffer[10] = 'L';
		buffer[11] = 'I';
		buffer[12] = 'D';
		buffer[13] = 'A';
		buffer[14] = ' ';
		buffer[15] = ' ';
>>>>>>> parent of 595d1f4... Final Para entregar
}
*/

<<<<<<< HEAD
<<<<<<< HEAD
void main_MEF_Init() {
=======
void main_MEF_Init(){
>>>>>>> parent of 9b6704a... AGREGADO MAIN MEF
=======
void main_MEF_Init(){
>>>>>>> parent of 595d1f4... Final Para entregar
	///////////////		LCD	- INIT		/////////////////
	LCD_init(DISPLAY_8X5 | _2_LINES, DISPLAY_ON | CURSOR_ON | CURSOR_BLINK);
	LCD_Clear_Buffer();
	/////////////////////////////////////////////////////

	//////////////	COMUNICACION - INIT /////////////////
	COMM_Init();
	/////////////////////////////////////////////////////

	/////////////		KEYPAD	- INIT		/////////////
	KEYPAD_Init();
	/////////////////////////////////////////////////////

	/////////////		ATENUADOR	- INIT		/////////
	Aten_Init();
	/////////////////////////////////////////////////////
<<<<<<< HEAD

	/////////////		BUZZER	- INIT		/////////////
	BUZZER_Init();
	/////////////////////////////////////////////////////
	fill_lcd_buffer_normal(data);
	LCD_Write_Buffer_Line(data,0);
	state=STATE_NORMAL;
	oldState=STATE_NORMAL;
}

<<<<<<< HEAD
void main_MEF_Update() {
	uint8_t *param;
=======
	state=STATE_NORMAL;
	oldState=STATE_NORMAL;
}

void main_MEF_Update(){
>>>>>>> parent of 9b6704a... AGREGADO MAIN MEF
=======
 void main_MEF_Update(){
>>>>>>> parent of 595d1f4... Final Para entregar
	KEYPAD_Interrupt();
	switch(state){
	case STATE_NORMAL:
<<<<<<< HEAD
		LCD_cursor_off();
		LCD_cursor_blink_off();
<<<<<<< HEAD
		key = KEYPAD_LastKey();
		if (key) { // Si se apreto alguna tecla...
			switch (key) {
=======
		//fill_lcd_buffer_normal(data);
		LCD_Write_Buffer(data);
		key=KEYPAD_LastKey();
		if(key){ // Si se apreto alguna tecla...
			switch(key){
>>>>>>> parent of 9b6704a... AGREGADO MAIN MEF
=======
		key=KEYPAD_LastKey();
		if(key){ // Si se apreto alguna tecla...
			switch(key){
>>>>>>> parent of 595d1f4... Final Para entregar
			case 4: // TECLA A, UN +
				AtenPlus();
				fill_lcd_buffer_normal(data);
				LCD_Write_Buffer_Line(data,0);
				break;
			case 8:// TECLA B, UN -
				AtenMinus();
				fill_lcd_buffer_normal(data);
				LCD_Write_Buffer_Line(data,0);
				break;
			case 12:// TECLA C, CONFIG ATENUACION
				oldState=STATE_NORMAL;
				state=STATE_CONFIG_ATEN;
				KEYPAD_Buffer_Number_Clear();
				break;
<<<<<<< HEAD
<<<<<<< HEAD
			case 16: // TECLA D, CONFIG COMUNICACION
				oldState = STATE_NORMAL;
				state = STATE_CONFIG_COM;
=======
			case 16:// TECLA D, CONFIG COMUNICACION
				oldState=STATE_NORMAL;
				state=STATE_CONFIG_COM;
>>>>>>> parent of 595d1f4... Final Para entregar
				com_MEF_Init();
=======
			case 16:// TECLA D, CONFIG COMUNICACION
				oldState=STATE_NORMAL;
				state=STATE_CONFIG_COM;
>>>>>>> parent of 9b6704a... AGREGADO MAIN MEF
				break;
			default:
				oldState=STATE_NORMAL;
				state=STATE_NORMAL;
				break;
			}
		}
<<<<<<< HEAD
<<<<<<< HEAD
		if (COMM_CheckSerials(&param)){
			switch (param[0]) {
				case '+':
					Aten_Plus();
=======
		else{ // Si no se apreto alguna tecla...
			//tengo que escuchar comunicacion
			COMM_CheckSerials();
		}
		break;
	case STATE_CONFIG_ATEN:
		key=KEYPAD_LastKey();
			if(key){ // Si se apreto alguna tecla...
				switch(key){
				case 4: // TECLA A, UN ACEPTAR
					value=KEYPAD_GetValue();
					// debo validarlo primero //
					if(value <= MAX_ATEN){
						Aten_SetValue(value);
						oldState=STATE_CONFIG_ATEN;
						state=STATE_NORMAL;
					}
					else{ // NO ES UN VALOR DE ATENUACION VALIDO
						KEYPAD_Buffer_Number_Clear();
						//fill_lcd_buffer_aten_err(data); // ACA ADENTRO CONVIERTO EN ASCII LOS NUMEROS DEL TECLADO
						LCD_Write_Buffer(data);
						BUZZER_Ring();
						oldState=STATE_CONFIG_ATEN;
						state=STATE_CONFIG_ATEN;
					}
					break;
				case 8:// TECLA B, UN CANCELAR
					KEYPAD_Buffer_Number_Clear();
					oldState=STATE_CONFIG_ATEN;
					state=STATE_NORMAL;
>>>>>>> parent of 9b6704a... AGREGADO MAIN MEF
					break;
				case '-':
					Aten_Minus();
					break;
				default:
					Aten_SetValue(atoi(param));
					break;
<<<<<<< HEAD
=======
				case 15:// TECLA #, NOP
					oldState=STATE_CONFIG_ATEN;
					state=STATE_CONFIG_ATEN;
					break;
				default: // CUALQUIER NUMERO XD
					//fill_lcd_buffer_aten(data); // ACA ADENTRO CONVIERTO EN ASCII LOS NUMEROS DEL TECLADO
					LCD_Write_Buffer(data);
					oldState=STATE_CONFIG_ATEN;
					state=STATE_CONFIG_ATEN;
					break;
				}
>>>>>>> parent of 9b6704a... AGREGADO MAIN MEF
			}
			fill_lcd_buffer_normal(data);
			LCD_Write_Buffer_Line(data, 0);
		}
=======
			COMM_CheckSerials();
>>>>>>> parent of 595d1f4... Final Para entregar
		break;
	case STATE_CONFIG_ATEN:
		fill_lcd_buffer_att(data);
		LCD_Set_PosCur(15,0);
		LCD_cursor_on();
		LCD_cursor_blink_on();
		LCD_Write_Buffer_Line(data,0);
		key=KEYPAD_LastKey();
			if(key){ // Si se apreto alguna tecla...
				LCD_Write_Buffer_Line(clear,1);
				switch(key){
				case 4: // TECLA A, UN ACEPTAR
					value=KEYPAD_GetValue(3);
					// debo validarlo primero //
					if(!Aten_SetValue(value)){
						oldState=STATE_CONFIG_ATEN;
						state=STATE_NORMAL;
						fill_lcd_buffer_normal(data);
						LCD_Write_Buffer_Line(data,0);
					}
					else{ // NO ES UN VALOR DE ATENUACION VALIDO
						fill_lcd_buffer_aten_err(data);
						KEYPAD_Buffer_Number_Clear();
						LCD_Write_Buffer_Line(data,1);
						BUZZER_Ring();
						oldState=STATE_CONFIG_ATEN;
						state=STATE_CONFIG_ATEN;
					}
					break;
				case 8:// TECLA B, UN CANCELAR
					KEYPAD_Buffer_Number_Clear();
					fill_lcd_buffer_normal(data); // ACA ADENTRO CONVIERTO EN ASCII LOS NUMEROS DEL TECLADO
					LCD_Write_Buffer_Line(data,0);
					oldState=STATE_CONFIG_ATEN;
					state=STATE_NORMAL;
					break;
				case 12:// TECLA C, NOP
					KEYPAD_Buffer_Number_Clear();
					oldState=STATE_CONFIG_ATEN;
					state=STATE_CONFIG_ATEN;
					break;
				case 13:// TECLA *, NOP
					oldState=STATE_CONFIG_ATEN;
					state=STATE_CONFIG_ATEN;
					break;
				case 15:// TECLA #, NOP
					oldState=STATE_CONFIG_ATEN;
					state=STATE_CONFIG_ATEN;
					break;
				default: // CUALQUIER NUMERO XD
					fill_lcd_buffer_normal(data); // ACA ADENTRO CONVIERTO EN ASCII LOS NUMEROS DEL TECLADO
					LCD_Write_Buffer_Line(data,1);
					oldState=STATE_CONFIG_ATEN;
					state=STATE_CONFIG_ATEN;
					break;
				}
			}
				COMM_CheckSerials();

		break;

	case STATE_CONFIG_COM:
<<<<<<< HEAD
		key = KEYPAD_LastKey();
		if(key == 16){ // Si me tocaron una tecla Y esa fue la D...
			oldState=STATE_CONFIG_COM;
			state=STATE_NORMAL;
			fill_lcd_buffer_normal(data);
			LCD_Write_Buffer_Line(data,0);
			LCD_Write_Buffer_Line(clear,1);
		}
		else{
			com_MEF_Update(key);
		}
=======

>>>>>>> parent of 9b6704a... AGREGADO MAIN MEF
		break;
	}


}

