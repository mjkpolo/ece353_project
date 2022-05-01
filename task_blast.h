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


// TODO Play a note for the given duration
void play_note(uint32_t period, uint16_t ms_time);

/******************************************************************************
* TODO Prints a message to the Console
******************************************************************************/
void TaskBlast(void *pvParameters);

extern QueueHandle_t Queue_Score;
extern QueueHandle_t Queue_Hit;


#endif /* TASK_BLAST_H_ */
