/*
 * task_blast.c
 *
 *  Created on: Apr 28, 2022
 *      Author: james
 */

#include <task_blast.h>

TaskHandle_t TaskH_TaskBlast;
TaskHandle_t TaskH_updateBackground;

// TODO Play a note for the given duration
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

    // Sound made when a target is missed
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
        {NOTE_F, 0, 10},
        {NOTE_DS, 0, 5},
        {NOTE_D, 0, 10},
        {NOTE_CS, 0, 5},
        {NOTE_C, 0, 20},
    };

    // Sound made when a target is hit
    Note_t sound_byte2[] =
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

    int arrSize = sizeof sound_byte / sizeof sound_byte[0];
    int arrSize2 = sizeof sound_byte2 / sizeof sound_byte2[0];
    int i=0; // TODO

    while(1)
    {
        // Wait for ISR to let us know that the button has been pressed
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Play target missed sound
        for(i=0; i < arrSize; i++) {
            // Configure TimerA0 with the specified period of the PWM pulse
            MKII_Buzzer_Init((uint32_t)floor(24000000.0/(sound_byte[i].note * pow(2,sound_byte[i].octave))));
            // Turn the buzzer on (start playing note)
            MKII_Buzzer_On();
            // Wait while buzzer plays the note
            vTaskDelay(pdMS_TO_TICKS(sound_byte[i].time));
            // Turn the buzzer off (stop playing note)
            MKII_Buzzer_Off();
        }

        vTaskDelay(pdMS_TO_TICKS(500));

        // Play target hit sound
        for(i=0; i < arrSize2; i++) {
            // Configure TimerA0 with the specified period of the PWM pulse
            MKII_Buzzer_Init((uint32_t)floor(24000000.0/(sound_byte2[i].note * pow(2,sound_byte2[i].octave))));
            // Turn the buzzer on (start playing note)
            MKII_Buzzer_On();
            // Wait while buzzer plays the note
            vTaskDelay(pdMS_TO_TICKS(sound_byte2[i].time));
            // Turn the buzzer off (stop playing note)
            MKII_Buzzer_Off();
        }

        // Notify blast task to shoot at the crosshairs
        xTaskNotifyGive(TaskH_updateBackground);
                // TODO vTaskNotifyGive(TaskH_updateBackground, &xHigherPriorityTaskWoken);

                // TODO portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        // TODO Sounds MKII buzzer for shot and shoot
        //draw_light_background();
    }
}

