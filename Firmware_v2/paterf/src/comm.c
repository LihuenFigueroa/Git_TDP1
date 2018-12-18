#include "comm.h"

void COMM_CheckSerials() {
	if (USB_Flag()) {
		USB_Buffer(buffer);
		COMM_UsbCheckCommand();
	}
	if (RS232_Flag()) {
		RS232_Buffer(buffer);
		COMM_RS232CheckCommand();
	}
	if (RS485_Flag()) {
		RS485_Buffer(buffer);
		COMM_RS485CheckCommand();
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
			//consultar EEPROM
			//consultar EEPROM
			//consultar EEPROM
			//consultar EEPROM
			//consultar EEPROM
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
			//consultar EEPROM
			//consultar EEPROM
			//consultar EEPROM
			//consultar EEPROM
			//consultar EEPROM
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
			//consultar EEPROM
			//consultar EEPROM
			//consultar EEPROM
			//consultar EEPROM
			//consultar EEPROM
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
