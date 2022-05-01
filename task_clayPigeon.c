/*
 * task_clayPigeon.c
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#include "task_clayPigeon.h"
#include "lcd.h"
#include "ps2.h"


TaskHandle_t TaskH_clayPigeon;
QueueHandle_t Queue_Accelerometer;

//image pidgeon; // TODO

// TODO Header
void Task_clayPigeon(void *pvParameters)
{
    bool move_up; // Boolean used to track whether the clay pigeon should move up or down (ascending or descending)
    short CLAY_HEIGHT = pidgeon.y1 - pidgeon.y0 + 1; // Height of the clay pigeon image TODO Make constant. If not constant, change to lower case
    short CLAY_WIDTH = pidgeon.x1 - pidgeon.x0 + 1; // Width of the clay pigeon image TODO Make constant. If not constant, change to lower case
    BaseType_t status;
    MOVE_DIR clay_x_move;
    uint8_t x, y; // x and y positions of the clay pigeon


    while(true) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait until task is notified to start

        // Don't allow the background to redraw while the clay pigeon is on the screen
        xSemaphoreTake(Sem_Background, portMAX_DELAY);

        move_up = true; // The clay pigeon should initially be moving up
        x = LCD_HORIZONTAL_MAX / 2; // todo randomize initial x position
        y = SKY_BOTTOM_Y - (CLAY_HEIGHT / 2) - STEP_VAL - 1; // todo replace crosshair_height with clay pigeon height


        while(y < SKY_BOTTOM_Y - (CLAY_HEIGHT / 2) - STEP_VAL) { // todo replace crosshair_height with clay pigeon height
            if(y <= (CLAY_HEIGHT / 2) + STEP_VAL + 1)
                move_up = false;

            if(move_up) y--; // todo y -= level #
            else y++; // todo y += level #

            // Wait until a new x move (including no move) is received from Queue_Accelerometer
            status = xQueueReceive(Queue_Accelerometer, &clay_x_move, portMAX_DELAY);

            switch(clay_x_move) {
                case LEFT:
                    // Move to the left unless the clay pigeon is already at the LCD left boundary; in which case, stay at the boundary
                    if(x > (CLAY_WIDTH / 2) + STEP_VAL)
                        x -= STEP_VAL;
                    break;
                case RIGHT:
                    // Move to the right unless the clay pigeon is already at the LCD right boundary; in which case, stay at the boundary
                    if(x < LCD_HORIZONTAL_MAX - (CLAY_WIDTH / 2) - STEP_VAL)
                        x += STEP_VAL;
                    break;
            }

            /* TODO Remove
            if(clay_x_move == ) {
                // move to the left unless the clay pigeon is already at the left boundary. in which case, stay at the boundary
                if(cx > (CLAY_WIDTH / 2) + STEP_VAL) cx -= STEP_VAL; // TODO replace crosshair_width with clay pigeon width
                // TODO else cx = 1 + CLAY_WIDTH / 2; // todo replace crosshair_width with clay pigeon width
            } else if (ACCEL_X == ACCEL_DIR_RIGHT) {
                // move to the right unless the clay pigeon is already at the right boundary. in which case, stay at the boundary
                if(cx < LCD_HORIZONTAL_MAX - (CLAY_WIDTH / 2) - STEP_VAL) cx += STEP_VAL; // todo replace crosshair_width with clay pigeon width
                // TODO else cx = LCD_HORIZONTAL_MAX - (CLAY_WIDTH / 2); // todo replace crosshair_width with clay pigeon width
            }*/

            // Redraw clay pigeon now that it has moved
            draw_clay(&pidgeon,x,y);

            vTaskDelay(pdMS_TO_TICKS(30)); // TODO Could slow down the delay when the clay pigeon gets closer to the top of the screen/peak of its arc
        }
        // Allow the background to redraw now that the clay pigeon is done
        xSemaphoreGive(Sem_Background);

        // Clear task notification's value so that the task cannot be notified while it is running (e.g. if the inner while loop is running and the
        // user tilts forward/notifies the task again, this will make sure any such notification attempts are not seen/processed at the next iteration
        // of the outer while loop/when the task runs again)
        ulTaskNotifyValueClear(TaskH_clayPigeon, 0xFFFFFFFF);
    }
}


