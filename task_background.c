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
SemaphoreHandle_t Sem_Background;

// TODO Header
void Task_background(void* pvParameters)
{
    while (true) {
        enum light {
            DARK,
            MEDIUM,
            BRIGHT,
            foo };
        static enum light l, pl = foo; // so pl != l
        float lux = opt3001_read_lux(); // TODO Maybe move this into task_timer and then notify this task (/ use a queue with portMAX_DELAY) if the lighting changed
        if (lux < 20)
            l = DARK;
        else if (lux < 75)
            l = MEDIUM;
        else
            l = BRIGHT;
        if (pl != l) {
            xSemaphoreTake(Sem_Background, portMAX_DELAY);
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
            xSemaphoreGive(Sem_Background);
        }
        pl=l;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

