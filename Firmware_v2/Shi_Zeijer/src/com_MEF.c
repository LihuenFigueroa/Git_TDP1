/*
 * com_MEF.c
 *
 *  Created on: 18/12/2018
 *      Author: Lihuen
 */

#include "com_MEF.h"
#include "comm.h"
#include "eeprom.h"
#include "lcd.h"
#include "keypad.h"

typedef enum {
	STATE_SHOW_USB,
	STATE_SHOW_RS232,
	STATE_SHOW_RS485,
	STATE_CONFIG_USB_S,
	STATE_CONFIG_RS232_S,
	STATE_CONFIG_RS485_S,
	STATE_CONFIG_USB_BD,
	STATE_CONFIG_RS232_BD,
	STATE_CONFIG_RS485_BD,
} com_States;
static estado_t sState;
static com_States oldState;
static com_States state;
static uint8_t data[32];
static void fill_lcd_buffer_show_com_usb(char buffer[32], estado_t USB_estado,uint32_t USB_baud_rate) {
	int i = 0;
	uint8_t digitos[8] = {0,0,0,0,0,0,0,0};
	while (USB_baud_rate != 0) {
		digitos[i] = USB_baud_rate % 10;
		USB_baud_rate = USB_baud_rate / 10;
		i++;
	}

	buffer[0] = ' ';
	buffer[1] = ' ';
	buffer[2] = ' ';
	buffer[3] = ' ';
	buffer[4] = 'U';
	buffer[5] = 'S';
	buffer[6] = 'B';
	buffer[7] = ' ';
	buffer[8] = ' ';
	buffer[9] = ' ';
	buffer[10] = ' ';
	buffer[11] = ':';
	buffer[12] = ' ';
	switch (USB_estado) {
	case Primario:
		buffer[13] = 'P';
		buffer[14] = 'R';
		buffer[15] = 'I';
		break;
	case Secundario:
		buffer[13] = 'S';
		buffer[14] = 'E';
		buffer[15] = 'C';
		break;
	case Apagado:
		buffer[13] = 'O';
		buffer[14] = 'F';
		buffer[15] = 'F';
		break;
	default:
		buffer[13] = 'E';
		buffer[14] = 'R';
		buffer[15] = 'R';
		break;
	}
	buffer[16] = 'B';
	buffer[17] = 'D';
	buffer[18] = ' ';
	buffer[19] = 'R';
	buffer[20] = 'A';
	buffer[21] = 'T';
	buffer[22] = 'E';
	buffer[23] = ' ';
	buffer[24] = digitos[7] + 0x30;
	buffer[25] = digitos[6] + 0x30;
	buffer[26] = digitos[5] + 0x30;
	buffer[27] = digitos[4] + 0x30;
	buffer[28] = digitos[3] + 0x30;
	buffer[29] = digitos[2] + 0x30;
	buffer[30] = digitos[1] + 0x30;
	buffer[31] = digitos[0] + 0x30;
}
static void fill_lcd_buffer_show_com_232(uint8_t buffer[32], estado_t RS232_estado,	uint32_t RS232_baud_rate) {
	int i = 0;
	uint8_t digitos[8] = {0,0,0,0,0,0,0,0};
	while (RS232_baud_rate != 0) {
		digitos[i] = RS232_baud_rate % 10;
		RS232_baud_rate = RS232_baud_rate / 10;
		i++;
	}

	buffer[0] = ' ';
	buffer[1] = ' ';
	buffer[2] = ' ';
	buffer[3] = ' ';
	buffer[4] = 'R';
	buffer[5] = 'S';
	buffer[6] = '2';
	buffer[7] = '3';
	buffer[8] = '2';
	buffer[9] = ' ';
	buffer[10] = ' ';
	buffer[11] = ':';
	buffer[12] = ' ';
	switch (RS232_estado) {
	case Primario:
		buffer[13] = 'P';
		buffer[14] = 'R';
		buffer[15] = 'I';
		break;
	case Secundario:
		buffer[13] = 'S';
		buffer[14] = 'E';
		buffer[15] = 'C';
		break;
	case Apagado:
		buffer[13] = 'O';
		buffer[14] = 'F';
		buffer[15] = 'F';
		break;
	default:
		buffer[13] = 'E';
		buffer[14] = 'R';
		buffer[15] = 'R';
		break;
	}
	buffer[16] = 'B';
	buffer[17] = 'D';
	buffer[18] = ' ';
	buffer[19] = 'R';
	buffer[20] = 'A';
	buffer[21] = 'T';
	buffer[22] = 'E';
	buffer[23] = ' ';
	buffer[24] = digitos[7] + 0x30;
	buffer[25] = digitos[6] + 0x30;
	buffer[26] = digitos[5] + 0x30;
	buffer[27] = digitos[4] + 0x30;
	buffer[28] = digitos[3] + 0x30;
	buffer[29] = digitos[2] + 0x30;
	buffer[30] = digitos[1] + 0x30;
	buffer[31] = digitos[0] + 0x30;
}
static void fill_lcd_buffer_show_com_485(uint8_t buffer[32], estado_t RS485_estado,	uint32_t RS485_baud_rate) {
	int i = 0;
	uint8_t digitos[8] = {0,0,0,0,0,0,0,0};
	while (RS485_baud_rate != 0) {
		digitos[i] = RS485_baud_rate % 10;
		RS485_baud_rate = RS485_baud_rate / 10;
		i++;
	}

	buffer[0] = ' ';
	buffer[1] = ' ';
	buffer[2] = ' ';
	buffer[3] = ' ';
	buffer[4] = 'R';
	buffer[5] = 'S';
	buffer[6] = '4';
	buffer[7] = '8';
	buffer[8] = '5';
	buffer[9] = ' ';
	buffer[10] = ' ';
	buffer[11] = ':';
	buffer[12] = ' ';
	switch (RS485_estado) {
	case Primario:
		buffer[13] = 'P';
		buffer[14] = 'R';
		buffer[15] = 'I';
		break;
	case Secundario:
		buffer[13] = 'S';
		buffer[14] = 'E';
		buffer[15] = 'C';
		break;
	case Apagado:
		buffer[13] = 'O';
		buffer[14] = 'F';
		buffer[15] = 'F';
		break;
	default:
		buffer[13] = 'E';
		buffer[14] = 'R';
		buffer[15] = 'R';
		break;
	}
	buffer[16] = 'B';
	buffer[17] = 'D';
	buffer[18] = ' ';
	buffer[19] = 'R';
	buffer[20] = 'A';
	buffer[21] = 'T';
	buffer[22] = 'E';
	buffer[23] = ' ';
	buffer[24] = digitos[7] + 0x30;
	buffer[25] = digitos[6] + 0x30;
	buffer[26] = digitos[5] + 0x30;
	buffer[27] = digitos[4] + 0x30;
	buffer[28] = digitos[3] + 0x30;
	buffer[29] = digitos[2] + 0x30;
	buffer[30] = digitos[1] + 0x30;
	buffer[31] = digitos[0] + 0x30;
}

