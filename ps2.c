/*
 * ps2.c
 *
 *  Created on: Oct 5, 2020
 *      Author: Marco Kurzynski
 */

#include "ps2.h"

volatile uint32_t PS2_X_VAL = 0;
volatile uint32_t PS2_Y_VAL = 0;
volatile uint32_t ACCEL_X = 0;
volatile uint32_t ACCEL_Y = 0;

TaskHandle_t TaskH_crosshair; // TODO
TaskHandle_t TaskH_clayPigeon; // TODO

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
    // TODO Remove: This is the end of a sequence.
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_9;// | ADC14_MCTLN_EOS; // TODO NO: Keep EOS from before ????
    // Associate the accelerometer X direction analog signal with MEM[2]
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_14;
    // Associate the accelerometer X direction analog signal with MEM[2]
    // This is the end of a sequence.
    ADC14->MCTL[3] = ADC14_MCTLN_INCH_13 | ADC14_MCTLN_EOS; // TODO EOS ????

    // Enable interrupts in the ADC AFTER a value is written into MEM[1] or MEM[3].
    ADC14->IER0 = ADC14_IER0_IE3; // TODO Remove: ADC14_IER0_IE1 | ADC14_IER0_IE3;

    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);
    // Set ADC Interrupt priority. Priority is greater than 2 to ensure it doesn't interrupt the FreeRTOS scheduler
    NVIC_SetPriority(ADC14_IRQn, 4);
    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;
}

void ADC14_IRQHandler(void) {
    BaseType_t xHigherPriorityTaskWoken;
    BaseType_t status;
    MOVE_t ps2_move;
    MOVE_DIR accelerometer_x;

    static uint8_t x_tilt_l_state = 0;
    static uint8_t x_tilt_r_state = 0;
    static uint8_t y_tilt_f_state = 0;
    static uint8_t y_tilt_b_state = 0;

    // TODO Add ADC14_IER0_IE1 | Above again????
    // TODO if ((ADC14->IFGR0 & ADC14_IFGR0_IFG1) != 0) {

      // TODO Maybe use a window comparator and notify the newFrame task, or maybe keep it like it is but add the new x/y values to length 1 queues and notify the newFrame task

      // Get x position of joystick and set ps2_move.x accordingly
      PS2_X_VAL = ADC14->MEM[0];
      if (PS2_X_VAL > VOLT_2P70)
          ps2_move.x = RIGHT;
      else if (PS2_X_VAL < VOLT_0P6)
          ps2_move.x = LEFT;
      else
          ps2_move.x = NO_MOVE;

      // Get y position of joystick and set ps2_move.y accordingly
      PS2_Y_VAL = ADC14->MEM[1];
      if (PS2_Y_VAL > VOLT_2P70)
          ps2_move.y = UP;
      else if (PS2_Y_VAL < VOLT_0P6)
          ps2_move.y = DOWN;
      else
          ps2_move.y = NO_MOVE;

      // Add joystick's x and y positions to queue for crosshair task
      // TODO Remove: status = xQueueSendToBack(Queue_LED, &msg, portMAX_DELAY);
      // TODO status = xQueueOverwriteFromISR(Queue_PS2, &ps2_move, &xHigherPriorityTaskWoken);

      // TODO Queue send to front ??? Use send to back instead of just send???
      status = xQueueSendFromISR(Queue_PS2, &ps2_move, &xHigherPriorityTaskWoken); // TODO
      //status = xQueueSendToBack(Queue_PS2, &ps2_move, portMAX_DELAY); // TODO


      // TODO Is this necessary to follow the project specifications??????????
      vTaskNotifyGiveFromISR(TaskH_crosshair, &xHigherPriorityTaskWoken);

      portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

    //}

    // TODO if((ADC14->IFGR0 & ADC14_IFGR0_IFG3) != 0) {

        // Debounce accelerometer x value to filter out readings from shaking the board
        ACCEL_X = ADC14->MEM[2];

        // TODO Make this the same as tilting forward/backward (or make those the same as this)???
        // TODO Instead of having two separate values that go from 0x0F to 0xFF, have one value that goes from 0x0F to 0xFF (left) or 0x00 (right)
        x_tilt_r_state = x_tilt_r_state << 1; //| (PS2_X_VAL > VOLT_TILT_HI);
        if(ACCEL_X > VOLT_TILT_R) {
            x_tilt_r_state |= 0x0F;
        }
        x_tilt_l_state = x_tilt_l_state << 1; //| (PS2_X_VAL < VOLT_TILT_LO);
        if(ACCEL_X < VOLT_TILT_L) {
            x_tilt_l_state |= 0x0F;
        }

        // Debounce accelerometer y value to filter out readings from shaking the board
        ACCEL_Y = ADC14->MEM[3];

        y_tilt_f_state = y_tilt_f_state << 1 | (ACCEL_Y > VOLT_TILT_F);
        y_tilt_b_state = y_tilt_b_state << 1 | (ACCEL_Y < VOLT_TILT_B);

        // Set accelerometer_x according to the x orientation of the accelerometer
        if(x_tilt_r_state == 0xFF) {
            accelerometer_x = RIGHT;
            // TODO Remove: ACCEL_X = ACCEL_DIR_RIGHT;
        } else if(x_tilt_l_state == 0xFF) {
            // TODO Remove: ACCEL_X = ACCEL_DIR_LEFT;
            accelerometer_x = LEFT;
        } else {
            // TODO Remove: ACCEL_X = ACCEL_DIR_NONE;
            accelerometer_x = NO_MOVE;
        }

        // Add accelerometer's x position (left/right/middle) to queue for clay pigeon task
        // TODO Remove: status = xQueueSendToBack(Queue_LED, &msg, portMAX_DELAY);
        // TODO status = xQueueOverwriteFromISR(Queue_Accelerometer, &accelerometer_x, &xHigherPriorityTaskWoken);

        // TODO Queue send to front ??? Use send to back instead of just send???
        status = xQueueSendFromISR(Queue_Accelerometer, &accelerometer_x, &xHigherPriorityTaskWoken); // TODO

        // Launch clay pigeon when the user tilts the board forward
        if(y_tilt_f_state == 0x7F) {
            // Notify clay pigeon task to pull clay pigeon
            vTaskNotifyGiveFromISR(TaskH_clayPigeon, &xHigherPriorityTaskWoken);

            portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        }
        // Only reload once when the user tilts the board backward
        // TODO Add something so it doesn't reload when ammo supply is full
        else if(y_tilt_b_state == 0x7F) {
            // TODO Reload cartridge
        }

    //}
}
