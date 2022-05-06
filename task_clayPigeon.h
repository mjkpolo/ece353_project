/*
 * task_clayPigeon.h
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#ifndef TASK_CLAYPIGEON_H_
#define TASK_CLAYPIGEON_H_

#include "main.h"

// TODO header
void Task_clayPigeon(void *pvParameters);
// TODO header
void Task_accelerometerXBottomHalf(void* pvParameters);

extern TaskHandle_t TaskH_clayPigeon;
extern TaskHandle_t TaskH_accelerometerXBottomHalf;
extern SemaphoreHandle_t Sem_ClayLaunched;


#endif /* TASK_CLAYPIGEON_H_ */
