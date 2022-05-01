#include "main.h"
#include "msp.h"
#include "msp432p401r.h"
// TODO Remove: #include "msp.h"
// TODO Remove: #include "msp432p401r.h"


// Tasks
#include "task_blast.h"
#include "task_clayPigeon.h"
#include "task_crosshair.h"
// Non-FreeRTOS
#include "images.h"
#include "lcd.h" // TODO Move hardware-related/non-FreeRTOS headers into main.h
#include "opt3001.h"
#include "ps2.h"
#include "serial_debug.h"
#include "timer32.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

SemaphoreHandle_t Sem_Background = NULL;
// TODO SemaphoreHandle_t Sem_LCD = NULL;
QueueHandle_t Draw_Queue = NULL;

TaskHandle_t TaskH_background = NULL;
// TODO Remove: TaskHandle_t TaskH_s2 = NULL;
TaskHandle_t TaskH_drawScreen = NULL;
TaskHandle_t TaskH_clayPigeon;
TaskHandle_t TaskH_crosshair;

// TODO Remove QueueHandle_t Queue_PS2; // TODO Move to joystick task file

/* TODO
extern image background;
extern image crosshair;
extern image score;
extern image pidgeon;*/


inline void init(void)
{
    // TODO P3->DIR &= ~BIT5;
    P5->DIR &= ~BIT1;
    P5->DIR &= ~BIT5;

    Crystalfontz128x128_Init();

    t32_init();
    adc14_init();
    i2c_init();
    opt3001_init();
    serial_debug_init();
}

void Task_drawScreen(void* pvParameters) {
    while(true) {
      image* image = NULL;
      xQueueReceive(Draw_Queue, &image, portMAX_DELAY);
      if (image) draw(image);
      vTaskDelay(pdMS_TO_TICKS(30));
    }
}

void Task_background(void* pvParameters)
{
    BaseType_t received_points;
    uint16_t points;
    uint16_t score_val = 0;

    // Draw the score board initially
    draw_xx0(&score);
    draw_x0x(&score);
    draw_0xx(&score);
    draw_scoreboard(&score);

    while (true) {
        enum light { DARK,
            MEDIUM,
            BRIGHT,
            foo };

        // Check if any points have been received (don't wait if the queue is empty)
        received_points = xQueueReceive(Queue_Score, &points, 0);

        if(received_points == pdPASS) {
            // Increase the score by the number of points received
            score_val += points;

        // TODO Remove: if (score_val!=phits) {
            erase_image(&score);

            switch (score_val%10) {
                case 0 : draw_xx0(&score);
                         break;
                case 1 : draw_xx1(&score);
                         break;
                case 2 : draw_xx2(&score);
                         break;
                case 3 : draw_xx3(&score);
                         break;
                case 4 : draw_xx4(&score);
                         break;
                case 5 : draw_xx5(&score);
                         break;
                case 6 : draw_xx6(&score);
                         break;
                case 7 : draw_xx7(&score);
                         break;
                case 8 : draw_xx8(&score);
                         break;
                case 9 : draw_xx9(&score);
                         break;
            }
            switch ((score_val/10)%10) {
                case 0 : draw_x0x(&score);
                         break;
                case 1 : draw_x1x(&score);
                         break;
                case 2 : draw_x2x(&score);
                         break;
                case 3 : draw_x3x(&score);
                         break;
                case 4 : draw_x4x(&score);
                         break;
                case 5 : draw_x5x(&score);
                         break;
                case 6 : draw_x6x(&score);
                         break;
                case 7 : draw_x7x(&score);
                         break;
                case 8 : draw_x8x(&score);
                         break;
                case 9 : draw_x9x(&score);
                         break;
            }
            switch ((score_val/100)%10) {
                case 0 : draw_0xx(&score);
                         break;
                case 1 : draw_1xx(&score);
                         break;
                case 2 : draw_2xx(&score);
                         break;
                case 3 : draw_3xx(&score);
                         break;
                case 4 : draw_4xx(&score);
                         break;
                case 5 : draw_5xx(&score);
                         break;
                case 6 : draw_6xx(&score);
                         break;
                case 7 : draw_7xx(&score);
                         break;
                case 8 : draw_8xx(&score);
                         break;
                case 9 : draw_9xx(&score);
                         break;
            }

            draw_scoreboard(&score);
        }
        static enum light l, pl = foo; // so pl != l
        float lux = opt3001_read_lux();
        if (lux < 20)
            l = DARK;
        else if (lux < 75)
            l = MEDIUM;
        else
            l = BRIGHT;
        if (pl != l) {
            xSemaphoreTake(Sem_Background, portMAX_DELAY);
            erase_image(&background);
            switch (l) {
            case BRIGHT:
                draw_light_background(&background);
                break;
            case MEDIUM:
                draw_medium_background(&background);
                break;
            case DARK:
                draw_dark_background(&background);
                break;
            }
          xSemaphoreGive(Sem_Background);
        }
        pl=l;
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}


// TODO Header ig
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
    init();
    size_t numImages;

    Sem_Background = xSemaphoreCreateBinary();
    add_image(&crosshair);
    add_image(&pidgeon);
    add_image(&score);
    numImages = add_image(&background);

    Draw_Queue = xQueueCreate(numImages,sizeof(image*));
    Queue_Accelerometer = xQueueCreate(1, sizeof(MOVE_DIR)); // TODO sizeof(LEFT) or sizeof(uint8_t) or 1???
    Queue_PS2 = xQueueCreate(1, sizeof(MOVE_t)); // TODO size ???
    Queue_Score = xQueueCreate(1, sizeof(uint16_t));
    Queue_Hit = xQueueCreate(1, sizeof(uint8_t));

    xSemaphoreGive(Sem_Background);

    // TODO Remove: Draw_Queue = xQueueCreate(8,sizeof(image*));

    /* TODO Remove
    add_image(&crosshair);
    add_image(&pidgeon);
    add_image(&score);
    add_image(&background);
    draw_scoreboard(&score);

    xSemaphoreGive(Sem_LCD);*/
    xTaskCreate(Task_clayPigeon, "pullClay", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_clayPigeon);
    xTaskCreate(Task_background, "background", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_background);
    xTaskCreate(Task_crosshair, "crosshair", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_crosshair);
    xTaskCreate(Task_drawScreen, "drawScreen", configMINIMAL_STACK_SIZE, NULL, 2, &TaskH_drawScreen);
    xTaskCreate(TaskBlast, "blast", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_TaskBlast);
    // TODO xTaskCreate(Task_s2, "s2", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_s2);

    vTaskStartScheduler();
    while (true);
    return 0;
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while (1) {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char* pcTaskName)
{
    // Handle FreeRTOS Stack Overflow
    while (1) {
    }
}
