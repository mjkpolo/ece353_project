#include "serial_debug.h"
#include "main.h"
#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "opt3001.h"
#include "light_background.h"
#include "medium_background.h"
#include "dark_background.h"
#include "lcd.h"
#include "crosshair.h"
#include "ps2.h"
#include "timer32.h"

TaskHandle_t TaskH_joystick = NULL;
TaskHandle_t TaskH_newFrame = NULL;
TaskHandle_t TaskH_s2 = NULL;
SemaphoreHandle_t Sem_LCD = NULL;
extern image background;
extern image crosshair;
extern image crosshair2;
extern image crosshair3;
static short x = 64, y = 64;

inline void init(void)
{
    P5->DIR &= ~BIT1;
    P5->DIR &= ~BIT5;

	  Crystalfontz128x128_Init();

    adc14_init();
	  i2c_init();
	  opt3001_init();
	  serial_debug_init();
}

void Task_s2(void *pvParameters) {
	while(true) {
    static uint8_t buttonState = 0;
    buttonState = buttonState << 1 | MKII_S2();

    if (buttonState == 0x7F) S2_P = true;
		if (S2_P) printf("S2 true\r\n");
		S2_P = false;
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;
		vTaskDelay(pdMS_TO_TICKS(7));
	}
}

void Task_newFrame(void *pvParameters)
{
	while(true) {
    enum light {DARK,MEDIUM,BRIGHT,foo};
    static enum light l, pl = foo; // so pl != l
    vTaskDelay(pdMS_TO_TICKS(5));
	  float lux = opt3001_read_lux();
		if (lux < 20) l=DARK;
		else if (lux < 75) l=MEDIUM;
		else l=BRIGHT;
		if (pl != l) {
			erase_image(&background);
			switch (l) {
			  case BRIGHT :
					draw_light_background(&background);
					break;
			  case MEDIUM :
					draw_medium_background(&background);
					break;
			  case DARK :
					draw_dark_background(&background);
					break;
			}
		}
		pl = l;
		draw();
	}
}

void Task_joystick(void *pvParameters) {
	while(true) {
	  if (PS2_Y_VAL == PS2_DIR_UP) y-= 1;
	  else if (PS2_Y_VAL == PS2_DIR_DOWN) y+= 1;
	  if (PS2_X_VAL == PS2_DIR_LEFT) x-= 1;
	  else if (PS2_X_VAL == PS2_DIR_RIGHT) x+= 1;
		x = x<0 ? 0 : x>131 ? 131 : x;
		y = y<0 ? 0 : y>131 ? 131 : y;
		draw_crosshair(&crosshair,x,y);
		draw_crosshair(&crosshair2,2+x,y-40);
		draw_crosshair(&crosshair3,131-x,131-y);
    vTaskDelay(pdMS_TO_TICKS(12));
	}
}


int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    init();

    Sem_LCD = xSemaphoreCreateBinary();
		add_image(&crosshair);
		add_image(&crosshair2);
		add_image(&crosshair3);
		add_image(&background);
    xSemaphoreGive(Sem_LCD);
    xTaskCreate(Task_newFrame, "newFrame", configMINIMAL_STACK_SIZE, NULL, 1, &TaskH_newFrame);
    xTaskCreate(Task_joystick, "joystick", configMINIMAL_STACK_SIZE, NULL, 2, &TaskH_joystick);
    xTaskCreate(Task_s2, "s2", configMINIMAL_STACK_SIZE, NULL, 2, &TaskH_s2);

    vTaskStartScheduler();

    while(true);
    return 0;
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
