/*
 * task_crosshair.c
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

#include "task_crosshair.h"
#include "lcd.h"
#include "adc14.h"

TaskHandle_t TaskH_crosshairBottomHalf;
TaskHandle_t TaskH_drawCrosshair;
MOVE_t crosshair_move;

// TODO header. Also, Task_crosshairBottomHalf
void Task_crosshairBottomHalf(void* pvParameters)
{
    BaseType_t status;

    while (true) {
        // Wait until task is notified to start by ADC14 ISR
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Update the x and y movements of the crosshair
        if (PS2_X_VAL > VOLT_2P70)
            crosshair_move.x = RIGHT;
        else if (PS2_X_VAL < VOLT_0P6)
            crosshair_move.x = LEFT;
        else
            crosshair_move.x = NO_MOVE;

        if (PS2_Y_VAL > VOLT_2P70)
            crosshair_move.y = UP;
        else if (PS2_Y_VAL < VOLT_0P6)
            crosshair_move.y = DOWN;
        else
            crosshair_move.y = NO_MOVE;
    }
}

// TODO header
void Task_drawCrosshair(void* pvParameters) {
    const short CROSSHAIR_HEIGHT = crosshair.y1 - crosshair.y0 + 1; // Height of the crosshair image
    const short CROSSHAIR_WIDTH = crosshair.x1 - crosshair.x0 + 1; // Width of the crosshair image
    short px, py; // x and y positions of the crosshair

    crosshair_move.x = NO_MOVE;
    crosshair_move.y = NO_MOVE;

    // Draw crosshair for the first time
    draw_crosshair(&crosshair, crosshair_x, crosshair_y);

    while(true) {
        px = crosshair_x;
        py = crosshair_y;

        // TODO Just use if statements
        switch(crosshair_move.y) {
            case UP:
                // Make sure the crosshair doesn't go past the top boundary of the screen
                if (crosshair_y > (CROSSHAIR_HEIGHT / 2) + 1)
                    crosshair_y --;
                break;
            case DOWN:
                // Make sure the crosshair doesn't go past the bottom boundary of the screen
                if(crosshair_y < (LCD_VERTICAL_MAX - (CROSSHAIR_HEIGHT / 2) - 1))
                    crosshair_y ++;
                break;
        }
        switch(crosshair_move.x) {
            case LEFT:
                // Make sure the crosshair doesn't go past the left boundary of the screen
                if(crosshair_x > (CROSSHAIR_WIDTH / 2) + 1)
                    crosshair_x --;
                break;
            case RIGHT:
                // Make sure the crosshair doesn't go past the right boundary of the screen
                if(crosshair_x < (LCD_HORIZONTAL_MAX - (CROSSHAIR_WIDTH / 2) - 1))
                    crosshair_x ++;
                break;
        }

        if(crosshair_x != px || crosshair_y != py) {
            // Redraw the crosshair
            draw_crosshair(&crosshair, crosshair_x, crosshair_y);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
