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
QueueHandle_t Queue_Hit; // TODO include task_blast???
QueueHandle_t Queue_Ammo; // TODO include task_blast???
SemaphoreHandle_t Sem_ClayLaunched;
SemaphoreHandle_t Sem_Background; // TODO include task_background???


// TODO Header
void Task_clayPigeon(void *pvParameters)
{
    bool move_up; // Boolean used to track whether the clay pigeon should move up or down (ascending or descending)
    short CLAY_HEIGHT = pidgeon.y1 - pidgeon.y0 + 1; // Height of the clay pigeon image TODO Make constant. If not constant, change to lower case
    short CLAY_WIDTH = pidgeon.x1 - pidgeon.x0 + 1; // Width of the clay pigeon image TODO Make constant. If not constant, change to lower case
    BaseType_t status;
    MOVE_DIR clay_x_move;
    uint8_t clays_hit, ammo, y_step = 1;
    uint8_t x, y; // x and y positions of the clay pigeon


    while(true) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait until task is notified to start

        // Take semaphore to indicate that the clay has been launched
        xSemaphoreTake(Sem_ClayLaunched, portMAX_DELAY);

        // Don't allow the background to redraw while the clay pigeon is on the screen
        xSemaphoreTake(Sem_Background, portMAX_DELAY);

        // Fill Queue_Ammo. Although the queue should be empty at this point, don't wait if it's full
        xQueueSendToBack(Queue_Ammo, &ammo, 0);

        move_up = true; // The clay pigeon should initially be moving up
        x = (uint8_t) (LCD_HORIZONTAL_MAX * (rand() / (double) RAND_MAX));
        // TODO Remove x = LCD_HORIZONTAL_MAX / 2; // todo randomize initial x position
        y = SKY_BOTTOM_Y - (CLAY_HEIGHT / 2) - 1;


        while(y < SKY_BOTTOM_Y - (CLAY_HEIGHT / 2)) {
            // Check if the clay has been hit (don't wait for new elements)
            // If it has been hit, the total number of clays hit up to this point will be received
            status = xQueueReceive(Queue_Hit, &clays_hit, 0);

            // If the clay has been hit, check to see if the next level has been reached and break from the loop
            if(status == pdPASS) {
                // Increment the speed/step size of future clays if the user has hit enough clays to move on to the next level
                if(clays_hit % CLAYS_PER_LEVEL == 0) y_step++;
                break;
            }

            if(y <= (CLAY_HEIGHT / 2) + y_step + 2) move_up = false;

            if(move_up) y -= y_step;
            else y += y_step;

            // Wait until a new x move (including no move) is received from Queue_Accelerometer
            status = xQueueReceive(Queue_Accelerometer, &clay_x_move, portMAX_DELAY);

            switch(clay_x_move) {
                case LEFT:
                    // Move to the left unless the clay pigeon is already at the LCD left boundary; in which case, stay at the boundary
                    if(x > (CLAY_WIDTH / 2) + CLAY_X_STEP)
                        x -= CLAY_X_STEP;
                    break;
                case RIGHT:
                    // Move to the right unless the clay pigeon is already at the LCD right boundary; in which case, stay at the boundary
                    if(x < LCD_HORIZONTAL_MAX - (CLAY_WIDTH / 2) - CLAY_X_STEP)
                        x += CLAY_X_STEP;
                    break;
            }

            // Redraw clay pigeon now that it has moved
            draw_clay(&pidgeon,x,y); // TODO Call this asynchronously

            vTaskDelay(pdMS_TO_TICKS(30)); // TODO Could slow down the delay when the clay pigeon gets closer to the top of the screen/peak of its arc
        }

        // Give semaphore to indicate that the clay is no longer in the air
        xSemaphoreGive(Sem_ClayLaunched);

        // Reset Queue_Ammo so that there is no ammo when the clay pigeon is no longer in the air
        xQueueReset(Queue_Ammo);

        // The clay is no longer in the air, so erase the clay pigeon image
        erase_image(&pidgeon);

        // Allow the background to redraw now that the clay pigeon is done
        xSemaphoreGive(Sem_Background);

        // Clear task notification's value so that the task cannot be notified while it is running (e.g. if the inner while loop is running and the
        // user tilts forward/notifies the task again, this will make sure any such notification attempts are not seen/processed at the next iteration
        // of the outer while loop/when the task runs again)
        ulTaskNotifyValueClear(TaskH_clayPigeon, 0xFFFFFFFF);
    }
}


