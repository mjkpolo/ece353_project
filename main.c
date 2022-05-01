#include "main.h"
#include "msp.h"
#include "msp432p401r.h"
// TODO Remove: #include "msp.h"
// TODO Remove: #include "msp432p401r.h"


// Tasks
#include "task_blast.h"
#include "task_clayPigeon.h"
#include "task_crosshair.h"
#include "task_background.h"
#include "task_drawScreen.h"
// Non-FreeRTOS
#include "images.h"
#include "lcd.h" // TODO Move hardware-related/non-FreeRTOS headers into main.h
#include "opt3001.h"
#include "ps2.h"
//#include "serial_debug.h"
#include "timer32.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


// TODO SemaphoreHandle_t Sem_LCD = NULL;

//TODO TaskHandle_t TaskH_clayPigeon;
//TODO TaskHandle_t TaskH_crosshair;

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
    //serial_debug_init();
}


// TODO Header ig
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
    init();
    size_t numImages;

    Sem_ClayLaunched = xSemaphoreCreateBinary();

    Sem_Background = xSemaphoreCreateBinary();
    add_image(&crosshair);
    add_image(&pidgeon);
    add_image(&score);
    numImages = add_image(&background);

    Draw_Queue = xQueueCreate(numImages,sizeof(image*));
    Queue_Accelerometer = xQueueCreate(1, sizeof(MOVE_DIR)); // TODO sizeof(LEFT) or sizeof(uint8_t) or 1???
    Queue_PS2 = xQueueCreate(1, sizeof(MOVE_t)); // TODO size ???
    Queue_Score = xQueueCreate(1, sizeof(uint8_t));
    Queue_Hit = xQueueCreate(1, sizeof(uint8_t));
    Queue_Ammo = xQueueCreate(1, sizeof(uint8_t));

    xSemaphoreGive(Sem_Background);
    xSemaphoreGive(Sem_ClayLaunched);

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
