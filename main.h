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
#define CLAYS_PER_LEVEL 5

extern SemaphoreHandle_t Sem_LCD; // TODO Is this still needed???

// TODO Remove: extern TaskHandle_t TaskH_updateBackground;


#endif /* MAIN_H_ */
