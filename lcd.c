/*
 * lcd.c
 *
 *  Created on: Sep 11, 2020
 *      Author: Joe Krachey
 */

#include "lcd.h"

extern SemaphoreHandle_t Sem_Background;
SemaphoreHandle_t Sem_Erase;
extern QueueHandle_t Draw_Queue;

/* ****************************************************************************
 * Used to configure the 5 pins that control the LCD interface on the MKII.
 *
 * CLK and MOSI will be configured as their Primary Module Function
 *
 * CS, C/D, and RST will be configured at output pins
 ******************************************************************************/
void HAL_LCD_PortInit(void)
{
    // ADD CODE

    // LCD_SCK
    LCD_SCK_PORT->SEL0 |= LCD_SCK_PIN;
    LCD_SCK_PORT->SEL1 &= ~LCD_SCK_PIN;

    // LCD_MOSI
    LCD_MOSI_PORT->SEL0 |= LCD_MOSI_PIN;
    LCD_MOSI_PORT->SEL1 &= ~LCD_MOSI_PIN;

    // LCD_CS
    LCD_CS_PORT->DIR |= LCD_CS_PIN;

    // LCD_RST
    LCD_RST_PORT->DIR |= LCD_RST_PIN;

    // LCD_RS
    LCD_DC_PORT->DIR |= LCD_DC_PIN;
}

/* ****************************************************************************
 * Used to configure the eUSCIB Interface as a 3-Wire SPI Interface
 *
 ******************************************************************************/
void HAL_LCD_SpiInit(void)
{
    EUSCI_B0->CTLW0 = EUSCI_B_CTLW0_SWRST; // Put eUSCI state machine in reset

    // ADD CODE to define the behavior of the eUSCI_B0 as a SPI interface
    EUSCI_B0->CTLW0 = EUSCI_B_CTLW0_CKPH | // Phase 1
        EUSCI_B_CTLW0_MSB | // Msb first
        EUSCI_B_CTLW0_MST | // Set as SPI master
        EUSCI_B_CTLW0_MODE_0 | // 3 pin spi mode
        EUSCI_B_CTLW0_SYNC | // async
        EUSCI_B_CTLW0_SSEL__SMCLK | // smclk
        // EUSCI_B_CTLW0_STEM | //UCxSTE digital output
        EUSCI_B_CTLW0_SWRST; // remain in eusci mode

    // ADD CODE to set the SPI Clock to 12MHz.
    //
    // Divide clock speed by 2 (24MHz/2) = 12 MHz
    // fBitClock = fBRCLK/(UCBRx+1).
    EUSCI_B0->BRW = 1;

    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // Initialize USCI state machine

    // set the chip select low
    // The chip select will be held low forever!  There is only 1 device (LCD)
    // connected to the SPI device, so we will leave it activated all the time.
    LCD_CS_PORT->OUT &= ~LCD_CS_PIN;

    // Set the DC pin high (put it in data mode)
    LCD_DC_PORT->OUT |= LCD_DC_PIN;
}

//*****************************************************************************
//
// Writes a command to the CFAF128128B-0145T.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void HAL_LCD_writeCommand(uint8_t command)
{
    // ADD CODE

    // Set to command mode -- DC PIN Set to 0
    LCD_DC_PORT->OUT &= ~LCD_DC_PIN;

    // Busy wait while the data is being transmitted. Check the STATW register and see if it is busy
    while (EUSCI_B0->STATW & UCBUSY)
        ;

    // Transmit data
    EUSCI_B0->TXBUF = command;

    // Busy wait while the data is being transmitted. Check the STATW register and see if it is busy
    while (EUSCI_B0->STATW & UCBUSY)
        ;

    // Set back to data mode, set the DC pin high
    LCD_DC_PORT->OUT |= LCD_DC_PIN;
}

//*****************************************************************************
//
// Writes a data to the CFAF128128B-0145T.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void HAL_LCD_writeData(uint8_t data)
{
    while (EUSCI_B0->STATW & UCBUSY)
        ;
    EUSCI_B0->TXBUF = data;
    while (EUSCI_B0->STATW & UCBUSY)
        ;
}

