#ifndef eeprom_H_
#define eeprom_H_

#include "sapi.h"
#include "comm.h"

void        EEPROM_SetUSBState      (estado_t estado);
void        EEPROM_SetRS232State    (estado_t estado);
void        EEPROM_SetRS485State    (estado_t estado);
estado_t    EEPROM_GetUSBState      (void);
estado_t    EEPROM_GetRS232State    (void);
estado_t    EEPROM_GetRS485State    (void);
void        EEPROM_SetUSBBaudRate      (uint32_t baudRate);
void        EEPROM_SetRS232BaudRate    (uint32_t baudRate);
void        EEPROM_SetRS485BaudRate    (uint32_t baudRate);
uint32_t    EEPROM_GetUSBBaudRate      (void);
uint32_t    EEPROM_GetRS232BaudRate    (void);
uint32_t    EEPROM_GetRS485BaudRate    (void);

#endif /* eeprom_H_ */
