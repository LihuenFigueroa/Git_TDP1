/*
 * buzzer.h
 *
 *  Created on: 18/12/2018
 *      Author: Lihuen
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "sapi.h"

#define BUZZER_PIN ENET_RXD0

void BUZZER_Init();
void BUZZER_Ring();



#endif /* BUZZER_H_ */
