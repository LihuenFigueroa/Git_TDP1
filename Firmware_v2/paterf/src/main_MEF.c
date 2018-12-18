/*
 * main_MEF.c
 *
 *  Created on: 18/12/2018
 *      Author: Lihuen
 */

#include "sapi.h"
#include "board.h"
#include "chip.h"
#include "main_MEF.h"
#include "lcd.h"
#include "comm.h"

#define MAX_ATEN 127

static void configKeypad(keypad_t* keypad){
		uint16_t keypressed=0;
		gpioMap_t columnas[]={T_FIL3,T_FIL2,T_COL0,T_FIL1};
		gpioMap_t filas[]={CAN_RD,CAN_TD,T_COL1,T_FIL0};
		keypadConfig(keypad,filas,4,columnas,4);
}

static void fill_lcd_buffer_normal(char data[32]){
	uint8_t value=Aten_Get_Actual_Aten();
	char digitos[3];
	int i=0;
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
	buffer[10] = ' ';
	buffer[11] = ':';
	buffer[12] = ' ';
	buffer[13] = digitos[2]+0x30;
	buffer[14] = digitos[1]+0x30;
	buffer[15] = digitos[0]+0x30;
	buffer[16] = ' ';
	buffer[17] = ' ';
	buffer[18] = ' ';
	buffer[19] = ' ';
	buffer[20] = ' ';
	buffer[21] = ' ';
	buffer[22] = ' ';
	buffer[23] = ' ';
	buffer[24] = ' ';
	buffer[25] = ' ';
	buffer[26] = ' ';
	buffer[27] = ' ';
	buffer[28] = ' ';
	buffer[29] = ' ';
	buffer[30] = ' ';
	buffer[31] = ' ';
}


static void main_MEF_Init(){
	///////////////		LCD	- INIT		/////////////////
	LCD_init(DISPLAY_8X5 | _2_LINES, DISPLAY_ON | CURSOR_ON | CURSOR_BLINK);
	LCD_Clear_Buffer();
	/////////////////////////////////////////////////////

	//////////////	COMUNICACION - INIT /////////////////
	COMM_Init();
	/////////////////////////////////////////////////////

	/////////////		KEYPAD	- INIT		/////////////
	configKeypad(&keypad);
	/////////////////////////////////////////////////////

	/////////////		ATENUADOR	- INIT		/////////
	Aten_Init();
	/////////////////////////////////////////////////////
	state=STATE_NORMAL;
	oldState=STATE_NORMAL;
}

static void main_MEF_Update(){
	KEYPAD_Interrupt();
	switch(state){
	case STATE_NORMAL:
		fill_lcd_buffer_normal(data);
		LCD_Write_Buffer(data);
		LCD_Interrupt();
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
					if(!value>MAX_ATEN){
						Aten_SetValue(value);
						oldState=STATE_CONFIG_ATEN;
						state=STATE_NORMAL;
					}
					else{ // NO ES UN VALOR DE ATENUACION VALIDO
						KEYPAD_Buffer_Clear();
						fill_lcd_buffer_aten_err(data); // ACA ADENTRO CONVIERTO EN ASCII LOS NUMEROS DEL TECLADO
						LCD_Write_Buffer(data);
						LCD_Interrupt();
						sonarBuzzer();
						oldState=STATE_CONFIG_ATEN;
						state=STATE_CONFIG_ATEN;
					}
					break;
				case 8:// TECLA B, UN CANCELAR
					KEYPAD_Buffer_Clear();
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
					fill_lcd_buffer_aten(data); // ACA ADENTRO CONVIERTO EN ASCII LOS NUMEROS DEL TECLADO
					LCD_Write_Buffer(data);
					LCD_Interrupt();
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

