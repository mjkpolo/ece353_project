/*
 * task_blast.c
 *
 *  Created on: Apr 28, 2022
 *      Author: james
 */

#include <task_blast.h>
#include "lcd.h"

TaskHandle_t TaskH_TaskBlast;
TaskHandle_t TaskH_score;

/******************************************************************************
* This task is notified when S2 on MKII is pressed while the clay is in the
* air. It fires at the location of the crosshair, updates the score and number
* of clays hit, and plays one of two sounds on the MKII buzzer depending on
* whether or not the clay was hit (if the crosshair and clay images overlap).
******************************************************************************/
void TaskBlast(void *pvParameters)
{
    // Sound made when a target is hit
    static Note_t hit_sound[] =
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

    const int HIT_SOUND_SIZE = sizeof hit_sound / sizeof hit_sound[0];
    const int MISS_SOUND_MAX = (int)(NOTE_C * pow(2, 3.25));
    int i = 0;

    while(1)
    {
        // Wait for ISR to let us know that the button has been pressed
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Only fire if there is ammo available
        if(AMMO) {
            // Empty ammo
            AMMO = false;

            // Check if the clay pigeon and crosshair images are overlapping; if they are, the clay pigeon is hit
            if((crosshair.x0 <= pidgeon.x1) && (crosshair.x1 >= pidgeon.x0) &&
               (crosshair.y0 <= pidgeon.y1) && (crosshair.y1 >= pidgeon.y0)) {
                // Increase/Update the score by the current point value of each clay
                SCORE += CLAYS_HIT / CLAYS_PER_LEVEL + 1;
                xTaskNotifyGive(TaskH_score);

                // Increment the number of clays hit
                CLAYS_HIT++;

                // Play target hit sound
                for(i=0; i < HIT_SOUND_SIZE; i++) {
                    // Configure TimerA0 with the specified period of the PWM pulse
                    MKII_Buzzer_Init((uint32_t)floor(24000000 / (hit_sound[i].note * pow(2, hit_sound[i].octave))));
                    // Turn the buzzer on (start playing note)
                    MKII_Buzzer_On();
                    // Wait while buzzer plays the note
                    vTaskDelay(pdMS_TO_TICKS(hit_sound[i].time));
                    // Turn the buzzer off (stop playing note)
                    MKII_Buzzer_Off();
                }
            } else {
                // If lowering the score by the current point value of each clay won't make it negative, decrease/update the score
                if((SCORE - (CLAYS_HIT/CLAYS_PER_LEVEL + 1)) >= 0) {
                    SCORE -= CLAYS_HIT / CLAYS_PER_LEVEL + 1;
                    xTaskNotifyGive(TaskH_score);
                }
                // Otherwise, if the score is not 0, set it to 0
                else if(SCORE != 0) {
                    SCORE = 0;
                    xTaskNotifyGive(TaskH_score);
                }

                // Play target missed sound (upside-down exponential curve to create a decreasing tone,
                // sampled at intervals to allow each sampled frequency to be played longer without
                // extending the time for which the sound is played)
                for(i=0; i < MISS_SOUND_MAX; i+=7) {
                    // Configure TimerA0 with the specified period of the PWM pulse
                    MKII_Buzzer_Init((uint32_t) floor(24000000 / (MISS_SOUND_MAX - MISS_SOUND_MAX*pow(2.71828, (i - MISS_SOUND_MAX)/((double)MISS_SOUND_MAX)))));
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
}

