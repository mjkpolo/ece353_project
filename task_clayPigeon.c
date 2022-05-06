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
TaskHandle_t TaskH_background; // TODO

SemaphoreHandle_t Sem_ClayLaunched;
SemaphoreHandle_t Sem_Background;

MOVE_DIR clay_x_move;


// TODO Header
void Task_clayPigeon(void *pvParameters)
{
    bool move_up; // Boolean used to track whether the clay pigeon should move up or down (ascending or descending)
    const short CLAY_HEIGHT = pidgeon.y1 - pidgeon.y0 + 1; // Height of the clay pigeon image
    const short CLAY_WIDTH = pidgeon.x1 - pidgeon.x0 + 1; // Width of the clay pigeon image
    BaseType_t status;
    short y, dt = 0;
    uint8_t prev_clays_hit;
    float x, xf, dx;

    while(true) {
        // Wait until task is notified to start
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Take semaphore to indicate that the clay has been launched
        xSemaphoreTake(Sem_ClayLaunched, portMAX_DELAY);

        // Don't allow the background to redraw while the clay pigeon is on the screen
        xSemaphoreTake(Sem_Background, portMAX_DELAY);

        // Fill ammo initially
        AMMO = true;
        // The clay pigeon should initially be moving up
        move_up = true;
        // Start the clay pigeon immediately above the grass at the left or right boundary of the LCD
        x = (ACCEL_X % 2 == 0) ? (CLAY_WIDTH / 2) : (LCD_HORIZONTAL_MAX - CLAY_WIDTH / 2);
        y = SKY_BOTTOM_Y - (CLAY_HEIGHT / 2) - 1;
        // Determine the starting x position (left or right border or the LCD) and the x step needed to get from there
        // to the horizontal center of the screen +/- a random number between 0 and 30 when the clay pigeon lands
        xf = (LCD_HORIZONTAL_MAX / 2) + ((rand() % 2 == 0) ? -(ACCEL_Y % 31) : (ACCEL_Y % 31));
        dx = (float) (xf - ((x == CLAY_WIDTH / 2) ? 0 : LCD_HORIZONTAL_MAX)) / (2.0 * (float) (SKY_BOTTOM_Y - CLAY_HEIGHT / 2)); // TODO Check which cast(s) (if either) is/are needed

        // Update the previous number of clays hit
        prev_clays_hit = CLAYS_HIT;
        // Set the speed of the clay pigeon according to the current level/number of clays that have been hit
        dt = CLAYS_HIT / CLAYS_PER_LEVEL;

        while(y < SKY_BOTTOM_Y - (CLAY_HEIGHT / 2)) {
            // Check if the clay has been hit. If so, break from the loop
            if(CLAYS_HIT != prev_clays_hit) break;

            // Check if the clay has hit the top of the screen. If so, it should descend
            if(y <= (CLAY_HEIGHT / 2)) move_up = false; // TODO I don't think CLAY_HEIGHT is properly calculating the height, as removing/adding it has no effect here

            if(move_up) y--;
            else y++;

            // Move the clay pigeon closer to the center of the screen
            x += dx;

            // Adjust the clay's x movement if the user is tilting the board to the left or right
            switch(clay_x_move) {
                case LEFT: // Tilting left
                    // Increase the clay's movement to the left (or decrease its movement to the right)
                    x -= dx / (dx < 0 ? -1.5 : 1.5);
                    break;
                case RIGHT: // Tilting right
                    // Increase the clay's movement to the right (or decrease its movement to the left)
                    x += dx / (dx < 0 ? -1.5 : 1.5);
                    break;
            }

            // Redraw clay pigeon now that it has moved
            draw_clay(&pidgeon, (uint8_t) x, y);

            vTaskDelay(pdMS_TO_TICKS((dt > 20) ? 10 : (30 - dt))); // TODO Could slow down the delay when the clay pigeon gets closer to the top of the screen/peak of its arc
        }

        // Give semaphore to indicate that the clay is no longer in the air
        xSemaphoreGive(Sem_ClayLaunched);

        // Empty ammo so that there is no ammo when the clay pigeon is no longer in the air
        AMMO = false;

        // The clay is no longer in the air, so erase the clay pigeon image
        erase_image(&pidgeon);

        // Allow the background to redraw now that the clay pigeon is done
        xSemaphoreGive(Sem_Background);

        xTaskNotifyGive(TaskH_background); // TODO

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

