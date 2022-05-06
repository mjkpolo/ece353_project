/*
 * task_blast.h
 *
 *  Created on: Apr 28, 2022
 *      Author: james
 */

#ifndef TASK_BLAST_H_
#define TASK_BLAST_H_

#include "main.h"
#include "buzzer.h"


/******************************************************************************
* This task is notified when S2 on MKII is pressed while the clay is in the
* air. It fires at the location of the crosshair, updates the score and number
* of clays hit, and plays one of two sounds on the MKII buzzer depending on
* whether or not the clay was hit (if the crosshair and clay images overlap).
******************************************************************************/
void TaskBlast(void *pvParameters);

extern TaskHandle_t TaskH_TaskBlast;


#endif /* TASK_BLAST_H_ */
