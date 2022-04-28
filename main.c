/*
 * Copyright (c) 2016-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_freertos.c ========
 */

/* RTOS header files */
#include "serial_debug.h"
#include "main.h"
#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "opt3001.h"
#include "light_background.h"
#include "medium_background.h"
#include "dark_background.h"
#include "lcd.h"
#include "crosshair.h"
#include "ps2.h"
#include "timer32.h"

TaskHandle_t TaskH_joystick = NULL;
TaskHandle_t TaskH_newFrame = NULL;
SemaphoreHandle_t Sem_LCD = NULL;


/* ****************************************************************************
 * This Function initializes the hardware required to blink LED1 on the
 * MSP432 Launchpad
 * ***************************************************************************/
static uint8_t x = 64, y = 64;

inline void init(void)
{
    P5->DIR &= ~BIT1;
    P5->DIR &= ~BIT5;

	  Crystalfontz128x128_Init();

    t32_init();
    adc14_init();
	  i2c_init();
	  opt3001_init();
	  serial_debug_init();
}

/******************************************************************************
* Tasked used to blink LED1 on MSP432 Launchpad
******************************************************************************/
void Task_newFrame(void *pvParameters)
{
	while(true) {
    enum light {DARK,MEDIUM,BRIGHT,foo};
    static enum light l, pl = foo; // so pl != l
	  float lux = opt3001_read_lux();
		if (lux < 20) l=DARK;
		else if (lux < 75) l=MEDIUM;
		else l=BRIGHT;
		if (pl != l) {
			switch (l) {
			  case BRIGHT :
					draw_light_background();
					break;
			  case MEDIUM :
					draw_medium_background();
					break;
			  case DARK :
					draw_dark_background();
					break;
			}
		}
		pl = l;
    vTaskDelay(pdMS_TO_TICKS(10));
		draw_crosshair(x,y);
		draw_moving_layers();
	}
}

void Task_joystick(void *pvParameters) {
	while(true) {
	  if (PS2_Y_VAL == PS2_DIR_UP) y-= 1;
	  else if (PS2_Y_VAL == PS2_DIR_DOWN) y+= 1;
	  if (PS2_X_VAL == PS2_DIR_LEFT) x-= 1;
	  else if (PS2_X_VAL == PS2_DIR_RIGHT) x+= 1;
    vTaskDelay(pdMS_TO_TICKS(5));
	}
}


/*
 *  ======== main ========
 */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    init();

    Sem_LCD = xSemaphoreCreateBinary();
    xSemaphoreGive(Sem_LCD);
    xTaskCreate(Task_newFrame, "newFrame", configMINIMAL_STACK_SIZE, NULL, 1, &TaskH_newFrame);
    xTaskCreate(Task_joystick, "joystick", configMINIMAL_STACK_SIZE, NULL, 2, &TaskH_joystick);

    vTaskStartScheduler();

    while(true);
    return 0;
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
