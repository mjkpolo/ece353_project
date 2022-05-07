/*
 * task_timer.h
 *
 *  Created on: May 4, 2022
 *      Author: james
 */

#ifndef TASK_TIMER_H_
#define TASK_TIMER_H_

#include "main.h"

/******************************************************************************
* Returns the state of S2 on MKII.
* Returns true if S2 is pressed, false if S2 is not pressed.
******************************************************************************/
bool MKII_S2(void);

/******************************************************************************
* Used to start ADC14 conversions and to read/debounce S2 on MKII. When S2 is
* pressed, Task_blast is notified. This task takes and gives the Sem_Timer
* semaphore at the beginning and end of each iteration, respectively, so this
* task can be blocked by another task taking Sem_Timer.
******************************************************************************/
void Task_timer(void* pvParameters);

extern TaskHandle_t TaskH_timer;

extern SemaphoreHandle_t Sem_Timer;

#endif /* TASK_TIMER_H_ */