void com_MEF_Init() {
	state = STATE_SHOW_USB;
	oldState = STATE_SHOW_USB;
	fill_lcd_buffer_show_com_usb(data,EEPROM_GetUSBState(),EEPROM_GetUSBBaudRate());
	LCD_Write_Buffer(data);
}

void com_MEF_Update(uint16_t key) {
	uint32_t value;
	switch (state) {
	case STATE_SHOW_USB:
		fill_lcd_buffer_show_com_usb(data,EEPROM_GetUSBState(),EEPROM_GetUSBBaudRate());
		LCD_Write_Buffer(data);
		LCD_cursor_blink_off();
		LCD_cursor_off();
		if (key) {
			switch (key) {
			case 4: // TECLA A, ENTER
				oldState = STATE_SHOW_USB;
				state = STATE_CONFIG_USB_S;
				sState = Primario;
				break;
			case 8: // TECLA B, BACK
				oldState = STATE_SHOW_USB;
				state = STATE_CONFIG_USB_BD;
				KEYPAD_Buffer_Number_Clear();
				//oldState no cambiaria...(?)
				break;
			case 13: // TECLA *, VOY A STATE_SHOW_RS485
				oldState = STATE_SHOW_USB;
				state = STATE_SHOW_RS485;
				break;
			case 15: // TECLA #, VOY A STATE_SHOW_RS232
				oldState = STATE_SHOW_USB;
				state = STATE_SHOW_RS232;
				break;

			default:
				//NOP
				break;
			}
		}
		break;
	case STATE_SHOW_RS232:
		fill_lcd_buffer_show_com_232(data,EEPROM_GetRS232State(),EEPROM_GetRS232BaudRate());
		LCD_Write_Buffer(data);
		LCD_cursor_blink_off();
		LCD_cursor_off();
		if (key) {
			switch (key) {
			case 4: // TECLA A, ENTER
				oldState = STATE_SHOW_RS232;
				state = STATE_CONFIG_RS232_S;
				sState = Primario;
				break;
			case 8: // TECLA B, BACK
				oldState = STATE_SHOW_RS232;
				state = STATE_CONFIG_RS232_BD;
				KEYPAD_Buffer_Number_Clear();
				//oldState no cambiaria...(?)
				break;
			case 13: // TECLA *, VOY A STATE_SHOW_RS485
				oldState = STATE_SHOW_RS232;
				state = STATE_SHOW_USB;
				break;
			case 15: // TECLA #, VOY A STATE_SHOW_RS232
				oldState = STATE_SHOW_RS232;
				state = STATE_SHOW_RS485;
				break;

			default:
				//NOP
				break;
			}
		}
		break;
	case STATE_SHOW_RS485:
		fill_lcd_buffer_show_com_485(data,EEPROM_GetRS485State(),EEPROM_GetRS485BaudRate());
		LCD_Write_Buffer(data);
		LCD_cursor_blink_off();
		LCD_cursor_off();
		if (key) {
			switch (key) {
			case 4: // TECLA A, ENTER
				oldState = STATE_SHOW_RS485;
				state = STATE_CONFIG_RS485_S;
				sState = Primario;
				break;
			case 8: // TECLA B, BACK
				oldState = STATE_SHOW_RS485;
				state = STATE_CONFIG_RS485_BD;
				KEYPAD_Buffer_Number_Clear();
				//oldState no cambiaria...(?)
				break;
			case 13: // TECLA *, VOY A STATE_SHOW_RS485
				oldState = STATE_SHOW_RS485;
				state = STATE_SHOW_RS232;
				break;
			case 15: // TECLA #, VOY A STATE_SHOW_RS485
				oldState = STATE_SHOW_RS485;
				state = STATE_SHOW_USB;
				break;

			default:
				//NOP
				break;
			}
		}
		break;
	case STATE_CONFIG_USB_S:
		fill_lcd_buffer_show_com_usb(data,sState,EEPROM_GetUSBBaudRate());
		LCD_Write_Buffer(data);
		LCD_Set_PosCur(13, 0);
		LCD_cursor_blink_on();
		LCD_cursor_on();
		if (key) {
			switch (key) {
			case 4: // TECLA A, BD CONFIG
				EEPROM_SetUSBState(sState);
				USB_Init(EEPROM_GetUSBState(),EEPROM_GetUSBBaudRate());
				state = oldState;
				oldState = STATE_CONFIG_USB_S;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				break;
			case 13: // SET STATE AS PRIMARY
				sState = (sState - 1) % 3;
				if (sState == 255){sState = Apagado;}
				break;
			case 15: // SET STATE AS SECUNDARY
				sState = (sState + 1) % 3;
				break;
			default: // NOP
				break;
			}
		}

		break;
	case STATE_CONFIG_RS232_S:
		fill_lcd_buffer_show_com_232(data,sState,EEPROM_GetRS232BaudRate());
		LCD_Write_Buffer(data);
		LCD_Set_PosCur(13, 0);
		LCD_cursor_blink_on();
		LCD_cursor_on();
		if (key) {
			switch (key) {
			case 4: // TECLA A, BD CONFIG
				EEPROM_SetRS232State(sState);
				RS232_Init(EEPROM_GetRS232State(),EEPROM_GetRS232BaudRate());
				state = oldState;
				oldState = STATE_CONFIG_RS232_S;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				break;
			case 13: // SET STATE AS PRIMARY
				sState = (sState - 1) % 3;
				if (sState == 255){sState = Apagado;}
				break;
			case 15: // SET STATE AS SECUNDARY
				sState = (sState + 1) % 3;
				break;
			default: // NOP
				break;
			}
		}

		break;
	case STATE_CONFIG_RS485_S:
		fill_lcd_buffer_show_com_485(data,sState,EEPROM_GetRS485BaudRate());
		LCD_Write_Buffer(data);
		LCD_Set_PosCur(13, 0);
		LCD_cursor_blink_on();
		LCD_cursor_on();
		if (key) {
			switch (key) {
			case 4: // TECLA A, BD CONFIG
				EEPROM_SetRS485State(sState);
				RS485_Init(EEPROM_GetRS485State(),EEPROM_GetRS485BaudRate());
				state = oldState;
				oldState = STATE_CONFIG_RS485_S;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				break;
			case 13: // SET STATE AS PRIMARY
				sState = (sState - 1) % 3;
				if (sState == 255){sState = Apagado;}
				break;
			case 15: // SET STATE AS SECUNDARY
				sState = (sState + 1) % 3;
				break;
			default: // NOP
				break;
			}
		}

		break;
	case STATE_CONFIG_USB_BD:
		fill_lcd_buffer_show_com_usb(data,EEPROM_GetUSBState(),KEYPAD_GetValue(8));
		LCD_Write_Buffer(data);
		LCD_Set_PosCur(15, 1);
		LCD_cursor_blink_on();
		LCD_cursor_on();
		if (key) {
			switch (key) {
			case 4: // TECLA A, ENTER
				value = KEYPAD_GetValue(8);
				EEPROM_SetUSBBaudRate(value);
				USB_Init(EEPROM_GetUSBState(),EEPROM_GetUSBBaudRate());
				oldState = STATE_CONFIG_USB_BD;
				state = STATE_SHOW_USB;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				break;
			case 12: // NOP
				break;
			case 13: // NOP
				break;
			case 15: // NOP
				break;
			case 16: // NOP
				break;
			default: //CUALQUIER NUMERO XD
				break;
			}
		}
		break;
	case STATE_CONFIG_RS232_BD:
		fill_lcd_buffer_show_com_232(data,EEPROM_GetRS232State(),KEYPAD_GetValue(8));
		LCD_Write_Buffer(data);
		LCD_Set_PosCur(15, 1);
		LCD_cursor_blink_on();
		LCD_cursor_on();
		if (key) {
			switch (key) {
			case 4: // TECLA A, ENTER
				value = KEYPAD_GetValue(8);
				EEPROM_SetRS232BaudRate(value);
				RS232_Init(EEPROM_GetRS232State(),EEPROM_GetRS232BaudRate());
				oldState = STATE_CONFIG_RS232_BD;
				state = STATE_SHOW_RS232;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				break;
			case 12: // NOP
				break;
			case 13: // NOP
				break;
			case 15: // NOP
				break;
			case 16: // NOP
				break;
			default: //CUALQUIER NUMERO XD
				break;
			}
		}
		break;
	case STATE_CONFIG_RS485_BD:
		fill_lcd_buffer_show_com_485(data,EEPROM_GetRS485State(),KEYPAD_GetValue(8));
		LCD_Write_Buffer(data);
		LCD_Set_PosCur(15, 1);
		LCD_cursor_blink_on();
		LCD_cursor_on();
		if (key) {
			switch (key) {
			case 4: // TECLA A, ENTER
				value = KEYPAD_GetValue(8);
				EEPROM_SetRS485BaudRate(value);
				RS485_Init(EEPROM_GetRS485State(),EEPROM_GetRS485BaudRate());
				oldState = STATE_CONFIG_RS485_BD;
				state = STATE_SHOW_RS485;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				break;
			case 12: // NOP
				break;
			case 13: // NOP
				break;
			case 15: // NOP
				break;
			case 16: // NOP
				break;
			default: //CUALQUIER NUMERO XD
				break;
			}
		}
		break;
	default:
		break;
	}
}


