/*
 * timer32.h
 *
 *  Created on: Oct 5, 2020
 *      Author: YOUR NAME
 */

#ifndef TIMER32_H_
#define TIMER32_H_

#include "main.h"

extern volatile bool S2_P;
extern volatile bool NEW_FRAME;
void t32_init(void);
bool MKII_S2(void);

#endif /* TIMER32_H_ */
