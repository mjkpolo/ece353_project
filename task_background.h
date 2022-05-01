/*
 * task_background.h
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#ifndef TASK_BACKGROUND_H_
#define TASK_BACKGROUND_H_

#include "main.h"

// TODO Header
void Task_background(void* pvParameters);

extern TaskHandle_t TaskH_background;
extern SemaphoreHandle_t Sem_Background;

#endif
