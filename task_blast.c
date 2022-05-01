/*
 * task_blast.c
 *
 *  Created on: Apr 28, 2022
 *      Author: james
 */

#include <task_blast.h>
#include "lcd.h" // TODO

TaskHandle_t TaskH_TaskBlast; // TODO Is this necessary/useful??

QueueHandle_t Queue_Score;

// TODO Remove? Play a note for the given duration
void play_note(uint32_t period, uint16_t ms_time)
{
    // Configure TimerA0 with the specified period of the PWM pulse
    MKII_Buzzer_Init(period);
    // Turn the buzzer on (start playing note)
    MKII_Buzzer_On();
    // Wait while buzzer plays the note
    vTaskDelay(pdMS_TO_TICKS(ms_time));
    // Turn the buzzer off (stop playing note)
    MKII_Buzzer_Off();
}


/******************************************************************************
* Prints a message to the Console
******************************************************************************/
void TaskBlast(void *pvParameters)
{
    // TODO BaseType_t status;
    BaseType_t xHigherPriorityTaskWoken;

    /*
    Note_t sound_byte[] =
    {
        {NOTE_B, 1, 7},
        {NOTE_AS, 1, 7},
        {NOTE_B, 1, 7},
        {NOTE_A, 1, 7},
        {NOTE_AS, 1, 7},
        {NOTE_GS, 1, 7},
        {NOTE_A, 1, 7},
        {NOTE_G, 1, 7},
        {NOTE_GS, 1, 7},
        {NOTE_F, 1, 7},
        {NOTE_FS, 1, 7},
        {NOTE_E, 1, 7},
        {NOTE_F, 1, 7},
        {NOTE_DS, 1, 7},
        {NOTE_E, 1, 7},
        {NOTE_D, 1, 7},
        {NOTE_DS, 1, 7},
        {NOTE_CS, 1, 7},
        {NOTE_C, 1, 7},
        {NOTE_B, 0, 7},
        {NOTE_AS, 0, 7},
        {NOTE_B, 0, 7},
        {NOTE_AS, 0, 7},
        {NOTE_A, 0, 7},
        {NOTE_AS, 0, 7},
        {NOTE_A, 0, 7},
        {NOTE_GS, 0, 7},
        {NOTE_A, 0, 7},
        {NOTE_GS, 0, 7},
        {NOTE_G, 0, 7},
        {NOTE_GS, 0, 7},
        {NOTE_G, 0, 7},
        {NOTE_FS, 0, 7},
        {NOTE_G, 0, 7},
    };*/


    /*TODO Okay
    Note_t sound_byte[] =
    {
        {NOTE_B, 1, 15},
        {NOTE_AS, 1, 15},
        {NOTE_B, 1, 15},
        {NOTE_F, 1, 15},
        {NOTE_A, 1, 15},
        {NOTE_D, 1, 15},
        {NOTE_A, 0, 15},
        {NOTE_C, 1, 15},
        {NOTE_F, 0, 15},
        {NOTE_D, 0, 15},
        {NOTE_C, 0, 20},
    };

    Note_t sound_byte2[] =
    {
        {NOTE_B, 3, 15},
        {NOTE_AS, 3, 15},
        {NOTE_B, 3, 15},
        {NOTE_F, 3, 15},
        {NOTE_A, 3, 15},
        {NOTE_D, 3, 15},
        {NOTE_A, 2, 15},
        {NOTE_C, 3, 15},
        {NOTE_F, 2, 15},
        {NOTE_G, 2, 15},
        {NOTE_D, 2, 15},
    };*/

    /* TODO Remove: Sound made when a target is missed
    Note_t sound_byte[] =
    {
        {NOTE_B, 1, 10},
        {NOTE_AS, 1, 10},
        {NOTE_B, 1, 10},
        {NOTE_GS, 1, 5},
        {NOTE_F, 1, 10},
        {NOTE_G, 1, 5},
        {NOTE_A, 1, 10},
        {NOTE_FS, 1, 5},
        {NOTE_D, 1, 10},
        {NOTE_B, 0, 5},
        {NOTE_A, 0, 10},
        {NOTE_B, 0, 5},
        {NOTE_C, 1, 10},
        {NOTE_A, 0, 5},
        {NOTE_F, 0, 7},
        {NOTE_DS, 0, 5},
        {NOTE_D, 0, 7},
        {NOTE_CS, 0, 10},
        {NOTE_C, 0, 25},
    };/*
    Note_t sound_byte[] =
    {
        {NOTE_B, 5, 50},
        //{NOTE_D, 11, 1},
        {NOTE_AS, 5, 50},
        {NOTE_A, 5, 50},
        //{NOTE_D, 11, 1},
        //{NOTE_A, 12, 1},
        //{NOTE_C, 11, 1},
        {NOTE_C, 0, 25},
    };*/

    // Sound made when a target is hit
    Note_t hit_sound[] =
    {
        {NOTE_B, 3, 10},
        {NOTE_AS, 3, 10},
        {NOTE_B, 3, 10},
        {NOTE_GS, 3, 5},
        {NOTE_F, 3, 10},
        {NOTE_G, 3, 5},
        {NOTE_A, 3, 10},
        {NOTE_FS, 3, 5},
        {NOTE_D, 3, 10},
        {NOTE_B, 2, 5},
        {NOTE_A, 2, 10},
        {NOTE_B, 2, 5},
        {NOTE_C, 3, 10},
        {NOTE_A, 2, 5},
        {NOTE_F, 2, 10},
        {NOTE_DS, 2, 5},
        {NOTE_D, 2, 10},
        {NOTE_CS, 2, 5},
        {NOTE_DS, 2, 20},
    };

    int hit_sound_size = sizeof hit_sound / sizeof hit_sound[0];
    int i = 0;
    int max = (int)(NOTE_C * pow(2, 3.25)); // TODO Replace with constant value

    uint8_t points = 1; // TODO Set points to whatever level we're on
    BaseType_t status;

    while(1)
    {
        // Wait for ISR to let us know that the button has been pressed
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Check if the clay pigeon and crosshair images are overlapping; if they are, the clay pigeon is hit
        if((crosshair.x0 <= pidgeon.x1) && (crosshair.x1 >= pidgeon.x0) &&
           (crosshair.y0 <= pidgeon.y1) && (crosshair.y1 >= pidgeon.y0)) {

            // Add the points for hitting the target to Queue_Score so that the scoreboard can be updated
            status = xQueueSendToBack(Queue_Score, &points, portMAX_DELAY);

            // Play target hit sound
            for(i=0; i < hit_sound_size; i++) {

                // TODO Either use play_note() here or remove play_note() entirely
                // TODO Use SystemClock instead of 24000000.0

                // Configure TimerA0 with the specified period of the PWM pulse
                MKII_Buzzer_Init((uint32_t)floor(24000000.0/(hit_sound[i].note * pow(2, hit_sound[i].octave))));
                // Turn the buzzer on (start playing note)
                MKII_Buzzer_On();
                // Wait while buzzer plays the note
                vTaskDelay(pdMS_TO_TICKS(hit_sound[i].time));
                // Turn the buzzer off (stop playing note)
                MKII_Buzzer_Off();
            }
        } else {
            // Play target missed sound (upside-down exponential curve to create a decreasing tone, sampled at intervals to allow each sampled frequency to be played longer without extending the time for which the sound is played)
            for(i=0; i < max; i+=7) {

                // TODO Either use play_note() here or remove play_note() entirely
                // TODO Use SystemClock instead of 24000000.0

                // Configure TimerA0 with the specified period of the PWM pulse
                MKII_Buzzer_Init((uint32_t) floor(24000000.0 / (max - max*pow(2.71828, (i - max)/((double)max)))));
                // Turn the buzzer on (start playing note)
                MKII_Buzzer_On();
                // Wait while buzzer plays the note
                vTaskDelay(pdMS_TO_TICKS(5));
                // Turn the buzzer off (stop playing note)
                MKII_Buzzer_Off();
            }
        }
    }
}

