/*
 * task_crosshair.c
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#include "task_crosshair.h"
#include "lcd.h"
#include "ps2.h"

TaskHandle_t TaskH_crosshair;
QueueHandle_t Queue_PS2;


// TODO header
void Task_crosshair(void* pvParameters)
{
    BaseType_t status;
    MOVE_t crosshair_move;
    short CROSSHAIR_HEIGHT = crosshair.y1 - crosshair.y0 + 1; // Height of the crosshair image TODO Make constant. If not constant, change to lower case
    short CROSSHAIR_WIDTH = crosshair.x1 - crosshair.x0 + 1; // Width of the crosshair image TODO Make constant. If not constant, change to lower case
    short x = 64, y = 64; // x and y positions of the crosshair

    while (true) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait until task is notified to start

        // Wait until a new x move (including no move) is received from Queue_Accelerometer
        status = xQueueReceive(Queue_PS2, &crosshair_move, portMAX_DELAY);

        // TODO Just use if statements
        switch(crosshair_move.y) {
            case UP:
                if (y > (CROSSHAIR_HEIGHT / 2) + STEP_VAL + 2)
                    y -= STEP_VAL;
                break;
            case DOWN:
                if(y < (SKY_BOTTOM_Y - (CROSSHAIR_HEIGHT / 2) - STEP_VAL - 1))
                    y += STEP_VAL;
                break;
        }
        switch(crosshair_move.x) {
            case LEFT:
                if(x > (CROSSHAIR_WIDTH / 2) + STEP_VAL + 1)
                    x -= STEP_VAL;
                break;
            case RIGHT:
                if(x < (LCD_HORIZONTAL_MAX - (CROSSHAIR_WIDTH / 2) - STEP_VAL - 1))
                    x += STEP_VAL;
                break;
        }

        draw_crosshair(&crosshair, x, y);

        vTaskDelay(pdMS_TO_TICKS(15));
    }
}
