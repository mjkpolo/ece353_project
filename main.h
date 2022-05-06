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

extern uint8_t CLAYS_HIT;
extern uint16_t SCORE;
extern short crosshair_x, crosshair_y;

extern volatile bool AMMO;

#endif /* MAIN_H_ */
