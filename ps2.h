/*
 * ps2.h
 *
 *  Created on: Oct 5, 2020
 *      Author: YOUR NAME
 */

#ifndef PS2_H_
#define PS2_H_

#include "main.h"
#include "task_clayPigeon.h"
#include "task_crosshair.h"

void adc14_init(void);

#define VOLT_0P6 744
#define VOLT_2P70 3351
/*
#define PS2_DIR_NONE 0
#define PS2_DIR_UP 1
#define PS2_DIR_DOWN 2
#define PS2_DIR_LEFT 3
#define PS2_DIR_RIGHT 4
*/
#define VOLT_TILT_L  1750
#define VOLT_TILT_R  2250
#define VOLT_TILT_F  2250 //TODO 2000
#define VOLT_TILT_B  1500
/* TODO
#define ACCEL_DIR_NONE 0 // TODO combine this with PS2_DIR_NONE to just have one DIR_NONE constant
#define ACCEL_DIR_LEFT 3 // TODO combine this with PS2_DIR_LEFT to just have one DIR_LEFT constant
#define ACCEL_DIR_RIGHT 4 // TODO combine this with PS2_DIR_RIGHT to just have one DIR_RIGHT constant
*/
typedef enum {LEFT, RIGHT, DOWN, UP, NO_MOVE} MOVE_DIR;

typedef struct {
    MOVE_DIR x;
    MOVE_DIR y;
} MOVE_t;


// TODO remove, or at least make not extern volatile
extern volatile uint32_t ACCEL_X;
extern volatile uint32_t ACCEL_Y;

extern volatile uint32_t PS2_X_VAL;
extern volatile uint32_t PS2_Y_VAL;

#endif /* PS2_H_ */
