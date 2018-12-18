/*
 * com_MEF.h
 *
 *  Created on: 18/12/2018
 *      Author: Lihuen
 */

#ifndef COM_MEF_H_
#define COM_MEF_H_

typedef enum{
	STATE_SHOW_USB,
	STATE_SHOW_RS232,
	STATE_SHOW_RS485,
	STATE_CONFIG_USB_S,
	STATE_CONFIG_RS232_S,
	STATE_CONFIG_RS485_S,
	STATE_CONFIG_USB_BD,
	STATE_CONFIG_RS232_BD,
	STATE_CONFIG_RS485_BD,
} com_States ;

static com_States state;
static com_States oldState;
static char buffer[32];

static void com_MEF_Init();
static void com_MEF_Update();

#endif /* COM_MEF_H_ */
