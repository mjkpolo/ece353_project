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

extern TaskHandle_t TaskH_crosshair;

extern QueueHandle_t Queue_PS2;

#endif /* TASK_CROSSHAIR_H_ */
