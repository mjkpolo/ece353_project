/*
 * task_clayPigeon.c
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#include "task_clayPigeon.h"
#include "lcd.h"
#include "adc14.h"


TaskHandle_t TaskH_clayPigeon;
TaskHandle_t TaskH_accelerometerXBottomHalf;
TaskHandle_t TaskH_background;

SemaphoreHandle_t Sem_ClayLaunched;

MOVE_DIR clay_x_move;


// TODO Header
void Task_clayPigeon(void *pvParameters)
{
    bool move_up; // Boolean used to track whether the clay pigeon should move up or down (ascending or descending)
    bool prev_ammo; // Boolean used to track the previous value of AMMO when the value of AMMO switches
    const short CLAY_HEIGHT = pidgeon.y1 - pidgeon.y0 + 1; // Height of the clay pigeon image
    const short CLAY_WIDTH = pidgeon.x1 - pidgeon.x0 + 1; // Width of the clay pigeon image
    short prev_clays_hit; // previous number of clays hit
    short y; // y position of clay
    short dt = 0; // task wait time decrease
    float x; // x position of clay
    float dx; // x step of clay

    while(true) {
        // Wait until task is notified to start
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Take semaphore to indicate that the clay has been launched
        xSemaphoreTake(Sem_ClayLaunched, portMAX_DELAY);

        // Fill ammo initially
        AMMO = true;
        prev_ammo = true;
        // The clay pigeon should initially be moving up
        move_up = true;
        // Start the clay pigeon immediately above the grass at the left or right boundary of the LCD
        bool left = ACCEL_X%2;
        x = (left) ? 0 : 131;
        y = SKY_BOTTOM_Y;
        // Determine the x step of the clay pigeon (a random float between 0.5 and 1.5)
        dx = (10+ACCEL_Y%21)/(float)20;

        // Update the previous number of clays hit
        prev_clays_hit = CLAYS_HIT;
        // Set the speed of the clay pigeon according to the current level/number of clays that have been hit
        dt = CLAYS_HIT / CLAYS_PER_LEVEL;

        while((y<=SKY_BOTTOM_Y)&(x>0 && x<=131)) {
            // Check if the clay has been hit. If so, break from the loop
            if(CLAYS_HIT != prev_clays_hit) break;

            // Check if ammo has switched between full and empty
            if(AMMO != prev_ammo) {
                if(AMMO) erase_image(&warn_ammo); // Ammo is full; erase ammo warning
                else draw_warn_ammo(&warn_ammo); // Ammo is empty; draw ammo warning
                // Update prev_ammo
                prev_ammo = AMMO;
            }

            // Check if the clay has hit the top of the screen. If so, it should descend
            if(y <= (CLAY_HEIGHT / 2)) move_up = false; // TODO I don't think CLAY_HEIGHT is properly calculating the height, as removing/adding it has no effect here

            // Adjust the clay's x movement if the user is tilting the board to the left or right
            switch(clay_x_move) {
                case LEFT: // Tilting left
                    // Increase the clay's movement to the left (or decrease its movement to the right)
                    x -= dx / 2;
                    break;
                case RIGHT: // Tilting right
                    // Increase the clay's movement to the right (or decrease its movement to the left)
                    x += dx / 2;
                    break;
            }

            // Redraw clay pigeon now that it has moved
            draw_clay(&pidgeon, (uint8_t) x, y);

            // Move the clay pigeon in the y direction
            if(move_up) y--;
            else y++;

            // Move the clay pigeon in the x direction (toward the vertical border opposite where it started,
            // adjusting according to the accelerometer x tilt)
            x = left ? x+dx : x-dx;

            // Wait for a certain amount of time (no less than 5ms) according to the number of clays hit
            // As more clays are hit/the level increases, the wait time will decrease
            vTaskDelay(pdMS_TO_TICKS((CLAYS_PER_LEVEL*dt > 25) ? 5 : (30 - CLAYS_PER_LEVEL*dt)));
        }

        // Give semaphore to indicate that the clay is no longer in the air
        xSemaphoreGive(Sem_ClayLaunched);

        if(AMMO) AMMO = false; // If ammo is full, so empty ammo so that there is no ammo when the clay pigeon is no longer in the air
        else erase_image(&warn_ammo); // Ammo is empty, so erase ammo warning since the clay is no longer in the air and firing is disabled

        // The clay is no longer in the air, so erase the clay pigeon image
        erase_image(&pidgeon);

        // Change the background for the next clay pigeon if the lighting has changed
        xTaskNotifyGive(TaskH_background);


        // TODO \/\/ Remove if the logic in ps2.c is reworked \/\/

        // Clear task notification's value so that the task cannot be notified while it is running (e.g. if the inner while loop is running and the
        // user tilts forward/notifies the task again, this will make sure any such notification attempts are not seen/processed at the next iteration
        // of the outer while loop/when the task runs again)
        ulTaskNotifyValueClear(TaskH_clayPigeon, 0xFFFFFFFF);
    }
}

// TODO header
void Task_accelerometerXBottomHalf(void* pvParameters)
{
    uint8_t x_tilt_l_state = 0;
    uint8_t x_tilt_r_state = 0;

    while (true) {
        // Wait until task is notified to start by ADC14 ISR
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // "Debounce" accelerometer x value to filter out readings from shaking the board
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

