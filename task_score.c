/*
 * task_score.c
 *
 *  Created on: May 5, 2022
 *      Author: james
 */

#include "task_score.h"
#include "lcd.h"

TaskHandle_t TaskH_score;
TaskHandle_t TaskH_endGame;

// TODO Header
void Task_score(void* pvParameters) {
    // Draw the score board initially
    draw_xx0(&score);
    draw_x0x(&score);
    draw_0xx(&score);
    draw_scoreboard(&score);

    while(true) {
        // Wait for the task to be notified (when the score has been updated)
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Erase the score
        erase_image(&score);

        // Draw the score numbers based on the score
        switch (SCORE%10) {
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
        switch ((SCORE/10)%10) {
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
        switch ((SCORE/100)%10) {
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

        // Redraw the scoreboard
        draw_scoreboard(&score);

        // TODO replace with actual number of clays (due to the order of updating the score and clays hit in task_blast, this should be 1 less than the number of clays that have to be hit)
        if(CLAYS_HIT > 10) {
            xTaskNotifyGive(TaskH_endGame);
        }
    }
}


