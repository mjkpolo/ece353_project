/*
 * buzzer.h
 *
 *  Created on: Apr 28, 2022
 *      Author: james
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "main.h"


/********************************************************
 * Sets the PWM period of the Buzzer. The duty cycle
 * will be set to 50%
 *
 * Parameters
 *      ticks_period  :  Period of the PWM pulse
 * Returns
 *      None
 *******************************************************/
void MKII_Buzzer_Init(uint16_t ticks_period);

/********************************************************
 * Turns the Buzzer on
 *
 * Parameters
 *      None
 * Returns
 *      None
 *******************************************************/
void MKII_Buzzer_On(void);

/********************************************************
 * Turns the Buzzer off
 *
 * Parameters
 *      None
 * Returns
 *      None
 *******************************************************/
void MKII_Buzzer_Off(void);


#endif /* BUZZER_H_ */
