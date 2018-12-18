#include "comm.h"

void COMM_Init() {
	USB_SetState(EEPROM_GetUSBState());
	RS232_SetState(EEPROM_GetRS232State());
	RS485_SetState(EEPROM_GetRS485State());
	USB_SetBaudRate(EEPROM_GetUSBBaudRate());
	RS232_SetBaudRate(EEPROM_GetRS232BaudRate());
	RS485_SetBaudRate(EEPROM_GetRS485BaudRate());
}

void COMM_CheckSerials() {
	if (USB_Flag()) {
		USB_Buffer(buffer);
		COMM_UsbCheckCommand(buffer);
	}
	if (RS232_Flag()) {
		RS232_Buffer(buffer);
		COMM_RS232CheckCommand(buffer);
	}
	if (RS485_Flag()) {
		RS485_Buffer(buffer);
		COMM_RS485CheckCommand(buffer);
	}
}

void COMM_UsbCheckCommand(uint8_t v[SIZE_BUFFER]) {
	char * p1 = strchr(v, ',');
	*(p1) = '\0';
	if (v == "EUSB") {
		v = ++p1;
		switch (v) {
		case "O":
			USB_SetState(Apagado);
			break;
		case "P":
			USB_SetState(Primario);
			break;
		case "S":
			USB_SetState(Secundario);
			break;
		case "?":
			USB_Write(EEPROM_GetUSBState());
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
void COMM_Rs232CheckCommand(uint8_t v[SIZE_BUFFER]) {
	char * p1 = strchr(v, ',');
	*(p1) = '\0';
	if (v == "E232") {
		v = ++p1;
		switch (v) {
		case "O":
			USB_SetState(Apagado);
			break;
		case "P":
			USB_SetState(Primario);
			break;
		case "S":
			USB_SetState(Secundario);
			break;
		case "?":
			RS232_Write(EEPROM_GetRS232State());
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
void COMM_Rs485CheckCommand(uint8_t v[SIZE_BUFFER]) {
	char * p1 = strchr(v, ',');
	*(p1) = '\0';
	if (v == "E485") {
		v = ++p1;
		switch (v) {
		case "O":
			USB_SetState(Apagado);
			break;
		case "P":
			USB_SetState(Primario);
			break;
		case "S":
			USB_SetState(Secundario);
			break;
		case "?":
			RS485_Write(EEPROM_GetRS485State());
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