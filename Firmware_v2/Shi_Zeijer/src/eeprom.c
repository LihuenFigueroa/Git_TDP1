#include "eeprom.h"
#include "chip.h"


static void EEPROM_Write(uint8_t page, uint8_t offset, uint32_t data){
	volatile uint32_t * pEEData = (uint32_t *)EEPROM_ADDRESS(page, offset); /* direcci�n de la palabra a escribir */

		Chip_EEPROM_Init(LPC_EEPROM);

	 /* programar la EEPROM */
		Chip_EEPROM_SetAutoProg(LPC_EEPROM, EEPROM_AUTOPROG_AFT_1WORDWRITTEN);

		(*pEEData) = data;

		Chip_EEPROM_WaitForIntStatus(LPC_EEPROM, EEPROM_INT_ENDOFPROG);
}

static uint32_t EEPROM_Read(uint8_t page, uint8_t offset){
	volatile uint32_t * pEEData = (uint32_t *)EEPROM_ADDRESS(page, offset); /* direcci�n de la palabra a escribir */

		Chip_EEPROM_Init(LPC_EEPROM);

		return (*pEEData);

		Chip_EEPROM_WaitForIntStatus(LPC_EEPROM, EEPROM_READ_WAIT_STATE_VAL);
}
void        EEPROM_SetUSBState      (estado_t estado){
    EEPROM_Write(0,0,estado);
}
void        EEPROM_SetRS232State    (estado_t estado){
    EEPROM_Write(0,2,estado);
}
void        EEPROM_SetRS485State    (estado_t estado){
    EEPROM_Write(0,4,estado);
}
estado_t    EEPROM_GetUSBState      (void){
    return EEPROM_Read(0, 0);
}
estado_t    EEPROM_GetRS232State    (void){
    return EEPROM_Read(0, 2);
}
estado_t    EEPROM_GetRS485State    (void){
    return EEPROM_Read(0, 4);
}
void        EEPROM_SetUSBBaudRate      (uint32_t baudRate){
    EEPROM_Write(0,1,baudRate);
}
void        EEPROM_SetRS232BaudRate    (uint32_t baudRate){
    EEPROM_Write(0,3,baudRate);
}   
void        EEPROM_SetRS485BaudRate    (uint32_t baudRate){
    EEPROM_Write(0,5,baudRate);
}
uint32_t    EEPROM_GetUSBBaudRate      (void){
    return EEPROM_Read(0, 1);
}
uint32_t    EEPROM_GetRS232BaudRate    (void){
    return EEPROM_Read(0, 3);
}
uint32_t    EEPROM_GetRS485BaudRate    (void){
    return EEPROM_Read(0, 5);
}
