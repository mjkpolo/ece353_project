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
QueueHandle_t Queue_Score; // TODO include task_blast???

// TODO Header
void Task_background(void* pvParameters)
{
    BaseType_t received_points;
    uint8_t points;
    uint16_t score_val = 0;

    // Draw the score board initially
    draw_xx0(&score);
    draw_x0x(&score);
    draw_0xx(&score);
    draw_end_splash(&score);
    draw_scoreboard(&score);

    while (true) {
        enum light { DARK,
            MEDIUM,
            BRIGHT,
            foo };

        // Check if any points have been received (don't wait if the queue is empty)
        received_points = xQueueReceive(Queue_Score, &points, 0);

        if(received_points == pdPASS) {
            // Increase the score by the number of points received
            score_val += points;

        // TODO Remove: if (score_val!=phits) {
            erase_image(&score);

            switch (score_val%10) {
                case 0 : draw_xx0(&score);
                         break;
                case 1 : draw_xx1(&score);
                         break;
                case 2 : draw_xx2(&score);
                         break;
                case 3 : draw_xx3(&score);
                         break;
                case 4 : draw_xx4(&score);
                         break;
                case 5 : draw_xx5(&score);
                         break;
                case 6 : draw_xx6(&score);
                         break;
                case 7 : draw_xx7(&score);
                         break;
                case 8 : draw_xx8(&score);
                         break;
                case 9 : draw_xx9(&score);
                         break;
            }
            switch ((score_val/10)%10) {
                case 0 : draw_x0x(&score);
                         break;
                case 1 : draw_x1x(&score);
                         break;
                case 2 : draw_x2x(&score);
                         break;
                case 3 : draw_x3x(&score);
                         break;
                case 4 : draw_x4x(&score);
                         break;
                case 5 : draw_x5x(&score);
                         break;
                case 6 : draw_x6x(&score);
                         break;
                case 7 : draw_x7x(&score);
                         break;
                case 8 : draw_x8x(&score);
                         break;
                case 9 : draw_x9x(&score);
                         break;
            }
            switch ((score_val/100)%10) {
                case 0 : draw_0xx(&score);
                         break;
                case 1 : draw_1xx(&score);
                         break;
                case 2 : draw_2xx(&score);
                         break;
                case 3 : draw_3xx(&score);
                         break;
                case 4 : draw_4xx(&score);
                         break;
                case 5 : draw_5xx(&score);
                         break;
                case 6 : draw_6xx(&score);
                         break;
                case 7 : draw_7xx(&score);
                         break;
                case 8 : draw_8xx(&score);
                         break;
                case 9 : draw_9xx(&score);
                         break;
            }

            draw_scoreboard(&score);
        }
        static enum light l, pl = foo; // so pl != l
        float lux = opt3001_read_lux();
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

