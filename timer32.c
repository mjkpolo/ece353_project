/*
 * timer32.c
 *
 *  Created on: Oct 5, 2020
 *      Author: YOUR NAME
 */
/* TODO
#include "timer32.h"
// TODO #include "main.h"

volatile bool S2_P = false; // TODO Remove
// TODO volatile bool NEW_FRAME = false;

TaskHandle_t TaskH_TaskBlast; // TODO include task_blast???

bool MKII_S2(void) {
    return (P3->IN & BIT5) == 0;
}

void t32_init(void) {
  /*
  10ms interrupt for t32_1
  *//* TODO
  uint32_t ticks = (SystemCoreClock/100) - 1;

  // Stop the timer
  TIMER32_1->CONTROL = 0;

  // Set the load register
  TIMER32_1->LOAD = ticks;

  // Enable the Timer32 interrupt in NVIC
  __enable_irq();
  NVIC_EnableIRQ(T32_INT1_IRQn);
  NVIC_SetPriority(T32_INT1_IRQn, 3);

  // Start Timer32 and enable interrupt
  TIMER32_1->CONTROL = TIMER32_CONTROL_ENABLE |   // turn timer on
                       TIMER32_CONTROL_MODE |     // periodic mode
                       TIMER32_CONTROL_SIZE |     // 32 bit timer
                       TIMER32_CONTROL_IE;        // enable interrupts
}

void T32_INT1_IRQHandler() {
    BaseType_t xHigherPriorityTaskWoken;
    static uint8_t buttonState = 0;
    buttonState = buttonState << 1 | MKII_S2();

    if (buttonState == 0x7F) {
        S2_P = true; // TODO Remove

        // Notify blast task to shoot at the crosshairs
        vTaskNotifyGiveFromISR(TaskH_TaskBlast, &xHigherPriorityTaskWoken);

        portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;
    TIMER32_1->INTCLR = BIT0;
}*/
