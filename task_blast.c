/*
 * task_blast.c
 *
 *  Created on: Apr 28, 2022
 *      Author: james
 */

#include <task_blast.h>
#include "lcd.h" // TODO

TaskHandle_t TaskH_TaskBlast;
TaskHandle_t TaskH_score;

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

                // TODO Does the changing order of these two change much???

                // Update the score
                SCORE += CLAYS_HIT / CLAYS_PER_LEVEL + 1;
                xTaskNotifyGive(TaskH_score);

                // Increment the number of clays hit
                CLAYS_HIT++;

                // Play target hit sound
                for(i=0; i < hit_sound_size; i++) {

                    // TODO Either use play_note() here or remove play_note() entirely

                    // Configure TimerA0 with the specified period of the PWM pulse
                    MKII_Buzzer_Init((uint32_t)floor(SystemCoreClock / (hit_sound[i].note * pow(2, hit_sound[i].octave)))); // TODO Change SystemCoreClock to 24000000
                    // Turn the buzzer on (start playing note)
                    MKII_Buzzer_On();
                    // Wait while buzzer plays the note
                    vTaskDelay(pdMS_TO_TICKS(hit_sound[i].time * SystemCoreClock / 24000000)); // TODO Remove or set to constant 2 multiplier
                    // Turn the buzzer off (stop playing note)
                    MKII_Buzzer_Off();
                }
            } else {
                // Play target missed sound (upside-down exponential curve to create a decreasing tone, sampled at intervals to allow each sampled frequency to be played longer without extending the time for which the sound is played)
                for(i=0; i < max; i+=7) {

                    // TODO Either use play_note() here or remove play_note() entirely

                    // Configure TimerA0 with the specified period of the PWM pulse
                    MKII_Buzzer_Init((uint32_t) floor(SystemCoreClock / (max - max*pow(2.71828, (i - max)/((double)max)))));
                    // Turn the buzzer on (start playing note)
                    MKII_Buzzer_On();
                    // Wait while buzzer plays the note
                    vTaskDelay(pdMS_TO_TICKS(5 * SystemCoreClock / 24000000)); // TODO Remove or set to constant 2 multiplier
                    // Turn the buzzer off (stop playing note)
                    MKII_Buzzer_Off();
                }
            }
        }
    }
}

