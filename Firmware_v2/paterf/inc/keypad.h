/*
 * keypad.h
 *
 *  Created on: 13/11/2018
 *      Author: Lihuen
 */

#ifndef _KEYPAD_H

#define _KEYPAD_H

#define SIZE_BUFFER_IN 4

	void KEYPAD_Init(void);
	void KEYPAD_Read_Buffer(uint16_t outBuffer[SIZE_BUFFER_IN]);
	void KEYPAD_Buffer_Clear(void) ;
	void KEYPAD_Interrupt(void);
	uint16_t KEYPAD_LastKey(void);

#endif /* KEYPAD_H_ */
