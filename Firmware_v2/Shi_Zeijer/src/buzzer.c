/*
 * buzzer.c
 *
 *  Created on: 18/12/2018
 *      Author: Lihuen
 */

#include "buzzer.h"


void BUZZER_Init(){
	gpioConfig(BUZZER_PIN,GPIO_OUTPUT);
	gpioWrite(BUZZER_PIN,OFF);
}

void BUZZER_Ring(){
	int i;
	for (i = 0; i < 9; i++) {
		gpioWrite(BUZZER_PIN,i%2);
		delay(100);
	}
}

