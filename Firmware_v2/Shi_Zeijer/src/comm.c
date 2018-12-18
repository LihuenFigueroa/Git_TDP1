#include "sapi.h"
#include <string.h>
#include "comm.h"
#include "rs232.h"
#include "rs485.h"
#include "usb.h"
#include "eeprom.h"

static uint8_t buffer[SIZE_BUFFER];

void COMM_Init() {
	USB_SetState(EEPROM_GetUSBState());
	RS232_SetState(EEPROM_GetRS232State());
	RS485_SetState(EEPROM_GetRS485State());
	USB_SetBaudRate(EEPROM_GetUSBBaudRate());
	RS232_SetBaudRate(EEPROM_GetRS232BaudRate());
	RS485_SetBaudRate(EEPROM_GetRS485BaudRate());
}


void COMM_USBCheckCommand(uint8_t v[SIZE_BUFFER]) {
	char * p1 = strchr(v, ',');
	*(p1) = '\0';
	if (v == "EUSB") {
		v = ++p1;
		switch (v[0]) {
		case 'O':
			USB_SetState(Apagado);
			break;
		case 'P':
			USB_SetState(Primario);
			break;
		case 'S':
			USB_SetState(Secundario);
			break;
		case '?':
			switch (EEPROM_GetUSBState()) {
			case Apagado:
				RS485_Write("Apagado");
				break;
			case Primario:
				RS485_Write("Primaria");
				break;
			case Secundario:
				RS485_Write("Secundaria");
				break;
				break;
			}
		}
		if (v == "BRUSB") {
			v = ++p1;
			USB_Write(v);
			RS232_Write(v);
			RS485_Write(v);
		}
	}
}
void COMM_RS232CheckCommand(uint8_t v[SIZE_BUFFER]) {
	char * p1 = strchr(v, ',');
	*(p1) = '\0';
	if (v == "E232") {
		v = ++p1;
		switch (v[0]) {
		case 'O':
			USB_SetState(Apagado);
			break;
		case 'P':
			USB_SetState(Primario);
			break;
		case 'S':
			USB_SetState(Secundario);
			break;
		case '?':
			switch (EEPROM_GetRS232State()) {
			case Apagado:
				RS485_Write("Apagado");
				break;
			case Primario:
				RS485_Write("Primaria");
				break;
			case Secundario:
				RS485_Write("Secundaria");
				break;
				break;
			}
		}
		if (v == "BR232") {
			v = ++p1;
			USB_Write(v);
			RS232_Write(v);
			RS485_Write(v);
		}
	}
}

void COMM_RS485CheckCommand(uint8_t v[SIZE_BUFFER]) {
	char * p1 = strchr(v, ',');
	*(p1) = '\0';
	if (v == "E485") {
		v = ++p1;
		switch (v[0]) {
		case 'O':
			USB_SetState(Apagado);
			break;
		case 'P':
			USB_SetState(Primario);
			break;
		case 'S':
			USB_SetState(Secundario);
			break;
		case '?':
			switch (EEPROM_GetRS485State()) {
			case Apagado:
				RS485_Write("Apagado");
				break;
			case Primario:
				RS485_Write("Primaria");
				break;
			case Secundario:
				RS485_Write("Secundaria");
				break;
			}

			break;
		}
	}
	if (v == "BR485") {
		v = ++p1;
		USB_Write(v);
		RS232_Write(v);
		RS485_Write(v);
	}
}

void COMM_CheckSerials() {
	if (USB_Flag()) {
		USB_GetBuffer(buffer);
		COMM_USBCheckCommand(buffer);
	}
	if (RS232_Flag()) {
		RS232_GetBuffer(buffer);
		COMM_RS232CheckCommand(buffer);
	}
	if (RS485_Flag()) {
		RS485_GetBuffer(buffer);
		COMM_RS485CheckCommand(buffer);
	}
}

