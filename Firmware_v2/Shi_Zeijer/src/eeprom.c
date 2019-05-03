#include "eeprom.h"
#include "chip.h"

void EEPROM_Write(unsigned char page, unsigned char offset, uint32_t data){
	uint32_t * pEEData = (uint32_t *)EEPROM_ADDRESS(page, offset); /* dirección de la palabra a escribir */

		Chip_EEPROM_Init(LPC_EEPROM);

	 /* programar la EEPROM */
		Chip_EEPROM_SetAutoProg(LPC_EEPROM, EEPROM_AUTOPROG_AFT_1WORDWRITTEN);

		*pEEData = data;

		Chip_EEPROM_WaitForIntStatus(LPC_EEPROM, EEPROM_INT_ENDOFPROG);
}

uint32_t EEPROM_Read(unsigned char page, unsigned char offset){
	uint32_t * pEEData = (uint32_t *)EEPROM_ADDRESS(page, offset); /* dirección de la palabra a escribir */

		Chip_EEPROM_Init(LPC_EEPROM);

		return (*pEEData);


}
void        EEPROM_SetUSBState      (estado_t estado){
    EEPROM_Write(0,0,estado);
}
void        EEPROM_SetRS232State    (estado_t estado){
    EEPROM_Write(0,4,estado);
}
void        EEPROM_SetRS485State    (estado_t estado){
    EEPROM_Write(0,8,estado);
}
estado_t    EEPROM_GetUSBState      (void){
    return EEPROM_Read(0, 0);
}
estado_t    EEPROM_GetRS232State    (void){
    return EEPROM_Read(0, 4);
}
estado_t    EEPROM_GetRS485State    (void){
    return EEPROM_Read(0, 8);
}
void        EEPROM_SetUSBBaudRate      (uint32_t baudRate){
    EEPROM_Write(0,12,baudRate);
}
void        EEPROM_SetRS232BaudRate    (uint32_t baudRate){
    EEPROM_Write(0,16,baudRate);
}   
void        EEPROM_SetRS485BaudRate    (uint32_t baudRate){
    EEPROM_Write(0,20,baudRate);
}
uint32_t    EEPROM_GetUSBBaudRate      (void){
    return EEPROM_Read(0, 12);
}
uint32_t    EEPROM_GetRS232BaudRate    (void){
    return EEPROM_Read(0, 16);
}
uint32_t    EEPROM_GetRS485BaudRate    (void){
    return EEPROM_Read(0, 20);
}
