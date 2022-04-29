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
#include "main.h"
#include "lcd.h" // TODO Move hardware-related/non-FreeRTOS headers into main.h
#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "opt3001.h"
#include "light_background.h"
#include "medium_background.h"
#include "dark_background.h"
#include "crosshair.h"
#include "ps2.h"
#include "timer32.h"
#include "task_blast.h"

TaskHandle_t TaskH_newFrame = NULL;
SemaphoreHandle_t Sem_LCD;


/* ****************************************************************************
 * This Function initializes the hardware required to blink LED1 on the
 * MSP432 Launchpad TODO
 * ***************************************************************************/
static uint8_t x = 64, y = 64;

inline void init(void)
{
    // TODO P3->DIR &= ~BIT5;
    P5->DIR &= ~BIT1;
    P5->DIR &= ~BIT5;

	Crystalfontz128x128_Init();

    t32_init();
    adc14_init(); // TODO Rename ps2.c/.h to adc14.c/.h
	i2c_init();
	opt3001_init();
}

// TODO Create header and move this to its own task_updateBackground.c file with a corresponding task_updateBackground.h file
void Task_updateBackground(void *pvParameters) {
	while(true) {
	    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
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
                // Draw crosshair so that it doesn't seem to disappear when the background color changes
                draw_crosshair(x,y);
            }
            pl = l;
        vTaskDelay(pdMS_TO_TICKS(10));
	}
}
/******************************************************************************
* Tasked used to blink LED1 on MSP432 Launchpad
* TODO Update header and move this to its own task_newFrame.c file with a corresponding task_newFrame.h file
******************************************************************************/
void Task_newFrame(void *pvParameters)
{
	while(true) {
	    vTaskDelay(pdMS_TO_TICKS(10));
		if (PS2_Y_VAL == PS2_DIR_UP) {
            // Move up unless the crosshair is already at the upper boundary. In which case, stay at the boundary
		    if(y > (CROSSHAIR_HEIGHT / 2) + STEP_VAL) y -= STEP_VAL;
		    else y = 1 + CROSSHAIR_HEIGHT / 2;
		}
		else if (PS2_Y_VAL == PS2_DIR_DOWN) {
            // Move down unless the crosshair is already at the bottom of the sky. In which case, stay at the bottom of the sky
		    if(y < SKY_BOTTOM_Y - (CROSSHAIR_HEIGHT / 2) - STEP_VAL) y += STEP_VAL;
		    else y = SKY_BOTTOM_Y - CROSSHAIR_HEIGHT / 2;
		}
		if (PS2_X_VAL == PS2_DIR_LEFT) {
            // Move to the left unless the crosshair is already at the left boundary. In which case, stay at the boundary
		    if(x > (CROSSHAIR_WIDTH / 2) + STEP_VAL) x -= STEP_VAL;
		    else x = 1 + CROSSHAIR_WIDTH / 2;
		}
		else if ((PS2_X_VAL == PS2_DIR_RIGHT)) {
		    // Move to the right unless the crosshair is already at the right boundary. In which case, stay at the boundary
		    if(x < LCD_HORIZONTAL_MAX - (CROSSHAIR_WIDTH / 2) - STEP_VAL) x += STEP_VAL;
		    else x = LCD_HORIZONTAL_MAX - (CROSSHAIR_WIDTH / 2);
		}
		if ((PS2_Y_VAL != PS2_DIR_NONE) ||
			(PS2_X_VAL != PS2_DIR_NONE)) {
			draw_crosshair(x,y);
		}
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
    xTaskCreate(TaskBlast, "blast", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_TaskBlast);
    xTaskCreate(Task_newFrame, "newFrame", configMINIMAL_STACK_SIZE, NULL, 2, &TaskH_newFrame);
    xTaskCreate(Task_updateBackground, "updateBackground", configMINIMAL_STACK_SIZE, NULL, 2, &TaskH_updateBackground);

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
