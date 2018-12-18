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
static uint8_t value;

/*
static void fill_lcd_buffer_normal(uint8_t data[32]){
	uint8_t value = Aten_Get_Actual_Aten();
	char digitos[3];
	int i = 0;
	while(value != 0){
		digitos[i] = value % 10;
		value = value / 10;
		i++;
	}

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
}
*/

void main_MEF_Init(){
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
	state=STATE_NORMAL;
	oldState=STATE_NORMAL;
}

void main_MEF_Update(){
	KEYPAD_Interrupt();
	LCD_Interrupt();
	switch(state){
	case STATE_NORMAL:
		//fill_lcd_buffer_normal(data);
		LCD_Write_Buffer(data);
		key=KEYPAD_LastKey();
		if(key){ // Si se apreto alguna tecla...
			switch(key){
			case 4: // TECLA A, UN +
				AtenPlus();
				break;
			case 8:// TECLA B, UN -
				AtenMinus();
				break;
			case 12:// TECLA C, CONFIG ATENUACION
				oldState=STATE_NORMAL;
				state=STATE_CONFIG_ATEN;
				break;
			case 16:// TECLA D, CONFIG COMUNICACION
				oldState=STATE_NORMAL;
				state=STATE_CONFIG_COM;
				break;
			default:
				oldState=STATE_NORMAL;
				state=STATE_NORMAL;
				break;
			}
		}
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
					break;
				case 12:// TECLA C, NOP
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
					//fill_lcd_buffer_aten(data); // ACA ADENTRO CONVIERTO EN ASCII LOS NUMEROS DEL TECLADO
					LCD_Write_Buffer(data);
					oldState=STATE_CONFIG_ATEN;
					state=STATE_CONFIG_ATEN;
					break;
				}
			}
			else{ // Si no se apreto alguna tecla...
				//tengo que escuchar comunicacion
				COMM_CheckSerials();
			}
		break;

	case STATE_CONFIG_COM:

		break;
	}


}

