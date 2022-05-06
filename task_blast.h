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
// TODO Remove???
void play_note(uint32_t period, uint16_t ms_time);

// TODO Header
void TaskBlast(void *pvParameters);

extern TaskHandle_t TaskH_TaskBlast;


#endif /* TASK_BLAST_H_ */
