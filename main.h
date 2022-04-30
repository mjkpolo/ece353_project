/*
 * main.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#ifndef MAIN_H_
#define MAIN_H_

/* RTOS header files */
#include "msp.h"
#include <FreeRTOS.h>
#include <semphr.h>
#include <stdbool.h>
#include <stdint.h>
#include <task.h>

#define STEP_VAL 1
#define SKY_BOTTOM_Y 95

extern SemaphoreHandle_t Sem_LCD;

extern TaskHandle_t TaskH_TaskBlast;
extern TaskHandle_t TaskH_updateBackground;

/******************************************************************************
* Prints a message to the Console TODO Update header and move to a new file
******************************************************************************/
void Task_newFrame(void *pvParameters);
/******************************************************************************
* Prints a message to the Console TODO Update header and move to a new file
******************************************************************************/
void Task_updateBackground(void *pvParameters);
/******************************************************************************
* Prints a message to the Console TODO Update header and move to a new file
******************************************************************************/
void Task_clayPigeon(void *pvParameters);


#endif /* MAIN_H_ */
