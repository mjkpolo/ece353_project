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
TaskHandle_t TaskH_accelerometerXBottomHalf;

// TODO QueueHandle_t Queue_Accelerometer;
QueueHandle_t Queue_Hit; // TODO include task_blast???
QueueHandle_t Queue_Ammo; // TODO include task_blast???
SemaphoreHandle_t Sem_ClayLaunched;
SemaphoreHandle_t Sem_Background; // TODO include task_background???

MOVE_DIR clay_x_move; // TODO


// TODO Header
void Task_clayPigeon(void *pvParameters)
{
    bool move_up; // Boolean used to track whether the clay pigeon should move up or down (ascending or descending)
    const uint8_t CLAY_HEIGHT = pidgeon.y1 - pidgeon.y0 + 1; // Height of the clay pigeon image TODO Make constant. If not constant, change to lower case
    const uint8_t CLAY_WIDTH = pidgeon.x1 - pidgeon.x0 + 1; // Width of the clay pigeon image TODO Make constant. If not constant, change to lower case
    BaseType_t status;
    // TODO MOVE_DIR clay_x_move;
    uint8_t clays_hit, ammo, y, dt = 0;
    float x, xf, dx;

    while(true) {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait until task is notified to start

        // Take semaphore to indicate that the clay has been launched
        xSemaphoreTake(Sem_ClayLaunched, portMAX_DELAY);

        // Don't allow the background to redraw while the clay pigeon is on the screen
        xSemaphoreTake(Sem_Background, portMAX_DELAY);

        // Fill Queue_Ammo. Although the queue should be empty at this point, don't wait if it's full
        xQueueSendToBack(Queue_Ammo, &ammo, 0);

        move_up = true; // The clay pigeon should initially be moving up
        // Start the clay pigeon immediately above the grass at the left or right boundary of the LCD
        x = (ACCEL_X % 2 == 0) ? (CLAY_WIDTH / 2) : (LCD_HORIZONTAL_MAX - CLAY_WIDTH / 2);
        // TODO x = (uint8_t) (LCD_HORIZONTAL_MAX * (rand() / (double) RAND_MAX));
        // TODO Remove x = LCD_HORIZONTAL_MAX / 2; // todo randomize initial x position
        y = SKY_BOTTOM_Y - (CLAY_HEIGHT / 2) - 1;
        // Determine the starting x position (left or right border or the LCD) and the x step needed to get from there
        // to the horizontal center of the screen +/- a random number between 0 and 30 when the clay pigeon lands
        xf = (LCD_HORIZONTAL_MAX / 2) + ((rand() % 2 == 0) ? -(ACCEL_Y % 31) : (ACCEL_Y % 31));
        dx = (float) (xf - ((x == CLAY_WIDTH / 2) ? 0 : LCD_HORIZONTAL_MAX)) / (2.0 * (float) (SKY_BOTTOM_Y - CLAY_HEIGHT / 2)); // TODO Check which cast(s) (if either) is/are needed


        while(y < SKY_BOTTOM_Y - (CLAY_HEIGHT / 2)) {
            // Check if the clay has been hit (don't wait for new elements)
            // If it has been hit, the total number of clays hit up to this point will be received
            status = xQueueReceive(Queue_Hit, &clays_hit, 0);

            // If the clay has been hit, check to see if the next level has been reached and break from the loop
            if(status == pdPASS) {
                // Increment the speed/step size of future clays if the user has hit enough clays to move on to the next level
                if(clays_hit % CLAYS_PER_LEVEL == 0) dt++; // TODO y_step++;
                break;
            }

            if(y <= (CLAY_HEIGHT / 2) + 5) move_up = false; // TODO I don't think CLAY_HEIGHT is properly calculating the height, as removing/adding it has no effect here

            if(move_up) y--; // TODO -= y_step;
            else y++; // TODO += y_step;

            // TODO Wait until a new x move (including no move) is received from Queue_Accelerometer
            // TODO status = xQueueReceive(Queue_Accelerometer, &clay_x_move, portMAX_DELAY);

            // Move the clay pigeon closer to the center of the screen
            x += dx;

            switch(clay_x_move) {
                case LEFT:
                    // Move to the left unless the clay pigeon is already at the LCD left boundary; in which case, stay at the boundary
                    //if(x > (CLAY_WIDTH / 2) + CLAY_X_STEP)
                        x -= dx / (dx < 0 ? -1.5 : 1.5); // TODO CLAY_X_STEP;
                    break;
                case RIGHT:
                    // Move to the right unless the clay pigeon is already at the LCD right boundary; in which case, stay at the boundary
                    //if(x < LCD_HORIZONTAL_MAX - (CLAY_WIDTH / 2) - CLAY_X_STEP)
                        x += dx / (dx < 0 ? -1.5 : 1.5); // TODO CLAY_X_STEP;
                    break;
            }

            // Redraw clay pigeon now that it has moved
            draw_clay(&pidgeon, (uint8_t) x, y); // TODO Call this asynchronously

            vTaskDelay(pdMS_TO_TICKS((dt > 20) ? 10 : (30 - dt))); // TODO Could slow down the delay when the clay pigeon gets closer to the top of the screen/peak of its arc
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

// TODO header
void Task_accelerometerXBottomHalf(void* pvParameters)
{
    BaseType_t status;
    uint8_t x_tilt_l_state = 0;
    uint8_t x_tilt_r_state = 0;

    while (true) {
        // Wait until task is notified to start by ADC14 ISR
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Debounce accelerometer x value to filter out readings from shaking the board

        // TODO Make this the same as tilting forward/backward (or make those the same as this)???
        // TODO Instead of having two separate values that go from 0x0F to 0xFF, have one value that goes from 0x0F to 0xFF (left) or 0x00 (right)
        x_tilt_r_state = x_tilt_r_state << 1;
        if(ACCEL_X > VOLT_TILT_R) {
            x_tilt_r_state |= 0x0F;
        }
        x_tilt_l_state = x_tilt_l_state << 1;
        if(ACCEL_X < VOLT_TILT_L) {
            x_tilt_l_state |= 0x0F;
        }
        // Update the x movement of the clay pigeon according to the x orientation of the accelerometer
        if(x_tilt_r_state == 0xFF) {
            clay_x_move = RIGHT;
        } else if(x_tilt_l_state == 0xFF) {
            clay_x_move = LEFT;
        } else {
            clay_x_move = NO_MOVE;
        }
    }
}

