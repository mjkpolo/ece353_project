/*
 * task_endGame.h
 *
 *  Created on: May 4, 2022
 *      Author: james
 */

#ifndef TASK_ENDGAME_H_
#define TASK_ENDGAME_H_

#include "main.h"

/******************************************************************************
* Returns the state of S1 on MKII.
* Returns true if S1 is pressed, false if S1 is not pressed.
******************************************************************************/
bool MKII_S1(void);

/******************************************************************************
* End of game task/sequence. Draws the end of game splash screen and pauses
* user input from S2 on MKII and ADC14. This task runs until the user presses
* S1 on MKII to reset the game. This task repeatedly notifies Task_background
* so that the background can update whenever the level of light detected by
* the opt3001 light sensor changes.
******************************************************************************/
void Task_endGame(void* pvParameters);

extern TaskHandle_t TaskH_endGame;

#endif /* TASK_ENDGAME_H_ */
