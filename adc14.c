/*
 * ps2.c
 *
 *  Created on: Oct 5, 2020
 *      Author: Marco Kurzynski
 */

#include "adc14.h"

// TODO Remove any unnecessary values
volatile uint32_t PS2_X_VAL = 0;
volatile uint32_t PS2_Y_VAL = 0;
volatile uint32_t ACCEL_X = 0;
volatile uint32_t ACCEL_Y = 0;

TaskHandle_t TaskH_crosshairBottomHalf;
TaskHandle_t TaskH_clayPigeon;
TaskHandle_t TaskH_accelerometerXBottomHalf;

SemaphoreHandle_t Sem_ClayLaunched;

/******************************************************************************
* Initialize ADC14
******************************************************************************/
void adc14_init(void) {
    // Configure the X direction of the joystick as an analog input pin.
    P6->SEL0 |= BIT0;
    P6->SEL1 |= BIT0;
    // Configure the Y direction of the joystick as an analog input pin.
    P4->SEL0 |= BIT4;
    P4->SEL1 |= BIT4;
    // Configure the X direction of the accelerometer as an analog input pin
    P6->SEL0 |= BIT1;
    P6->SEL1 |= BIT1;
    // Configure the Y direction of the accelerometer as an analog input pin
    P4->SEL0 |= BIT0;
    P4->SEL1 |= BIT0;

    // Configure CTL0 to sample 16-times in pulsed sample mode. This is a sequence-of-channels.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_CONSEQ_1;

    // Configure ADC to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;

    // Associate the X direction analog signal with MEM[0]
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_15;
    // Associate the Y direction analog signal with MEM[1]
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_9;
    // Associate the accelerometer X direction analog signal with MEM[2]
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_14;
    // Associate the accelerometer X direction analog signal with MEM[2]
    // This is the end of a sequence.
    ADC14->MCTL[3] = ADC14_MCTLN_INCH_13 | ADC14_MCTLN_EOS;

    // Enable interrupts in the ADC AFTER a value is written into MEM[1] or MEM[3].
    ADC14->IER0 = ADC14_IER0_IE3;

    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);
    // Set ADC Interrupt priority. Priority is greater than 2 to ensure it doesn't interrupt the FreeRTOS scheduler
    NVIC_SetPriority(ADC14_IRQn, 3); // TODO Change to 3 since t32 is removed
    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;
}

/******************************************************************************
* Top Half of ADC14 Handler. Gets the PS2 and accelerometer values and
* notifies the crosshairBottomHalf, accelerometerXBottomHalf, and clayPigeon
* tasks.
******************************************************************************/
void ADC14_IRQHandler(void) {
    BaseType_t xHigherPriorityTaskWoken;
    BaseType_t status;

    static uint8_t y_tilt_f_state = 0;
    static uint8_t y_tilt_b_state = 0;

    // Get x position of the joystick
    PS2_X_VAL = ADC14->MEM[0];
    // Get y position of the joystick
    PS2_Y_VAL = ADC14->MEM[1];

    // Notify the crosshair task to update the crosshair's movement based on the joystick values
    vTaskNotifyGiveFromISR(TaskH_crosshairBottomHalf, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

    // Get accelerator x value
    ACCEL_X = ADC14->MEM[2];

    // TODO move this to the bottom of the ISR and rework the logic so that the tasks are only notified at appropriate times (when the clay is either in the air or not yet launched)
    // Notify bottom half task to update the clay pigeon's x movement direction
    vTaskNotifyGiveFromISR(TaskH_accelerometerXBottomHalf, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

    // Get accelerometer y value
    ACCEL_Y = ADC14->MEM[3];

    // "Debounce" accelerometer y value to filter out readings from shaking the board
    y_tilt_f_state = y_tilt_f_state << 1 | (ACCEL_Y > VOLT_TILT_F);
    y_tilt_b_state = y_tilt_b_state << 1 | (ACCEL_Y < VOLT_TILT_B);

    // Launch clay pigeon when the user tilts the board forward
    if(y_tilt_f_state == 0x7F) {
        // Notify clay pigeon task to pull clay pigeon
        vTaskNotifyGiveFromISR(TaskH_clayPigeon, &xHigherPriorityTaskWoken);

        portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
    // Reload once when the user tilts the board backward
    else if(y_tilt_b_state == 0x7F) {
        // Try to take Sem_ClayLaunched to check if the clay is currently in the air
        status = xSemaphoreTakeFromISR(Sem_ClayLaunched, &xHigherPriorityTaskWoken); // TODO Change to reloading semaphore

        if(status == pdPASS) // The clay is not in the air (status == pdPASS), so just give the semaphore back and don't reload
            xSemaphoreGiveFromISR(Sem_ClayLaunched, &xHigherPriorityTaskWoken);
        else if(!AMMO) // The clay is in the air and there is no ammo, so reload
            AMMO = true; // Reload ammo
    }

}
