#include "main.h"
#include "msp.h"
#include "msp432p401r.h"
// Tasks
#include "task_blast.h"
#include "task_clayPigeon.h"
#include "task_crosshair.h"
#include "task_background.h"
#include "task_drawScreen.h"
#include "task_timer.h"
#include "task_endGame.h"
#include "task_score.h"
// Non-FreeRTOS
#include "images.h"
#include "lcd.h"
#include "opt3001.h"
#include "adc14.h"
// TODO Remove #include "timer32.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// TODO SemaphoreHandle_t Sem_LCD = NULL;

extern SemaphoreHandle_t Sem_Erase; // TODO

uint8_t CLAYS_HIT = 0; // Number of clays hit
uint16_t SCORE = 0; // Score
short crosshair_x = 64, crosshair_y = 64;
volatile bool AMMO = false; // true if there is ammo; false otherwise

// TODO Header
inline void init(void)
{
    P5->DIR &= ~BIT1;
    P5->DIR &= ~BIT5;

    Crystalfontz128x128_Init();

    // TODO Remove t32_init();
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
    Sem_Erase = xSemaphoreCreateBinary();
    Sem_Timer = xSemaphoreCreateBinary();

    xSemaphoreGive(Sem_ClayLaunched);
    xSemaphoreGive(Sem_Erase);
    xSemaphoreGive(Sem_Timer);

    add_image(&crosshair);
    add_image(&pidgeon);
    add_image(&score);
    add_image(&end_splash);
    numImages = add_image(&background);

    Draw_Queue = xQueueCreate(numImages,sizeof(image*));

    xTaskCreate(Task_clayPigeon, "drawClay", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_clayPigeon);
    xTaskCreate(Task_accelerometerXBottomHalf, "updateClayX", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_accelerometerXBottomHalf);
    xTaskCreate(Task_background, "background", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_background);
    xTaskCreate(Task_score, "score", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_score);
    xTaskCreate(Task_crosshairBottomHalf, "updateCrosshairMovement", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_crosshairBottomHalf);
    xTaskCreate(Task_drawCrosshair, "drawCrosshair", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_drawCrosshair);

    //xTaskCreate(Task_clayPigeon, "drawClay", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_clayPigeon);
    //xTaskCreate(Task_accelerometerXBottomHalf, "updateClayX", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_accelerometerXBottomHalf);
    //xTaskCreate(Task_background, "background", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_background);
    //xTaskCreate(Task_score, "score", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_score);
    //xTaskCreate(Task_crosshairBottomHalf, "crosshair", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_crosshairBottomHalf);
    //xTaskCreate(Task_drawCrosshair, "drawCrosshair", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_drawCrosshair);
    

    xTaskCreate(Task_drawScreen, "drawScreen", configMINIMAL_STACK_SIZE, NULL, 2, &TaskH_drawScreen);
    xTaskCreate(TaskBlast, "blast", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_TaskBlast);
    xTaskCreate(Task_timer, "buttonADCTimer", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_timer);
    xTaskCreate(Task_endGame, "endGame", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_endGame);

    xTaskNotifyGive(TaskH_background); //TODO

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
        printf("mem alloc error\r\n");
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
        printf("stack overflow error\r\n");
    }
}
