/*
 * task_endGame.c
 *
 *  Created on: May 4, 2022
 *      Author: james
 */

#include "task_endGame.h"
#include "lcd.h" // TODO
#include "ps2.h" // TODO

TaskHandle_t TaskH_endGame;
TaskHandle_t TaskH_crosshair;
TaskHandle_t TaskH_clayPigeon; // TODO
SemaphoreHandle_t Sem_Timer;
QueueHandle_t Queue_Hit; // TODO
QueueHandle_t Queue_Score;

// TODO Header
bool MKII_S1(void) {
    return (P5->IN & BIT1) == 0;
}

// TODO Header
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

        // Notify Task_crosshair to update the x and y movements of the crosshair (so it stops moving)
        xTaskNotifyGive(TaskH_crosshair);

        // Erase the crosshair
        erase_image(&crosshair);

        // Draw end of game splash screen
        draw_end_splash(&end_splash, 66, 66);

        // TODO Use S1 instead

        while (buttonState != 0xFF) {
            // Debounce S1 on MKII
            buttonState = buttonState << 1 | MKII_S1();

            vTaskDelay(pdMS_TO_TICKS(10));
        }

        // Erase the end of game splash screen
        erase_image(&end_splash);

        // Reset score and all context for the game
        xQueueSendToBack(Queue_Score, &buttonState, portMAX_DELAY);

        // Reset buttonState
        buttonState = 0;

        // TODO Reset number of clay pigeons hit and number of points per clay pigeon

        //xQueueSendToBack(Queue_Hit, &buttonState, portMAX_DELAY);
        //xTaskNotifyGive(TaskH_clayPigeon);

        // Give the timer semaphore to enable gameplay/user input again
        xSemaphoreGive(Sem_Timer);
    }
}