//*****************************************************************************
// Code adapted from TI LCD driver library
//*****************************************************************************
void Crystalfontz128x128_SetDrawFrame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{

    // ADD CODE
    // Write the CM_CASET command followed by the 4 bytes of data
    // used to set the Column start and end rows.
    HAL_LCD_writeCommand(CM_CASET);
    HAL_LCD_writeData(x0 >> 8);
    HAL_LCD_writeData(x0);
    HAL_LCD_writeData(x1 >> 8);
    HAL_LCD_writeData(x1);

    // ADD CODE
    // Write the CM_RASET command followed by the 4 bytes of data
    // used to set the Row start and end rows.
    HAL_LCD_writeCommand(CM_RASET);
    HAL_LCD_writeData(y0 >> 8);
    HAL_LCD_writeData(y0);
    HAL_LCD_writeData(y1 >> 8);
    HAL_LCD_writeData(y1);
}

//*****************************************************************************
// Code adapted from TI LCD driver library
//
//! Initializes the display driver.
//!
//! This function initializes the ST7735 display controller on the panel,
//! preparing it to display data.
//!
//! \return None.
//
//*****************************************************************************
void Crystalfontz128x128_Init(void)
{
    int i;
    int j;
    uint8_t upper8 = 0x00;
    uint8_t lower8 = 0x00;

    HAL_LCD_PortInit();
    HAL_LCD_SpiInit();

    LCD_RST_PORT->OUT &= ~LCD_RST_PIN;
    HAL_LCD_delay(50);

    LCD_RST_PORT->OUT |= LCD_RST_PIN;
    HAL_LCD_delay(120);

    HAL_LCD_writeCommand(CM_SLPOUT);
    HAL_LCD_delay(200);

    HAL_LCD_writeCommand(CM_GAMSET);
    HAL_LCD_writeData(0x04);

    HAL_LCD_writeCommand(CM_SETPWCTR);
    HAL_LCD_writeData(0x0A);
    HAL_LCD_writeData(0x14);

    HAL_LCD_writeCommand(CM_SETSTBA);
    HAL_LCD_writeData(0x0A);
    HAL_LCD_writeData(0x00);

    HAL_LCD_writeCommand(CM_COLMOD);
    HAL_LCD_writeData(0x05);
    HAL_LCD_delay(10);

    HAL_LCD_writeCommand(CM_MADCTL);
    HAL_LCD_writeData(CM_MADCTL_MX | CM_MADCTL_MY | CM_MADCTL_BGR);

    HAL_LCD_writeCommand(CM_NORON);

    Crystalfontz128x128_SetDrawFrame(0, 0, LCD_HORIZONTAL_MAX, LCD_VERTICAL_MAX);
    HAL_LCD_writeCommand(CM_RAMWR);

    for (i = 0; i < LCD_VERTICAL_MAX; i++) {

        for (j = 0; j < LCD_HORIZONTAL_MAX; j++) {
            HAL_LCD_writeData(upper8);
            HAL_LCD_writeData(lower8);
        }
    }

    HAL_LCD_delay(10);

    HAL_LCD_writeCommand(CM_DISPON);

    HAL_LCD_writeCommand(CM_MADCTL);
    HAL_LCD_writeData(CM_MADCTL_MX | CM_MADCTL_MY | CM_MADCTL_BGR);
}

image pidgeon, score, crosshair, background, end_splash;
static image** images = NULL;
static size_t numImages = 0;

size_t add_image(image* i)
{
    i->inQueue = false;
    images = realloc(images, (numImages + 1) * sizeof(image*));
    images[numImages++] = i;
    i->layers = NULL;
    return numImages;
}

