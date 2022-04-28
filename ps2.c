/*
 * ps2.c
 *
 *  Created on: Oct 5, 2020
 *      Author: Marco Kurzynski
 */

#include "ps2.h"

volatile uint32_t PS2_X_VAL = 0;
volatile uint32_t PS2_Y_VAL = 0;

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

    // Configure CTL0 to sample 16-times in pulsed sample mode.
    // NEW -- Indicate that this is a sequence-of-channels.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_CONSEQ_1;

    // Configure ADC to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;

    // Set high and low thresholds for joystick


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
    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;

  /* TODO __enable_irq();
  P6->SEL0 |= BIT0;
  P6->SEL1 |= BIT0;

  P4->SEL0 |= BIT4;
  P4->SEL1 |= BIT4;

  ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_CONSEQ_1;
  ADC14->CTL1 = ADC14_CTL1_RES_2;
  ADC14->MCTL[0] = ADC14_MCTLN_INCH_15;
  ADC14->MCTL[1] = ADC14_MCTLN_INCH_9 | ADC14_MCTLN_EOS;
  ADC14->IER0 = ADC14_IER0_IE1;

  NVIC_EnableIRQ(ADC14_IRQn);
  ADC14->CTL0 |= ADC14_CTL0_ON;*/
}

void ADC14_IRQHandler(void) {

    static uint8_t x_tilt_l_state = 0;
    static uint8_t x_tilt_r_state = 0;
    static uint8_t y_tilt_f_state = 0;
    static uint8_t y_tilt_b_state = 0;

    if ((ADC14->IFGR0 & ADC14_IFGR0_IFG1) != 0) {
      // TODO Maybe use a window comparator and notify the newFrame task, or maybe keep it like it is but add the new x/y values to a queue and notify the newFrame task
      uint32_t tempX = ADC14->MEM[0]; // TODO Remove; Just a temporary variable to take in joystick x
        /* TODO
      PS2_X_VAL = ADC14->MEM[0];
      if (PS2_X_VAL > VOLT_2P70) PS2_X_VAL=PS2_DIR_RIGHT;
      else if (PS2_X_VAL < VOLT_0P6) PS2_X_VAL=PS2_DIR_LEFT;
      else PS2_X_VAL=PS2_DIR_NONE;*/

      uint32_t tempY = ADC14->MEM[1]; // TODO Remove; Just a temporary variable to take in joystick y
      /* TODO PS2_Y_VAL = ADC14->MEM[1];
      if (PS2_Y_VAL > VOLT_2P70) PS2_Y_VAL=PS2_DIR_UP;
      else if (PS2_Y_VAL < VOLT_0P6) PS2_Y_VAL=PS2_DIR_DOWN;
      else PS2_Y_VAL=PS2_DIR_NONE;*/
    }
    if((ADC14->IFGR0 & ADC14_IFGR0_IFG3) != 0) {
        PS2_X_VAL = ADC14->MEM[2];

        x_tilt_r_state = x_tilt_r_state << 1; //| (PS2_X_VAL > VOLT_TILT_HI);
        if(PS2_X_VAL > VOLT_TILT_R) {
            x_tilt_r_state |= 0x0F;
        }
        x_tilt_l_state = x_tilt_l_state << 1; //| (PS2_X_VAL < VOLT_TILT_LO);
        if(PS2_X_VAL < VOLT_TILT_L) {
            x_tilt_l_state |= 0x0F;
        }

        PS2_Y_VAL = ADC14->MEM[3];

        y_tilt_f_state = y_tilt_f_state << 1 | (PS2_Y_VAL > VOLT_TILT_F);
        y_tilt_b_state = y_tilt_b_state << 1 | (PS2_Y_VAL < VOLT_TILT_B);

        if(x_tilt_r_state == 0xFF) {
            PS2_X_VAL=PS2_DIR_RIGHT;
        } else if(x_tilt_l_state == 0xFF) {
            PS2_X_VAL=PS2_DIR_LEFT;
        } else {
            PS2_X_VAL=PS2_DIR_NONE;
        }

        if(y_tilt_f_state == 0xFF) {
            PS2_Y_VAL=PS2_DIR_UP;
        } else if(y_tilt_b_state == 0xFF) {
            PS2_Y_VAL=PS2_DIR_DOWN;
        } else {
            PS2_Y_VAL=PS2_DIR_NONE;
        }

        //if (PS2_X_VAL > VOLT_TILT_RIGHT) PS2_X_VAL=PS2_DIR_RIGHT;
        //else if (PS2_X_VAL < VOLT_TILT_LEFT) PS2_X_VAL=PS2_DIR_LEFT;
        //else PS2_X_VAL=PS2_DIR_NONE;
    }
}
