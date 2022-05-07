/*
 * task_background.c
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#include "task_background.h"
#include "lcd.h"
#include "opt3001.h"

TaskHandle_t TaskH_background;

/******************************************************************************
* Draws the background. The background will be drawn as one of three images
* (light_background, medium_background, or dark_background) depending on the
* level of light sensed by the opt3001 light sensor.
******************************************************************************/
void Task_background(void* pvParameters)
{
    while (true) {
        enum light {
            DARK,
            MEDIUM,
            BRIGHT,
            foo };
        static enum light l, pl = foo; // so pl != l

        // Wait for task to be notified
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        float lux = opt3001_read_lux();

        if (lux < 20)
            l = DARK;
        else if (lux < 75)
            l = MEDIUM;
        else
            l = BRIGHT;

        if (pl != l) {
            erase_image(&background);
            switch (l) {
            case BRIGHT:
                draw_light_background(&background);
                break;
            case MEDIUM:
                draw_medium_background(&background);
                break;
            case DARK:
                draw_dark_background(&background);
                break;
            }
        }

        pl=l;

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

