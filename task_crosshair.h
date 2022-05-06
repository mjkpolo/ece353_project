/*
 * task_crosshair.h
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#ifndef TASK_CROSSHAIR_H_
#define TASK_CROSSHAIR_H_

#include "main.h"

// TODO Header
void Task_crosshair(void* pvParameters);
// TODO Header
void Task_drawCrosshair(void* pvParameters);

extern TaskHandle_t TaskH_crosshair;
extern TaskHandle_t TaskH_drawCrosshair;

#endif /* TASK_CROSSHAIR_H_ */
