#include "sapi.h"
#include <string.h>
#include "comm.h"
#include "rs232.h"
#include "rs485.h"
#include "usb.h"
#include "eeprom.h"

static uint8_t buffer[SIZE_BUFFER];

void COMM_Init() {
	RS232_Init(EEPROM_GetRS232State(), EEPROM_GetRS232BaudRate());
	RS485_Init(EEPROM_GetRS485State(), EEPROM_GetRS485BaudRate());
	USB_Init(EEPROM_GetUSBState(), EEPROM_GetUSBBaudRate());

}
void write(uint8_t *data) {
	USB_Write(data);
	RS232_Write(data);
	RS485_Write(data);
}

static bool_t string_compare(uint8_t *str1, uint8_t *str2) {
	uint8_t i = 0;
	while ((str1[i] == str2[i]) & (str1[i] != '\0') & (str2[i++] != '\0'))
		;
	return str1[i - 1] == str2[i - 1];
}

static bool_t COMM_CheckCommand(uint8_t *v, uint8_t **param) {
	uint8_t *command = v;
	uint8_t digitos[9] = { 32, 32, 32, 32, 32, 32, 32, 32, 0 };
	uint8_t i = 0;
	uint32_t baud_rate;
	uint8_t * p1 = strchr(v, ',');
	write(command);
	if (p1 != NULL) {
		*(p1) = '\0';
		if (string_compare(v, "EUSB")) {
			v = ++p1;
			switch (v[0]) {
			case 'O':
				EEPROM_SetUSBState(Apagado);
				USB_Init(EEPROM_GetUSBState(), EEPROM_GetUSBBaudRate());
				break;
			case 'P':
				EEPROM_SetUSBState(Primario);
				USB_Init(EEPROM_GetUSBState(), EEPROM_GetUSBBaudRate());
				break;
			case 'S':
				EEPROM_SetUSBState(Secundario);
				USB_Init(EEPROM_GetUSBState(), EEPROM_GetUSBBaudRate());
				break;
			case '?':
				switch (EEPROM_GetUSBState()) {
				case Apagado:
					write("Apagado");
					break;
				case Primario:
					write("Primaria");
					break;
				case Secundario:
					write("Secundaria");
					break;
				}
				break;
			default:
				write("Invalido.");
				BUZZER_Ring();
				break;
			}
		}
		if (string_compare(v, "BRUSB")) {
			v = ++p1;
			if (v[0] == '?') {
				baud_rate = EEPROM_GetUSBBaudRate();
				while (baud_rate != 0) {
					digitos[7 - i] = (baud_rate % 10) + 0x30;
					baud_rate = baud_rate / 10;
					i++;
				}
				write(digitos);
			} else {
				EEPROM_SetUSBBaudRate(atoi(v));
				USB_Init(EEPROM_GetUSBState(), EEPROM_GetUSBBaudRate());
			}
		}
		//______________________________________________________________________________
		if (string_compare(v, "E232")) {
			v = ++p1;
			switch (v[0]) {
			case 'O':
				EEPROM_SetRS232State(Apagado);
				RS232_Init(EEPROM_GetRS232State(), EEPROM_GetRS232BaudRate());
				break;
			case 'P':
				EEPROM_SetRS232State(Primario);
				RS232_Init(EEPROM_GetRS232State(), EEPROM_GetRS232BaudRate());
				break;
			case 'S':
				EEPROM_SetRS232State(Secundario);
				RS232_Init(EEPROM_GetRS232State(), EEPROM_GetRS232BaudRate());
				break;
			case '?':
				switch (EEPROM_GetRS232State()) {
				case Apagado:
					write("Apagado");
					break;
				case Primario:
					write("Primaria");
					break;
				case Secundario:
					write("Secundaria");
					break;
				}
				break;
			default:
				write("Invalido.");
				BUZZER_Ring();
				break;
			}
		}
		if (string_compare(v, "BR232")) {
			v = ++p1;
			if (v[0] == '?') {
				baud_rate = EEPROM_GetRS232BaudRate();
				while (baud_rate != 0) {
					digitos[7 - i] = (baud_rate % 10) + 0x30;
					baud_rate = baud_rate / 10;
					i++;
				}
				write(digitos);
			} else {
				EEPROM_SetRS232BaudRate(atoi(v));
				RS232_Init(EEPROM_GetRS232State(), EEPROM_GetRS232BaudRate());
			}
		}
//_________________________________________________________________________
		if (string_compare(v, "E485")) {
			v = ++p1;
			switch (v[0]) {
			case 'O':
				EEPROM_SetRS485State(Apagado);
				RS485_Init(EEPROM_GetRS485State(), EEPROM_GetRS485BaudRate());
				break;
			case 'P':
				EEPROM_SetRS485State(Primario);
				RS485_Init(EEPROM_GetRS485State(), EEPROM_GetRS485BaudRate());
				break;
			case 'S':
				EEPROM_SetRS485State(Secundario);
				RS485_Init(EEPROM_GetRS485State(), EEPROM_GetRS485BaudRate());
				break;
			case '?':
				switch (EEPROM_GetRS485State()) {
				case Apagado:
					write("Apagado");
					break;
				case Primario:
					write("Primaria");
					break;
				case Secundario:
					write("Secundaria");
					break;
				}
				break;
			default:
				write("Invalido.");
				BUZZER_Ring();
				break;
			}
		}
		if (string_compare(v, "BR485")) {
			v = ++p1;
			if (v[0] == '?') {
				baud_rate = EEPROM_GetRS485BaudRate();
				while (baud_rate != 0) {
					digitos[7 - i] = (baud_rate % 10) + 0x30;
					baud_rate = baud_rate / 10;
					i++;
				}
				write(digitos);
			} else {
				EEPROM_SetRS485BaudRate(atoi(v));
				RS485_Init(EEPROM_GetRS485State(), EEPROM_GetRS485BaudRate());
			}
		}
		if (string_compare(v, "ATEN")) {
			(*param) = ++p1;
			return 1;
		}
	} else {
		write("Invalido.");
		return 0;
	}
	if (!string_compare(command, "EUSB") && !string_compare(command, "BRUSB")
			&& !string_compare(command, "E232")
			&& !string_compare(command, "BR232")
			&& !string_compare(command, "E485")
			&& !string_compare(command, "BR485")
			&& !string_compare(command, "ATEN")) {
		write("Invalido.");
	}
	return 0;
}

uint8_t COMM_CheckSerials(uint8_t **param) {
	if (USB_Flag()) {
		USB_GetBuffer(buffer);
		return COMM_CheckCommand(buffer, param);
	}
	if (RS232_Flag()) {
		RS232_GetBuffer(buffer);
		return COMM_CheckCommand(buffer, param);
	}
	if (RS485_Flag()) {
		RS485_GetBuffer(buffer);
		return COMM_CheckCommand(buffer, param);
	}
	return 0;
}

