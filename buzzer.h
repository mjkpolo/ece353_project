/*
 * buzzer.h
 *
 *  Created on: Apr 28, 2022
 *      Author: james
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "main.h"
#include "math.h"

// TODO Remove unnecessary notes
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
    uint8_t time; // TODO uint8_t ???
}Note_t;


/********************************************************
 * Sets the PWM period of the Buzzer. The duty cycle
 * will be set to 50%
 *
 * Parameters
 *      ticks_period  :  Period of the PWM pulse
 * Returns
 *      None
 *******************************************************/
void MKII_Buzzer_Init(uint16_t ticks_period);

/********************************************************
 * Turns the Buzzer on
 *
 * Parameters
 *      None
 * Returns
 *      None
 *******************************************************/
void MKII_Buzzer_On(void);

/********************************************************
 * Turns the Buzzer off
 *
 * Parameters
 *      None
 * Returns
 *      None
 *******************************************************/
void MKII_Buzzer_Off(void);

// TODO ??? \/\/\/ Remove \/\/\/ ???
/********************************************************
 * Check Buzzer Run Status
 *
 * Parameters
 *      None
 * Returns
 *      true  if TimerA0 is on
 *      false if TimerA0 is off
 *******************************************************/
bool MKII_Buzzer_Run_Status(void);

#endif /* BUZZER_H_ */
