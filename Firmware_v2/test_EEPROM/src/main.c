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
#include "sapi.h"
#include "eeprom.h"


#define FIN_DE_COMANDO '#'
/*==================[macros and definitions]=================================*/
char dato;
char endComand[]="RECIBI CARACTER FIN DE COMANDO";
int dir_r=0x00;
int dir_wr=0x00;
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/** @brief hardware initialization function
 *	@return none
 */
static void initHardware(void);



static callBackFuncPtr_t interrupcionUSB(void){
	int i=0;
	uint32_t data;
	dato=uartRxRead( UART_USB );
	if(dato==FIN_DE_COMANDO){
		data=EEPROM_Read(0,0);
		uartTxWrite( UART_USB, data );
		uartTxWrite( UART_USB, 'O' );
		uartTxWrite( UART_USB, 'K' );
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

/*==================[external functions definition]==========================*/


int main(void)
{
	int var;
	boardConfig();
	initHardware();
	uartConfig(UART_USB,9600);
	uartRxInterruptSet(UART_USB, ON );
	uartRxInterruptCallbackSet(UART_USB ,&interrupcionUSB);  // pointer to function
	EEPROM_Write(0,4,9600);
	for(;;){
		Board_LED_Toggle(LED);
		delay(500);
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
