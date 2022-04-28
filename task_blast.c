/*
 * task_blast.c
 *
 *  Created on: Apr 28, 2022
 *      Author: james
 */

#include <task_blast.h>

TaskHandle_t TaskH_TaskBlast;
TaskHandle_t TaskH_updateBackground;

/******************************************************************************
* Prints a message to the Console
******************************************************************************/
void TaskBlast(void *pvParameters)
{
    // TODO BaseType_t status;
    BaseType_t xHigherPriorityTaskWoken;

    while(1)
    {
        // Wait for ISR to let us know that the button has been pressed
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Notify blast task to shoot at the crosshairs
        xTaskNotifyGive(TaskH_updateBackground);
                // TODO vTaskNotifyGive(TaskH_updateBackground, &xHigherPriorityTaskWoken);

                // TODO portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        // TODO Sounds MKII buzzer for shot and shoot
        //draw_light_background();
    }
}

