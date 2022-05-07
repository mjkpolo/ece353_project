/*
 * task_endGame.c
 *
 *  Created on: May 4, 2022
 *      Author: james
 */

#include "task_endGame.h"
#include "lcd.h"
#include "adc14.h"

TaskHandle_t TaskH_endGame;
TaskHandle_t TaskH_crosshairBottomHalf;
TaskHandle_t TaskH_score;
TaskHandle_t TaskH_background;
SemaphoreHandle_t Sem_Timer;

/******************************************************************************
* Returns the state of S1 on MKII.
* Returns true if S1 is pressed, false if S1 is not pressed.
******************************************************************************/
bool MKII_S1(void) {
    return (P5->IN & BIT1) == 0;
}

/******************************************************************************
* End of game task/sequence. Draws the end of game splash screen and pauses
* user input from S2 on MKII and ADC14. This task runs until the user presses
* S1 on MKII to reset the game. This task repeatedly notifies Task_background
* so that the background can update whenever the level of light detected by
* the opt3001 light sensor changes.
******************************************************************************/
void Task_endGame(void* pvParameters) {
    uint8_t buttonState = 0;

    while(1) {
        // Wait for task to be notified (at the end of the game)
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Take the timer semaphore so that the ADC and button are no longer doing anything
        xSemaphoreTake(Sem_Timer, portMAX_DELAY);

        // Set PS2 values to values corresponding to the middle of the joystick
        PS2_X_VAL = 2000;
        PS2_Y_VAL = 2000;

        // Notify Task_crosshairBottomHalf to update the x and y movements of the crosshair (so it stops moving)
        xTaskNotifyGive(TaskH_crosshairBottomHalf);

        // Delay for a few ms to allow the crosshair to stop
        vTaskDelay(pdMS_TO_TICKS(5));

        // Erase the crosshair
        erase_image(&crosshair);

        // Draw end of game splash screen
        draw_end_splash(&end_splash, 66, 66);

        while (buttonState != 0xFF) {
            // Debounce S1 on MKII
            buttonState = buttonState << 1 | MKII_S1();

            xTaskNotifyGive(TaskH_background);

            vTaskDelay(pdMS_TO_TICKS(10));
        }

        // Erase the end of game splash screen
        erase_image(&end_splash);

        // Reset score
        SCORE = 0;
        xTaskNotifyGive(TaskH_score);

        // Move the crosshair to the center of the screen and redraw it
        crosshair_x = 64;
        crosshair_y = 64;
        draw_crosshair(&crosshair, crosshair_x, crosshair_y);

        // Reset buttonState
        buttonState = 0;

        // Reset number of clay pigeons hit
        CLAYS_HIT = 0;

        // Give the timer semaphore to enable gameplay/user input again
        xSemaphoreGive(Sem_Timer);
    }
}
