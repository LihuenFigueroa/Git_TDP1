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
#include "TimerTicks.h"
#include "main_MEF.h"

#define TICKRATE_1MS	(1)				/* 1000 ticks per second */
#define TICKRATE_MS		20	/* 1000 ticks per second */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
volatile bool SysTick_Time_Flag = false;
/*==================[internal functions declaration]=========================*/

void myTickHook( void *ptr ){
	SysTick_Time_Flag = true;
}
/** @brief hardware initialization function
 *	@return none
 */
static void initHardware(void);

/** @brief delay function
 * @param t desired milliseconds to wait
 */
static void pausems(uint32_t t);

/*==================[internal data definition]===============================*/


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();
}

void myTickHook( void *ptr ){
	main_MEF_Update();
}

int main(void)
{
	boardConfig();
	initHardware();
	/* Init Ticks counter => TICKRATE_MS */
	tickConfig( TICKRATE_MS );
	/* Add Tick Hook */
	tickCallbackSet( myTickHook, (void*)NULL );
	main_MEF_Init();
	for(;;)
	{
		Board_LED_Toggle(LED);
		delay(500);
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
