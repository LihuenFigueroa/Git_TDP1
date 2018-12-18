/*
 * com_MEF.c
 *
 *  Created on: 18/12/2018
 *      Author: Lihuen
 */

#include "com_MEF.h"

static void fill_lcd_buffer_show_com_usb(char buffer[32]) {
	estado_t USB_estado = EEPROM_GetUSBState();
	uint32_t USB_baud_rate = EEPROM_GetUSBBaudRate();
	int i = 0;
	char digitos[8];
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

static void fill_lcd_buffer_show_com_usb_bd(char buffer[32]) {
	estado_t USB_estado = EEPROM_GetUSBState();
	uint32_t USB_baud_rate = KEYPAD_GetValue();
	int i = 0;
	char digitos[8];
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

static void fill_lcd_buffer_show_com_232(char buffer[32]) {
	estado_t RS232_estado = EEPROM_GetRS232State();
	uint32_t RS232_baud_rate = EEPROM_GetRS232BaudRate();
	int i = 0;
	char digitos[8];
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

static void fill_lcd_buffer_show_com_232_bd(char buffer[32]) {
	estado_t RS232_estado = EEPROM_GetRS232State();
	uint32_t RS232_baud_rate = KEYPAD_GetValue();
	int i = 0;
	char digitos[8];
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

static void fill_lcd_buffer_show_com_485(char buffer[32]) {
	estado_t RS485_estado = EEPROM_GetRS485State();
	uint32_t RS485_baud_rate = EEPROM_GetRS485BaudRate();
	int i = 0;
	char digitos[8];
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

static void fill_lcd_buffer_show_com_485_bd(char buffer[32]) {
	estado_t RS485_estado = EEPROM_GetRS485State();
	uint32_t RS485_baud_rate = KEYPAD_GetValue();
	int i = 0;
	char digitos[8];
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

static void com_MEF_Init() {
	state = STATE_SHOW_USB;
	oldState = STATE_SHOW_USB;
}

static void com_MEF_Update() {
	KEYPAD_Interrupt();
	LCD_Interrupt();
	switch (state) {
	case STATE_SHOW_USB:
		fill_lcd_buffer_show_com_usb(buffer);
		LCD_Write_Buffer(buffer);
		key = KEYPAD_LastKey();
		if (key) {
			switch (key) {
			case 4: // TECLA A, ENTER
				oldState = STATE_SHOW_USB;
				state = STATE_CONFIG_USB_S;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
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
			}
			default:
			//NOP
			break;
		}
		break;
	case STATE_SHOW_RS232:
		fill_lcd_buffer_show_com_232(buffer);
		LCD_Write_Buffer(buffer);
		key = KEYPAD_LastKey();
		if (key) {
			switch (key) {
			case 4: // TECLA A, ENTER
				oldState = STATE_SHOW_RS232;
				state = STATE_CONFIG_RS232_S;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				//oldState no cambiaria...(?)
				break;
			case 13: // TECLA *, VOY A STATE_SHOW_USB
				oldState = STATE_SHOW_RS232;
				state = STATE_SHOW_USB;
				break;
			case 15: // TECLA #, VOY A STATE_SHOW_RS485
				oldState = STATE_SHOW_RS232;
				state = STATE_SHOW_RS485;
				break;
			default: //NOP
				break;
			}

		}
		break;
	case STATE_SHOW_RS485:
		fill_lcd_buffer_show_com_485(buffer);
		LCD_Write_Buffer(buffer);
		key = KEYPAD_LastKey();
		if (key) {
			switch (key) {
			case 4: // TECLA A, ENTER
				oldState = STATE_SHOW_RS485;
				state = STATE_CONFIG_RS485_S;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				//oldState no cambiaria...(?)
				break;
			case 13: // TECLA *, VOY A STATE_SHOW_RS485
				oldState = STATE_SHOW_RS485;
				state = STATE_SHOW_RS232;
				break;
			case 15: // TECLA #, VOY A STATE_SHOW_RS232
				oldState = STATE_SHOW_RS485;
				state = STATE_SHOW_USB;
				break;
			default: //NOP
				break;
			}
		}
		break;
	case STATE_CONFIG_USB_S:
		fill_lcd_buffer_show_com_usb(buffer);
		LCD_pos_xy(14, 0);
		LCD_cursor_blink_on();
		key = KEYPAD_LastKey();
		if (key) {
			switch (key) {
			case 4: // TECLA A, BD CONFIG
				oldState = STATE_CONFIG_USB_S;
				state = STATE_CONFIG_USB_BD;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				break;
			case 1: // SET STATE AS PRIMARY
				EEPROM_SetUSBState(Primario);
				oldState = STATE_CONFIG_USB_S;
				state = STATE_SHOW_USB;
				break;
			case 2: // SET STATE AS SECUNDARY
				EEPROM_SetUSBState(Secundario);
				oldState = STATE_CONFIG_USB_S;
				state = STATE_SHOW_USB;
				break;
			case 3: // SET STATE AS OFF
				EEPROM_SetUSBState(Apagado);
				oldState = STATE_CONFIG_USB_S;
				state = STATE_SHOW_USB;
				break;
			default: // NOP
				break;
			}
		}

		break;
	case STATE_CONFIG_RS232_S:
		fill_lcd_buffer_show_com_232(buffer);
		LCD_pos_xy(14, 0);
		LCD_cursor_blink_on();
		key = KEYPAD_LastKey();
		if (key) {
			switch (key) {
			case 4: // TECLA A, BD CONFIG
				oldState = STATE_CONFIG_RS232_S;
				state = STATE_CONFIG_RS232_BD;
				break;
			case 8: // TECLA B, BACK
				KEYPAD_Buffer_Number_Clear();
				state = oldState;
				break;
			case 1: // SET STATE AS PRIMARY
				EEPROM_SetRS232State(Primario);
				oldState = STATE_CONFIG_RS232_S;
				state = STATE_SHOW_RS232;
				break;
			case 2: // SET STATE AS SECUNDARY
				EEPROM_SetRS232State(Secundario);
				oldState = STATE_CONFIG_RS232_S;
				state = STATE_SHOW_RS232;
				break;
			case 3: // SET STATE AS OFF
				EEPROM_SetRS232State(Apagado);
				oldState = STATE_CONFIG_RS232_S;
				state = STATE_SHOW_RS232;
				break;
			default: // NOP
				break;
			}
			break;
			case STATE_CONFIG_RS485_S:
			fill_lcd_buffer_show_com_485(buffer);
			LCD_pos_xy(14, 0);
			LCD_cursor_blink_on();
			key = KEYPAD_LastKey();
			if (key) {
				switch (key) {
				case 4: // TECLA A, BD CONFIG
					oldState = STATE_CONFIG_RS485_S;
					state = STATE_CONFIG_RS485_BD;
					break;
				case 8: // TECLA B, BACK
					KEYPAD_Buffer_Number_Clear();
					state = oldState;
					break;
				case 1: // SET STATE AS PRIMARY
					EEPROM_SetRS485State(Primario);
					oldState = STATE_CONFIG_RS485_S;
					state = STATE_SHOW_RS485;
					break;
				case 2: // SET STATE AS SECUNDARY
					EEPROM_SetRS485State(Secundario);
					oldState = STATE_CONFIG_RS485_S;
					state = STATE_SHOW_RS485;
					break;
				case 3: // SET STATE AS OFF
					EEPROM_SetRS485State(Apagado);
					oldState = STATE_CONFIG_RS485_S;
					state = STATE_SHOW_RS485;
					break;
				default: // NOP
					break;
				}
			}
			break;
			case STATE_CONFIG_USB_BD:
			fill_lcd_buffer_show_com_usb(buffer);
			LCD_pos_xy(15, 1);
			LCD_cursor_blink_on();
			key = KEYPAD_LastKey();
			if (key) {
				switch (key) {
				case 4: // TECLA A, ENTER
					value = KEYPAD_GetValue();
					EEPROM_SetUSBBaudRate(value);
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
					fill_lcd_buffer_show_com_usb_bd(buffer);
					LCD_Write_Buffer(buffer);
					break;
				}
			}
			break;
			case STATE_CONFIG_RS232_BD:
			fill_lcd_buffer_show_com_232(buffer);
			LCD_pos_xy(15, 1);
			LCD_cursor_blink_on();
			key = KEYPAD_LastKey();
			if (key) {
				switch (key) {
				case 4: // TECLA A, ENTER
					value = KEYPAD_GetValue();
					EEPROM_Set232BaudRate(value);
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
					fill_lcd_buffer_show_com_232_bd(buffer);
					LCD_Write_Buffer(buffer);
					break;
				}
			}
			break;
			case STATE_CONFIG_RS485_BD:
			fill_lcd_buffer_show_com_485(buffer);
			LCD_pos_xy(15, 1);
			LCD_cursor_blink_on();
			key = KEYPAD_LastKey();
			if (key) {
				switch (key) {
				case 4: // TECLA A, ENTER
					value = KEYPAD_GetValue();
					EEPROM_Set485BaudRate(value);
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
					fill_lcd_buffer_show_com_485_bd(buffer);
					LCD_Write_Buffer(buffer);
					break;
				}
			}
			break;
			default:
			break;
		}
	}
}



