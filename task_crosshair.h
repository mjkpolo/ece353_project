/*
 * task_crosshair.h
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#ifndef TASK_CROSSHAIR_H_
#define TASK_CROSSHAIR_H_

#include "main.h"

/******************************************************************************
* Bottom Half Task. Examines the ADC data from the joystick on the MKII and
* sets the crosshair's movement directions accordingly
******************************************************************************/
void Task_crosshairBottomHalf(void* pvParameters);

/******************************************************************************
* Updates the x and y positions of the crosshair and draws the crosshair at
* those x and y positions
******************************************************************************/
void Task_drawCrosshair(void* pvParameters);

extern TaskHandle_t TaskH_crosshairBottomHalf;
extern TaskHandle_t TaskH_drawCrosshair;

#endif /* TASK_CROSSHAIR_H_ */
