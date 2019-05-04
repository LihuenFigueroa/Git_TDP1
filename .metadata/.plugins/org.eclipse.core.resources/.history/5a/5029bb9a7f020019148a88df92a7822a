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

/*==================[macros and definitions]=================================*/
typedef enum{
	STATE_WELCOME,STATE_PRINCIPAL,STATE_CONFIG_ATEN,STATE_CONFIG_INTERF_0,
	STATE_CONFIG_INTERF_1,STATE_CONFIG_INTERF_2,STATE_COMMAND_ANALYZE
} States;

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/


static void f_STATE_WELCOME(void);
static void f_STATE_PRINCIPAL(void);
static void f_STATE_CONFIG_ATEN(void);
static void f_STATE_CONFIG_INTERF_0(void);
static void f_STATE_CONFIG_INTERF_1(void);
static void f_STATE_CONFIG_INTERF_2(void);
static void f_STATE_COMMAND_ANALYZE(void);

static void f_OUTPUT_STATE_WELCOME(void);
static void f_OUTPUT_STATE_PRINCIPAL(void);
static void f_OUTPUT_STATE_CONFIG_ATEN(void);
static void f_OUTPUT_STATE_CONFIG_INTERF_0(void);
static void f_OUTPUT_STATE_CONFIG_INTERF_1(void);
static void f_OUTPUT_STATE_CONFIG_INTERF_2(void);
static void f_OUTPUT_STATE_COMMAND_ANALYZE(void);

static void (*MEF[])(void) = { f_STATE_WELCOME,f_STATE_PRINCIPAL,f_STATE_CONFIG_ATEN,
		f_STATE_CONFIG_INTERF_0,f_STATE_CONFIG_INTERF_1,f_STATE_CONFIG_INTERF_2,
		f_STATE_COMMAND_ANALYZE
};

void MEF_Init(void);


void MEF_Update(void) {
	(*MEF[state])();
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

static States state;
static States oldState;

/** @brief used for delay counter */
static uint32_t pausems_count;

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	Board_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
}

static void pausems(uint32_t t)
{
	pausems_count = t;
	while (pausems_count != 0) {
		__WFI();
	}
}

static void func_STATE_WELCOME(void){}
static void f_STATE_PRINCIPAL(void){}
static void f_STATE_CONFIG_ATEN(void){}
static void f_STATE_CONFIG_INTERF_0(void){}
static void f_STATE_CONFIG_INTERF_1(void){}
static void f_STATE_CONFIG_INTERF_2(void){}
static void f_STATE_COMMAND_ANALYZE(void){}

static void f_OUTPUT_STATE_WELCOME(void){}
static void f_OUTPUT_STATE_PRINCIPAL(void){}
static void f_OUTPUT_STATE_CONFIG_ATEN(void){}
static void f_OUTPUT_STATE_CONFIG_INTERF_0(void){}
static void f_OUTPUT_STATE_CONFIG_INTERF_1(void){}
static void f_OUTPUT_STATE_CONFIG_INTERF_2(void){}
static void f_OUTPUT_STATE_COMMAND_ANALYZE(void){}

/*==================[external functions definition]==========================*/

void SysTick_Handler(void)
{
	if(pausems_count > 0) pausems_count--;
}

int main(void)
{
	initHardware();

	while (1)
	{
		//Board_LED_Toggle(LED);
		//pausems(DELAY_MS);
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
