/*
 * task_timer.c
 *
 *  Created on: May 4, 2022
 *      Author: james
 */

#include "task_timer.h"

TaskHandle_t TaskH_timer;
TaskHandle_t TaskH_TaskBlast;

SemaphoreHandle_t Sem_Timer;

/******************************************************************************
* Returns the state of S2 on MKII.
* Returns true if S2 is pressed, false if S2 is not pressed.
******************************************************************************/
bool MKII_S2(void) {
    return (P3->IN & BIT5) == 0;
}

/******************************************************************************
* Used to start ADC14 conversions and to read/debounce S2 on MKII. When S2 is
* pressed, Task_blast is notified. This task takes and gives the Sem_Timer
* semaphore at the beginning and end of each iteration, respectively, so this
* task can be blocked by another task taking Sem_Timer.
******************************************************************************/
void Task_timer(void* pvParameters) {

    BaseType_t xHigherPriorityTaskWoken;
    uint8_t buttonState = 0;

    while(1) {
        // Take timer semaphore
        xSemaphoreTake(Sem_Timer, portMAX_DELAY);

        // Debounce S2 on MKII
        buttonState = buttonState << 1 | MKII_S2();

        if (buttonState == 0x7F) {
            // Notify blast task to shoot at the crosshairs
            xTaskNotifyGive(TaskH_TaskBlast);
        }

        // Start ADC conversion
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

        // Give timer semaphore
        xSemaphoreGive(Sem_Timer);

        // 10 ms delay
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
