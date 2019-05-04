/* Copyright 2016, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of Workspace.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
/** @brief This is a simple blink example.
 */

/** \addtogroup blink Bare-metal blink example
 ** @{ */

/*==================[inclusions]=============================================*/

#include "main.h"
#include "board.h"
#include "sapi.h"
#include "lcd.h"

#define FIN_DE_COMANDO '#'
/*==================[macros and definitions]=================================*/
char dato;
char endComand[]="RECIBI CARACTER FIN DE COMANDO";
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/** @brief hardware initialization function
 *	@return none
 */
static void initHardware(void);

static callBackFuncPtr_t interrupcionUSB(void){
	dato=uartRxRead( UART_USB );
	if(dato==FIN_DE_COMANDO){
		uartTxWrite( UART_USB, 'O' );
		uartTxWrite( UART_USB, 'K' );
	}
	else{
		uartTxWrite( UART_USB, dato );
	}
}

/** @brief delay function
 * @param t desired milliseconds to wait
 */


/*==================[internal data definition]===============================*/

/** @brief used for delay counter */


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();

}

static void llenar_buffer(char buffer[32] , uint16_t keypressed){
	int i;
	for (i = 0; i < 32; i++) {
		if(i==15){
			buffer[i]=keypressed;
		}
		else{
		buffer[i]=0;}
	}
}

/*==================[external functions definition]==========================*/



int main(void)
{
	int var;
	unsigned char buffer[32];
	keypad_t keypad;
	uint16_t keypressed=0;
	gpioMap_t columnas[]={T_FIL3,T_FIL2,T_COL0,T_FIL1};
	gpioMap_t filas[]={CAN_RD,CAN_TD,T_COL1,T_FIL0};
	boardConfig();
	initHardware();
	keypadConfig(&keypad,filas,4,columnas,4);
	LCD_init(DISPLAY_8X5 | _2_LINES, DISPLAY_ON | CURSOR_ON | CURSOR_BLINK);
	LCD_Clear_Buffer();
	uartConfig(UART_USB,9600);
	uartRxInterruptSet(UART_USB, ON );
	uartRxInterruptCallbackSet(UART_USB ,&interrupcionUSB);  // pointer to function
	for(;;){
		while(!keypadRead(&keypad,&keypressed)){
		Board_LED_Toggle(LED);
		delay(500);
		}
		uartTxWrite( UART_USB, keypressed);
		llenar_buffer(buffer,keypressed);
		LCD_Write_Buffer(buffer);
		LCD_Interrupt();
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
