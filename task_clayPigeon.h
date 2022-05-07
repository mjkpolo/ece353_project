/*
 * task_clayPigeon.h
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#ifndef TASK_CLAYPIGEON_H_
#define TASK_CLAYPIGEON_H_

#include "main.h"

/******************************************************************************
* Draws the clay pigeon to move from one side of the screen to the other. It
* also takes care of filling ammo initially and notifying the task to update
* the background after the clay pigeon is hit, leaves the screen, or hits the
* ground.
******************************************************************************/
void Task_clayPigeon(void *pvParameters);

/******************************************************************************
* Bottom Half Task. Examines the accelerometer x value and sets the clay's x
* direction movement (more specifically, which way to adjust its x movement
* towards) accordingly
******************************************************************************/
void Task_accelerometerXBottomHalf(void* pvParameters);

extern TaskHandle_t TaskH_clayPigeon;
extern TaskHandle_t TaskH_accelerometerXBottomHalf;
extern SemaphoreHandle_t Sem_ClayLaunched;


#endif /* TASK_CLAYPIGEON_H_ */
