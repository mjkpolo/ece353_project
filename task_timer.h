/*
 * task_timer.h
 *
 *  Created on: May 4, 2022
 *      Author: james
 */

#ifndef TASK_TIMER_H_
#define TASK_TIMER_H_

#include "main.h"

// TODO Header
bool MKII_S2(void);
// TODO Header
void Task_timer(void* pvParameters);

extern TaskHandle_t TaskH_timer;

extern SemaphoreHandle_t Sem_Timer;

#endif /* TASK_TIMER_H_ */
