/*
 * task_clayPigeon.h
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#ifndef TASK_CLAYPIGEON_H_
#define TASK_CLAYPIGEON_H_

#include "main.h"

#define CLAY_X_STEP 1

// TODO header
void Task_clayPigeon(void *pvParameters);

extern TaskHandle_t TaskH_clayPigeon;
extern SemaphoreHandle_t Sem_ClayLaunched;
extern QueueHandle_t Queue_Accelerometer;


#endif /* TASK_CLAYPIGEON_H_ */
