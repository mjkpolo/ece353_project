/*
 * ps2.h
 *
 *  Created on: Oct 5, 2020
 *      Author: YOUR NAME
 */

#ifndef PS2_H_
#define PS2_H_

#include "main.h"
//#include "task_clayPigeon.h"
//#include "task_crosshair.h"
//#include "task_blast.h"

void adc14_init(void);

#define VOLT_0P6 744
#define VOLT_2P70 3351

#define VOLT_TILT_L  1750
#define VOLT_TILT_R  2250
#define VOLT_TILT_F  2100 //TODO 2000
#define VOLT_TILT_B  1500

typedef enum {LEFT, RIGHT, DOWN, UP, NO_MOVE} MOVE_DIR;

typedef struct {
    MOVE_DIR x;
    MOVE_DIR y;
} MOVE_t;


// TODO remove any unnecessary values
extern volatile uint32_t ACCEL_X;
extern volatile uint32_t ACCEL_Y;

extern volatile uint32_t PS2_X_VAL;
extern volatile uint32_t PS2_Y_VAL;

#endif /* PS2_H_ */
