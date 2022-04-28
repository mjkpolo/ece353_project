/*
 * main.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#ifndef MAIN_H_
#define MAIN_H_


/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <stdint.h>
#include <stdbool.h>
#include "msp.h"

extern SemaphoreHandle_t Sem_LCD;
extern TaskHandle_t TaskH_TaskBlast;
extern TaskHandle_t TaskH_updateBackground;


#endif /* MAIN_H_ */
