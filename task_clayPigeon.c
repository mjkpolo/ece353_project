/*
 * task_clayPigeon.c
 *
 *  Created on: Apr 30, 2022
 *      Author: james
 */

QueueHandle_t Queue_Accelerometer;

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

            if(move_up) y--; // todo y -= level #
            else y++; // todo y += level #

            /* ADD CODE
             * Wait until we receive a message from the Queue_LED
             */
            // TODO status = xQueueReceive(Queue_, &msg, portMAX_DELAY);

            if(ACCEL_X == ) {
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


