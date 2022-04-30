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
#define SKY_BOTTOM_Y 95

SemaphoreHandle_t Sem_LCD = NULL;
TaskHandle_t TaskH_joystick = NULL;
TaskHandle_t TaskH_newFrame = NULL;
TaskHandle_t TaskH_s2 = NULL;
extern image background;
extern image crosshair;
extern image score;
extern image pidgeon;
static short x = 64, y = 64, px=64, py=64, cx, cy, pcx, pcy;
static uint8_t phits = 0xFF;
static uint8_t hits = 0;

const short CROSSHAIR_HEIGHT = 22;
const short CROSSHAIR_WIDTH = 22;
const short CLAY_HEIGHT = 4;
const short CLAY_WIDTH = 22;
uint16_t sky_color = 0x8718;

static bool show_clay = false;


inline void draw_crosshair_basic(uint8_t x, uint8_t y, uint8_t px, uint8_t py) {
    xSemaphoreTake(Sem_LCD, portMAX_DELAY);
    // TODO Account for movement when erasing

    // TODO lcd_draw_rectangle(px,py,22,4,sky_color);
    // TODO lcd_draw_rectangle(px,py,4,22,sky_color);



    // TODO Mostly works when drawing everything in one function
    lcd_draw_rectangle(px, py, 22, 4, sky_color);
    lcd_draw_rectangle(px, py, 4, 22, sky_color);

    if(x > px) {
        lcd_draw_rectangle(px - 1, py + 6, x - px + 4, 11, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(px - 1, py - 6, x - px + 4, 11, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(px - 11, py, x - px + 4, 6, sky_color);
    } else {
        lcd_draw_rectangle(px + 1, py + 6, px - x + 4, 11, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(x + 1, py - 6, px - x + 4, 11, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(px + 10, py, px - x + 4, 6, sky_color);
    }

    if(y > py) {
        lcd_draw_rectangle(px - 6, py - 1, 11, y - py + 4, sky_color);
        lcd_draw_rectangle(px + 6, py - 1, 11, y - py + 4, sky_color); // TODO Could have width be 9 instead of 10
        lcd_draw_rectangle(px, py - 11, 6, y - py + 4, sky_color);
    } else {
        lcd_draw_rectangle(px - 6, py + 1, 11, py - y + 4, sky_color);
        lcd_draw_rectangle(px + 6, py + 1, 11, py - y + 4, sky_color); // TODO Could have width be 9 instead of 10
        lcd_draw_rectangle(px, py + 10, 6, py - y + 4, sky_color);
    }


    /* TODO if(x > px) {
        lcd_draw_rectangle(px - 2, py + 6, STEP_VAL + 1, 10, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(px - 2, py - 6, STEP_VAL + 1, 10, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(px - 11, py, STEP_VAL + 1, 4, sky_color);
    } else {
        lcd_draw_rectangle(px + 10, py, STEP_VAL + 1, 4, sky_color);
        lcd_draw_rectangle(px + 1, py + 6, STEP_VAL + 1, 10, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(px + 1, py - 6, STEP_VAL + 1, 10, sky_color); // TODO Could have width be 8 instead of 9
    }

    if(y > py) {
        lcd_draw_rectangle(px - 6, py - 2, 10, STEP_VAL + 1, sky_color);
        lcd_draw_rectangle(px + 6, py - 2, 10, STEP_VAL + 1, sky_color); // TODO Could have width be 9 instead of 10
        lcd_draw_rectangle(px, py - 11, 4, STEP_VAL + 1, sky_color);
    } else {
        lcd_draw_rectangle(px - 6, py + 1, 10, STEP_VAL + 1, sky_color);
        lcd_draw_rectangle(px + 6, py + 1, 10, STEP_VAL + 1, sky_color); // TODO Could have width be 9 instead of 10
        lcd_draw_rectangle(px, py + 10, 4, STEP_VAL + 1, sky_color);
    }*/


    /*if(x > px) {
        lcd_draw_rectangle(px - 2, py + 6, 1, 10, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(px - 2, py - 6, 1, 10, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(px - 11, py, 1, 4, sky_color);
    } else {
        lcd_draw_rectangle(px + 10, py, 1, 4, sky_color);
        lcd_draw_rectangle(px + 1, py + 6, 1, 10, sky_color); // TODO Could have width be 8 instead of 9
        lcd_draw_rectangle(px + 1, py - 6, 1, 10, sky_color); // TODO Could have width be 8 instead of 9
    }

    if(y > py) {
        lcd_draw_rectangle(px - 6, py - 2, 10, 1, sky_color);
        lcd_draw_rectangle(px + 6, py - 2, 10, 1, sky_color); // TODO Could have width be 9 instead of 10
        lcd_draw_rectangle(px, py - 11, 4, 1, sky_color);
    } else {
        lcd_draw_rectangle(px - 6, py + 1, 10, 1, sky_color);
        lcd_draw_rectangle(px + 6, py + 1, 10, 1, sky_color); // TODO Could have width be 9 instead of 10
        lcd_draw_rectangle(px, py + 10, 4, 1, sky_color);
    }*/



    lcd_draw_rectangle(x + 10, y, 1, 4, 0x0000);
    lcd_draw_rectangle(x - 11, y, 1, 4, 0x0000);
    lcd_draw_rectangle(x, y - 11, 4, 1, 0x0000);
    lcd_draw_rectangle(x, y + 10, 4, 1, 0x0000);
    lcd_draw_rectangle(x + 5, y - 2, 9, 1, 0x0000);
    lcd_draw_rectangle(x + 5, y + 1, 9, 1, 0x0000);
    lcd_draw_rectangle(x - 6, y - 2, 9, 1, 0x0000);
    lcd_draw_rectangle(x - 6, y + 1, 9, 1, 0x0000);
    lcd_draw_rectangle(x - 2, y + 6, 1, 8, 0x0000);
    lcd_draw_rectangle(x + 1, y + 6, 1, 8, 0x0000);
    lcd_draw_rectangle(x - 2, y - 6, 1, 8, 0x0000);
    lcd_draw_rectangle(x + 1, y - 6, 1, 8, 0x0000);

    //lcd_draw_rectangle(x,y,22,4,0x0000);
    //lcd_draw_rectangle(x,y,4,22,0x0000);
    lcd_draw_rectangle(x,y,20,2,0xFFFF);
    lcd_draw_rectangle(x,y,2,20,0xFFFF);
    xSemaphoreGive(Sem_LCD);
}

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
/*TODO
void Task_s2(void* pvParameters)
{
    while (true) {
        static uint8_t buttonState = 0;
        buttonState = buttonState << 1 | MKII_S2();

        if (buttonState == 0xF) S2_P = true;
        if (S2_P) hits++;
        S2_P = false;
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;
        vTaskDelay(pdMS_TO_TICKS(30));
    }
}*/

void Task_newFrame(void* pvParameters)
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
        vTaskDelay(pdMS_TO_TICKS(30));
        float lux = opt3001_read_lux();
        if (lux < 20)
            l = DARK;
        else if (lux < 75)
            l = MEDIUM;
        else
            l = BRIGHT;
        if (pl != l) {
            erase_image(&background);
            switch (l) {
            case BRIGHT:
                sky_color = 0x8718;
                draw_light_background(&background);
                break;
            case MEDIUM:
                sky_color = 0x8410;
                draw_medium_background(&background);
                break;
            case DARK:
                sky_color = 0x8;
                draw_dark_background(&background);
                break;
            }
            draw(); // TODO
        }
        pl = l;




        if(show_clay) {
            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
            // TODO Account for movement when erasing
            lcd_draw_rectangle(pcx,pcy,22,4,sky_color); // TODO Replace color with whatever color the sky is
            lcd_draw_rectangle(cx,cy,22,4,0x0000);
            lcd_draw_rectangle(cx,cy,20,2,0xFF0F);
            xSemaphoreGive(Sem_LCD);

            /* TODO
            if(sqrt(pow(x-cx, 2) + pow(y-cy, 2)) >= 40) {
                xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                // TODO Account for movement when erasing
                lcd_draw_rectangle(pcx,pcy,22,4,sky_color); // TODO Replace color with whatever color the sky is
                lcd_draw_rectangle(cx,cy,22,4,0x0000);
                lcd_draw_rectangle(cx,cy,20,2,0xFF0F);
                xSemaphoreGive(Sem_LCD);
            } else {
                draw_clay(&pidgeon, cx, cy);
            }*/


            // Update previous clay x and y
            pcx = cx;
            pcy = cy;
        }



        if(px != x || py != y) {
            draw_crosshair_basic(x, y, px, py); // TODO
        }

        /* TODO
        if(px != x || py != y) {
            if(sqrt(pow(x-cx, 2) + pow(y-cy, 2)) >= 40) {
                draw_crosshair_basic(x, y, px, py);
            } else {
                draw_crosshair(&crosshair, x, y);
            }
        }*/

        // Update previous x and y
        px = x;
        py = y;





    // TODO draw();
    }
}

void Task_joystick(void* pvParameters)
{
    while (true) {
        if ((PS2_Y_VAL == PS2_DIR_UP) && (y > (CROSSHAIR_HEIGHT / 2) + STEP_VAL + 2))
            y -= STEP_VAL;
        else if ((PS2_Y_VAL == PS2_DIR_DOWN) && (y < (SKY_BOTTOM_Y - (CROSSHAIR_HEIGHT / 2) - STEP_VAL - 1)))
            y += STEP_VAL;
        if ((PS2_X_VAL == PS2_DIR_LEFT) && (x > (CROSSHAIR_WIDTH / 2) + STEP_VAL + 1))
            x -= STEP_VAL;
        else if ((PS2_X_VAL == PS2_DIR_RIGHT) && (x < (LCD_HORIZONTAL_MAX - (CROSSHAIR_WIDTH / 2) - STEP_VAL - 1)))
            x += STEP_VAL;
        /* TODO x = x < 0 ? 0 : x > 131 ? 131
                                : x;
        y = y < 0 ? 0 : y > 131 ? 131
                                : y;*/
        /* TODO Remove
        x = x < (CROSSHAIR_WIDTH / 2) + STEP_VAL ? (CROSSHAIR_WIDTH / 2)
                                       : (x > (LCD_HORIZONTAL_MAX - (CROSSHAIR_WIDTH / 2) - STEP_VAL) ? (LCD_HORIZONTAL_MAX - (CROSSHAIR_WIDTH / 2)) : x);
        y =  ? (CROSSHAIR_HEIGHT / 2)
                                        :  ? (SKY_BOTTOM_Y - (CROSSHAIR_HEIGHT / 2)) : y);
*/
        /* TODO This worked
        draw_crosshair_basic(x, y, px, py); // TODO

        /* TODO
        if(px != x || py != y) {
            if(sqrt(pow(x-cx, 2) + pow(y-cy, 2)) >= 40) {
                draw_crosshair_basic(x, y, px, py);
            } else {
                draw_crosshair(&crosshair, x, y);
            }
        }*/


        /* TODO This worked
        // Update previous x and y
        px = x;
        py = y;*/

        // xSemaphoreTake(Sem_LCD, portMAX_DELAY);
        // TODO draw_crosshair(&crosshair, x, y);
        //draw_clay(&pidgeon, x + 15, y - 15);
        // xSemaphoreGive(Sem_LCD);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

// TODO Header and move to its own file
void Task_clayPigeon(void *pvParameters)
{
    // Boolean used to track whether the clay pigeon should move up or down
    bool move_up;
    //short crosshair_height = crosshair.y1 - crosshair.y0+1; // TODO Change to clay
    //short crosshair_width = crosshair.x1 - crosshair.x0+1; // TODO Change to clay

    while(true) {
        short x,y;
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait until task is notified to start

        move_up = true; // The clay pigeon should initially be moving up
        // TODO Use different x and y variables
        cx = LCD_HORIZONTAL_MAX / 2; // todo randomize initial x position
        cy = SKY_BOTTOM_Y - (CLAY_HEIGHT / 2) - STEP_VAL - 1; // todo replace crosshair_height with clay pigeon height
        // Initialize previous clay pigeon x and y
        pcx = cx;
        pcy = cy;

        show_clay = true;

        while(cy < SKY_BOTTOM_Y - (CLAY_HEIGHT / 2) - STEP_VAL) { // todo replace crosshair_height with clay pigeon height
            if(cy <= (CLAY_HEIGHT / 2) + STEP_VAL + 1) move_up = false;

            if(move_up) cy--; // todo y -= level #
            else cy++; // todo y += level #


            if(ACCEL_X == ACCEL_DIR_LEFT) {
                // move to the left unless the clay pigeon is already at the left boundary. in which case, stay at the boundary
                if(cx > (CLAY_WIDTH / 2) + STEP_VAL) cx -= STEP_VAL; // TODO replace crosshair_width with clay pigeon width
                // TODO else cx = 1 + CLAY_WIDTH / 2; // todo replace crosshair_width with clay pigeon width
            } else if (ACCEL_X == ACCEL_DIR_RIGHT) {
                // move to the right unless the clay pigeon is already at the right boundary. in which case, stay at the boundary
                if(cx < LCD_HORIZONTAL_MAX - (CLAY_WIDTH / 2) - STEP_VAL) cx += STEP_VAL; // todo replace crosshair_width with clay pigeon width
                // TODO else cx = LCD_HORIZONTAL_MAX - (CLAY_WIDTH / 2); // todo replace crosshair_width with clay pigeon width
            }


            /* TODO This worked
            // TODO
            xSemaphoreTake(Sem_LCD, portMAX_DELAY);
            // TODO Account for movement when erasing
            lcd_draw_rectangle(pcx,pcy,22,4,sky_color); // TODO Replace color with whatever color the sky is
            lcd_draw_rectangle(cx,cy,22,4,0x0000);
            lcd_draw_rectangle(cx,cy,20,2,0xFF0F);
            xSemaphoreGive(Sem_LCD);

            */

            /* TODO
            if(sqrt(pow(x-cx, 2) + pow(y-cy, 2)) >= 40) {
                xSemaphoreTake(Sem_LCD, portMAX_DELAY);
                // TODO Account for movement when erasing
                lcd_draw_rectangle(pcx,pcy,22,4,sky_color); // TODO Replace color with whatever color the sky is
                lcd_draw_rectangle(cx,cy,22,4,0x0000);
                lcd_draw_rectangle(cx,cy,20,2,0xFF0F);
                xSemaphoreGive(Sem_LCD);
            } else {
                draw_clay(&pidgeon, cx, cy);
            }*/


            /* TODO This worked
            // Update previous clay x and y
            pcx = cx;
            pcy = cy;*/

            // TODO draw_clay(&pidgeon,x,y); // todo replace with draw clay pigeon
            vTaskDelay(pdMS_TO_TICKS(20)); // TODO Could slow down the delay when the clay pigeon gets closer to the top of the screen/peak of its arc
        }

        show_clay = false;

        xSemaphoreTake(Sem_LCD, portMAX_DELAY);
        // TODO Account for movement when erasing
        lcd_draw_rectangle(pcx,pcy,22,4,sky_color); // TODO Replace color with whatever color the sky is
        xSemaphoreGive(Sem_LCD);

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

    Sem_LCD = xSemaphoreCreateBinary();
    add_image(&crosshair);
    add_image(&pidgeon);
    add_image(&score);
    add_image(&background);
    draw_scoreboard(&score);

    xSemaphoreGive(Sem_LCD);
    xTaskCreate(Task_clayPigeon, "pullClay", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_clayPigeon);
    xTaskCreate(TaskBlast, "blast", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_TaskBlast);
    xTaskCreate(Task_newFrame, "newFrame", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_newFrame);
    xTaskCreate(Task_joystick, "joystick", configMINIMAL_STACK_SIZE, NULL, 3, &TaskH_joystick);
    //xTaskCreate(Task_s2, "s2", configMINIMAL_STACK_SIZE, NULL, 4, &TaskH_s2);

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
