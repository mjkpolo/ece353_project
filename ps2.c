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
  __enable_irq();
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
  ADC14->CTL0 |= ADC14_CTL0_ON;
}

void ADC14_IRQHandler(void) {
  PS2_X_VAL = ADC14->MEM[0];
  if (PS2_X_VAL > VOLT_2P70) PS2_X_VAL=PS2_DIR_RIGHT;
  else if (PS2_X_VAL < VOLT_0P6) PS2_X_VAL=PS2_DIR_LEFT;
  else PS2_X_VAL=PS2_DIR_NONE;

  PS2_Y_VAL = ADC14->MEM[1];
  if (PS2_Y_VAL > VOLT_2P70) PS2_Y_VAL=PS2_DIR_UP;
  else if (PS2_Y_VAL < VOLT_0P6) PS2_Y_VAL=PS2_DIR_DOWN;
  else PS2_Y_VAL=PS2_DIR_NONE;
}
