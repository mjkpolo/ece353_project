#include "main.h"
#include "images.h"
#include "lcd.h" // TODO Move hardware-related/non-FreeRTOS headers into main.h
#include "msp.h"
#include "msp432p401r.h"
#include "msp.h"
#include "msp432p401r.h"
#include "opt3001.h"
#include "ps2.h"
#include "task_blast.h"
#include "serial_debug.h"
#include "timer32.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define STEP_VAL 1

SemaphoreHandle_t Sem_Background = NULL;
QueueHandle_t Draw_Queue = NULL;
TaskHandle_t TaskH_joystick = NULL;
TaskHandle_t TaskH_background = NULL;
TaskHandle_t TaskH_s2 = NULL;
TaskHandle_t TaskH_drawScreen = NULL;
extern image background;
extern image crosshair;
extern image score;
extern image pidgeon;
static short x = 64, y = 64;
static uint8_t phits = 0xFF;
static uint8_t hits = 0;

inline void init(void)
{
    // TODO P3->DIR &= ~BIT5;
    P5->DIR &= ~BIT1;
    P5->DIR &= ~BIT5;

    Crystalfontz128x128_Init();

    adc14_init();
    i2c_init();
    opt3001_init();
    serial_debug_init();
}

void Task_s2(void* pvParameters)
{
    while (true) {
        static uint8_t buttonState = 0;
        buttonState = buttonState << 1 | MKII_S2();

        if (buttonState == 0xF) S2_P = true;
        if (S2_P) hits++;
        S2_P = false;
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;
        vTaskDelay(pdMS_TO_TICKS(15));
    }
}

void Task_drawScreen(void* pvParameters) {
    while(true) {
      image* image = NULL;
      xQueueReceive(Draw_Queue, &image, portMAX_DELAY);
      draw(image);
      vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void Task_background(void* pvParameters)
{
    while (true) {
        enum light { DARK,
            MEDIUM,
            BRIGHT,
            foo };
        if (hits!=phits) {
          erase_image(&score);
          switch (hits%10) {
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
          switch ((hits/10)%10) {
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
          switch ((hits/100)%10) {
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
          phits = hits;
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

void Task_joystick(void* pvParameters)
{
    while (true) {
        if (PS2_Y_VAL == PS2_DIR_UP)
            y -= 1;
        else if (PS2_Y_VAL == PS2_DIR_DOWN)
            y += 1;
        if (PS2_X_VAL == PS2_DIR_LEFT)
            x -= 1;
        else if (PS2_X_VAL == PS2_DIR_RIGHT)
            x += 1;
        x = x < 0 ? 0 : x > 131 ? 131
                                : x;
        y = y < 0 ? 0 : y > 131 ? 131
                                : y;
        draw_crosshair(&crosshair, x, y);
        vTaskDelay(pdMS_TO_TICKS(7));
    }
}

// TODO Header and move to its own file
void Task_clayPigeon(void *pvParameters)
{
    // Boolean used to track whether the clay pigeon should move up or down
    bool move_up;
    short crosshair_height = crosshair.y1 - crosshair.y0+1;
    short crosshair_width = crosshair.x1 - crosshair.x0+1;

    while(true) {
        short x,y;
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait until task is notified to start
        xSemaphoreTake(Sem_Background, portMAX_DELAY);

        move_up = true; // The clay pigeon should initially be moving up
        // TODO Use different x and y variables
        y = 131 - (crosshair_height / 2) - 1; // todo replace crosshair_height with clay pigeon height
        x = 131 / 2; // todo randomize initial x position

        while(y < 131 - (crosshair_height / 2)) { // todo replace crosshair_height with clay pigeon height
            if(move_up) y--; // todo y -= level #
            else y++; // todo y += level #

            if(y <= (crosshair_height / 2)) move_up = false;

            if(ACCEL_X == ACCEL_DIR_LEFT) {
                // move to the left unless the clay pigeon is already at the left boundary. in which case, stay at the boundary
                if(x > (crosshair_width / 2) + STEP_VAL) x -= STEP_VAL; // TODO replace crosshair_width with clay pigeon width
                else x = 1 + crosshair_width / 2; // todo replace crosshair_width with clay pigeon width
            } else if (ACCEL_X == ACCEL_DIR_RIGHT) {
                // move to the right unless the clay pigeon is already at the right boundary. in which case, stay at the boundary
                if(x < 131 - (crosshair_width / 2) - STEP_VAL) x += STEP_VAL; // todo replace crosshair_width with clay pigeon width
                else x = 131 - (crosshair_width / 2); // todo replace crosshair_width with clay pigeon width
            }

            draw_clay(&pidgeon,x,y); // todo replace with draw clay pigeon
            vTaskDelay(pdMS_TO_TICKS(15)); // TODO Could slow down the delay when the clay pigeon gets closer to the top of the screen/peak of its arc
        }
        xSemaphoreGive(Sem_Background);

        // Clear task notification's value so that the task cannot be notified while it is running (e.g. if the inner while loop is running and the
        // user tilts forward/notifies the task again, this will make sure any such notification attempts are not seen/processed at the next iteration
        // of the outer while loop/when the task runs again)
        ulTaskNotifyValueClear(TaskH_clayPigeon, 0xFFFFFFFF);
    }
}

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

    xSemaphoreGive(Sem_Background);
    xTaskCreate(Task_clayPigeon, "pullClay", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_clayPigeon);
    xTaskCreate(Task_background, "background", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_background);
    xTaskCreate(Task_joystick, "joystick", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_joystick);
    xTaskCreate(Task_drawScreen, "drawScreen", configMINIMAL_STACK_SIZE, NULL, 2, &TaskH_drawScreen);
    xTaskCreate(TaskBlast, "blast", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_TaskBlast);
    xTaskCreate(Task_s2, "s2", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_s2);

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
