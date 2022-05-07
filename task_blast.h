/*
 * task_blast.h
 *
 *  Created on: Apr 28, 2022
 *      Author: james
 */

#ifndef TASK_BLAST_H_
#define TASK_BLAST_H_

#include "main.h"
#include "math.h"
#include "buzzer.h"

#define NOTE_C  16.35
#define NOTE_CS 17.32
#define NOTE_D  18.35
#define NOTE_DS 19.45
#define NOTE_E  20.6
#define NOTE_F  21.83
#define NOTE_FS 23.12
#define NOTE_G  24.5
#define NOTE_GS 25.96
#define NOTE_A  27.5
#define NOTE_AS 29.14
#define NOTE_B  30.87

typedef struct{
    double note;
    uint8_t octave;
    uint8_t time;
}Note_t;

/******************************************************************************
* This task is notified when S2 on MKII is pressed while the clay is in the
* air. It fires at the location of the crosshair, updates the score and number
* of clays hit, and plays one of two sounds on the MKII buzzer depending on
* whether or not the clay was hit (if the crosshair and clay images overlap).
******************************************************************************/
void TaskBlast(void *pvParameters);

extern TaskHandle_t TaskH_TaskBlast;


#endif /* TASK_BLAST_H_ */
