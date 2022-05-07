/*
 * task_score.h
 *
 *  Created on: May 5, 2022
 *      Author: james
 */

#ifndef TASK_SCORE_H_
#define TASK_SCORE_H_

#include "main.h"

/******************************************************************************
* When notified, this task draws the score/scoreboard according to the value
* of the global variable SCORE. This task also checks the number of clay
* pigeons that have been hit and notifies Task_endGame if that number is high
* enough to end the game.
******************************************************************************/
void Task_score(void* pvParameters);

extern TaskHandle_t TaskH_score;


#endif /* TASK_SCORE_H_ */
