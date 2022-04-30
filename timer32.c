/*
 * timer32.c
 *
 *  Created on: Oct 5, 2020
 *      Author: YOUR NAME
 */

#include "timer32.h"
#include "main.h"

volatile bool S2_P = false;
volatile bool NEW_FRAME = false;

bool MKII_S2(void)
{
    return (P3->IN & BIT5) == 0;
}

void t32_init(void)
{
    /*
    10ms interrupt for t32_1
    */
    __enable_irq();
    uint32_t ticks = (SystemCoreClock / 100) - 1;
    TIMER32_1->CONTROL = 0;
    TIMER32_1->LOAD = ticks;
    NVIC_EnableIRQ(T32_INT1_IRQn);
    TIMER32_1->CONTROL = TIMER32_CONTROL_ENABLE | TIMER32_CONTROL_MODE | TIMER32_CONTROL_SIZE | TIMER32_CONTROL_IE;

    /*
    100ms interrupt for t32_2
    */
    ticks = (SystemCoreClock / 30) - 1;
    TIMER32_2->CONTROL = 0;
    TIMER32_2->LOAD = ticks;
    NVIC_EnableIRQ(T32_INT2_IRQn);
    TIMER32_2->CONTROL = TIMER32_CONTROL_ENABLE | TIMER32_CONTROL_MODE | TIMER32_CONTROL_SIZE | TIMER32_CONTROL_IE;
}
void T32_INT1_IRQHandler()
{
    static uint8_t buttonState = 0;
    buttonState = buttonState << 1 | MKII_S2();

    if (buttonState == 0x7F)
        S2_P = true;
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;
    TIMER32_1->INTCLR = BIT0;
}

void T32_INT2_IRQHandler()
{
    NEW_FRAME = true;
    TIMER32_2->INTCLR = BIT0;
}
