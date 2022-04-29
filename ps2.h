/*
 * ps2.h
 *
 *  Created on: Oct 5, 2020
 *      Author: YOUR NAME
 */

#ifndef PS2_H_
#define PS2_H_
#include "main.h"


void adc14_init(void);
#define VOLT_0P6 744
#define VOLT_2P70 3351

#define PS2_DIR_NONE 0
#define PS2_DIR_UP 1
#define PS2_DIR_DOWN 2
#define PS2_DIR_LEFT 3
#define PS2_DIR_RIGHT 4

#define VOLT_TILT_L  1750
#define VOLT_TILT_R  2250
#define VOLT_TILT_F  2250 //TODO 2000
#define VOLT_TILT_B  1500


extern volatile uint32_t PS2_X_VAL;
extern volatile uint32_t PS2_Y_VAL;


#endif /* PS2_H_ */
