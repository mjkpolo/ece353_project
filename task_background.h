/*
 * task_background.h
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#ifndef TASK_BACKGROUND_H_
#define TASK_BACKGROUND_H_

#include "main.h"

/******************************************************************************
* Draws the background. The background will be drawn as one of three images
* (light_background, medium_background, or dark_background) depending on the
* level of light sensed by the opt3001 light sensor.
******************************************************************************/
void Task_background(void* pvParameters);

extern TaskHandle_t TaskH_background;

#endif
