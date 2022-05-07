/*
 * task_drawScreen.h
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#ifndef TASK_DRAWSCREEN_H_
#define TASK_DRAWSCREEN_H_

#include "main.h"

/* responsible for managing the image queue and sending them to the LCD */
void Task_drawScreen(void* pvParameters);

extern TaskHandle_t TaskH_drawScreen;

extern QueueHandle_t Draw_Queue;

#endif /* TASK_DRAWSCREEN_H_ */