void erase_image(image* image)
{
    xSemaphoreTake(Sem_Erase, portMAX_DELAY);
    image->numLayers = 0;
    if (image->layers) free(image->layers);
    image->layers = NULL;
    image->x0 = 132;
    image->y0 = 132;
    image->x1 = 0;
    image->y1 = 0;
    xSemaphoreGive(Sem_Erase);

    if (image->inQueue ? false : image->moving) {
        xQueueSendToBack(Draw_Queue,&image,portMAX_DELAY);
        image->inQueue = true;
    }
}

void fill_image(image* image, layer* layers, size_t numLayers, bool moving)
{
    image->layers = (layer*)realloc(image->layers, (image->numLayers + numLayers) * sizeof(layer));
    memcpy(&image->layers[image->numLayers], layers, sizeof(layer) * numLayers);
    image->numLayers += numLayers;
    image->moving = moving;
    int i;
    for (i = 0; i < numLayers; i++) {
        image->x0 = image->x0 < layers[i].x0 ? image->x0 : layers[i].x0;
        image->y0 = image->y0 < layers[i].y0 ? image->y0 : layers[i].y0;
        image->x1 = image->x1 > layers[i].x1 ? image->x1 : layers[i].x1;
        image->y1 = image->y1 > layers[i].y1 ? image->y1 : layers[i].y1;
    }
    if (!image->inQueue) {
        xQueueSendToBack(Draw_Queue,&image,portMAX_DELAY);
        image->inQueue = true;
    }
}

bool draw_pixel(image* image, short i, short j)
{
    int k;
    for (k = 0; k < image->numLayers; k++) {
        short image_width = image->layers[k].x1 - image->layers[k].x0 + 1;
        short image_height = image->layers[k].y1 - image->layers[k].y0 + 1;
        short bytes_per_row = image_width / 8;
        bytes_per_row += image_width % 8 ? 1 : 0;
        short relx = j - image->layers[k].x0;
        short rely = i - image->layers[k].y0;
        short byte_index = (rely * bytes_per_row) + relx / 8;
        bool inbounds = relx >= 0 ? (relx < image_width ? (rely >= 0 ? rely < image_height : false) : false) : false;
        if (inbounds ? image->layers[k].bitmap[byte_index] & (1 << (7 - (relx % 8))) : false) {
            HAL_LCD_writeData(image->layers[k].color >> 8);
            HAL_LCD_writeData(image->layers[k].color);
            return true;
        }
    }
    return false;
}

void draw(image* image)
{
  image->inQueue = false;
  short i, j, k;

  short y0 = image->y0 < image->py0 ? image->y0 : image->py0;
  short x0 = image->x0 < image->px0 ? image->x0 : image->px0;
  short y1 = image->y1 > image->py1 ? image->y1 : image->py1;
  short x1 = image->x1 > image->px1 ? image->x1 : image->px1;

  x0 = (x0 > 131 ? 131 : (x0 < 0 ? 0 : x0));
  y0 = (y0 > 131 ? 131 : (y0 < 0 ? 0 : y0));
  x1 = (x1 > 131 ? 131 : (x1 < 0 ? 0 : x1));
  y1 = (y1 > 131 ? 131 : (y1 < 0 ? 0 : y1));

  image->px0 = image->x0;
  image->py0 = image->y0;
  image->px1 = image->x1;
  image->py1 = image->y1;

  if (x0<=x1 ? (y0<=y1 ? true : false) : false) {
    xSemaphoreTake(Sem_Erase, portMAX_DELAY);
    Crystalfontz128x128_SetDrawFrame(x0, y0, x1, y1);
    HAL_LCD_writeCommand(CM_RAMWR);

    for (i = y0; i <= y1; i++) {
      for (j = x0; j <= x1; j++) {
        for (k=0; k<numImages; k++) {
          if (((images[k]->inQueue & images[k]->moving) & !image->moving) ? false : draw_pixel(images[k],i,j)) break;
        }
        if (k==numImages) {
          HAL_LCD_writeData(0x0);
          HAL_LCD_writeData(0x0);
        }
      }
    }
    xSemaphoreGive(Sem_Erase);
  }
}
