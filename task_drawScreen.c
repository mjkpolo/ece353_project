/*
 * task_drawScreen.c
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#include "task_drawScreen.h"
#include "lcd.h"

TaskHandle_t TaskH_drawScreen;
QueueHandle_t Draw_Queue;

// TODO header
void Task_drawScreen(void* pvParameters)
{
    while(true) {
      image* image = NULL;
      xQueueReceive(Draw_Queue, &image, portMAX_DELAY);
      if (image) draw(image);
      vTaskDelay(pdMS_TO_TICKS(30));
    }
}
