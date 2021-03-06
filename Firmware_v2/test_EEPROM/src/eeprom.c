/*
 * EEPROM.c

 *
 *  Created on: 17/12/2018
 *      Author: Lihuen
 */

#include "eeprom.h"
#include "chip.h"


void EEPROM_Write(unsigned char page, unsigned char offset, uint32_t data){
	uint32_t * pEEData = (uint32_t *)EEPROM_ADDRESS(page, offset); /* direcci�n de la palabra a escribir */

		Chip_EEPROM_Init(LPC_EEPROM);

	 /* programar la EEPROM */
		Chip_EEPROM_SetAutoProg(LPC_EEPROM, EEPROM_AUTOPROG_AFT_1WORDWRITTEN);

		*pEEData = data;

		Chip_EEPROM_WaitForIntStatus(LPC_EEPROM, EEPROM_INT_ENDOFPROG);
}

/*==================[external functions definition]==========================*/
uint32_t EEPROM_Read(unsigned char page, unsigned char offset){
	uint32_t * pEEData = (uint32_t *)EEPROM_ADDRESS(page, offset); /* direcci�n de la palabra a escribir */

		Chip_EEPROM_Init(LPC_EEPROM);

		return (*pEEData);


}


