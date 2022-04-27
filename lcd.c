/*
 * lcd.c
 *
 *  Created on: Sep 11, 2020
 *      Author: Joe Krachey
 */

#include "lcd.h"

extern SemaphoreHandle_t Sem_LCD;


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
    EUSCI_B0->CTLW0 =  EUSCI_B_CTLW0_SWRST;            // Put eUSCI state machine in reset

    // ADD CODE to define the behavior of the eUSCI_B0 as a SPI interface
    EUSCI_B0->CTLW0 = EUSCI_B_CTLW0_CKPH | // Phase 1
                      EUSCI_B_CTLW0_MSB | // Msb first
                      EUSCI_B_CTLW0_MST | // Set as SPI master
                      EUSCI_B_CTLW0_MODE_0 | // 3 pin spi mode
                      EUSCI_B_CTLW0_SYNC | // async
                      EUSCI_B_CTLW0_SSEL__SMCLK | //smclk
                      //EUSCI_B_CTLW0_STEM | //UCxSTE digital output
                      EUSCI_B_CTLW0_SWRST; // remain in eusci mode

    // ADD CODE to set the SPI Clock to 12MHz.
    //
    // Divide clock speed by 2 (24MHz/2) = 12 MHz
    //fBitClock = fBRCLK/(UCBRx+1).
    EUSCI_B0->BRW = 1;

    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;// Initialize USCI state machine

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
    while(EUSCI_B0->STATW & UCBUSY);

    // Transmit data
    EUSCI_B0->TXBUF = command;

    // Busy wait while the data is being transmitted. Check the STATW register and see if it is busy 
    while(EUSCI_B0->STATW & UCBUSY);

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
    while(EUSCI_B0->STATW & UCBUSY);
    EUSCI_B0->TXBUF = data;
    while(EUSCI_B0->STATW & UCBUSY);
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
    uint8_t upper8  = 0x00;
    uint8_t lower8  = 0x00;

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

    for (i = 0; i < LCD_VERTICAL_MAX; i++)
    {

        for(j=0; j < LCD_HORIZONTAL_MAX; j++)
        {
            HAL_LCD_writeData(upper8);
            HAL_LCD_writeData(lower8);
        }
    }

    HAL_LCD_delay(10);

    HAL_LCD_writeCommand(CM_DISPON);

    HAL_LCD_writeCommand(CM_MADCTL);
    HAL_LCD_writeData(CM_MADCTL_MX | CM_MADCTL_MY | CM_MADCTL_BGR);
}

void draw(
  const short* x0,
  const short* y0,
  const short* x1,
  const short* y1,
  const uint8_t **image,
  const uint16_t *fColor,
  short numImages,
  short first_col,
  short first_row,
  short last_col,
  short last_row,
  bool moving
) {
  short i,j,k;

  /*
  Previous Drawing
  */
  static short* px0 = NULL;
  static short* py0 = NULL;
  static short* px1 = NULL;
  static short* py1 = NULL;
  static const uint8_t **pimage = NULL;
  static const uint16_t *pfColor = NULL;
  static short pnumImages = NULL;
  static short pfirst_row = NULL;
  static short pfirst_col = NULL;
  static short plast_row = NULL;
  static short plast_col = NULL;


  if (pnumImages != NULL && moving)
    draw(px0,py0,px1,py1,pimage,pfColor,pnumImages,pfirst_col,pfirst_row,plast_col,plast_row,false);

  px0 = moving ? px0 : x0;
  py0 = moving ? py0 : y0;
  px1 = moving ? px1 : x1;
  py1 = moving ? py1 : y1;
  pimage = moving ? pimage: image;
  pfColor = moving ? pfColor : fColor;
  pnumImages = moving ? pnumImages : numImages;
  pfirst_row = moving ? first_row : pfirst_row;
  pfirst_col = moving ? first_col : pfirst_col;
  plast_row = moving ? last_row : plast_row;
  plast_col = moving ? last_col : plast_col;

  xSemaphoreTake(Sem_LCD, portMAX_DELAY);
  Crystalfontz128x128_SetDrawFrame(first_col,first_row,last_col,last_row);
  HAL_LCD_writeCommand(CM_RAMWR);

  for (i=first_row; i<=last_row; i++) {
    for (j=first_col; j<=last_col; j++) {
      for (k=0; k<numImages; k++) {
        short image_width = x1[k]-x0[k]+1;
        short image_height = y1[k]-y0[k]+1;
        short bytes_per_row = image_width / 8;
        bytes_per_row += image_width % 8 ? 1 : 0;
        short relx = moving ? j-first_col : j-x0[k];
        short rely = moving ? i-first_row : i-y0[k];
        short byte_index = (rely*bytes_per_row) + relx/8;
        bool inbounds = relx >= 0 ? (relx < image_width ? (rely >= 0 ? rely < image_height : false) : false) : false;

        if (inbounds) {
          if (image[k][byte_index] & (1 << (7-(relx%8)))) {
            HAL_LCD_writeData(fColor[k] >> 8);
            HAL_LCD_writeData(fColor[k]);
            break;
          }
        }
      }
      if (k==numImages) {
        for (k=0; k<pnumImages; k++) {
          short image_width = px1[k]-px0[k]+1;
          short image_height = py1[k]-py0[k]+1;
          short bytes_per_row = image_width / 8;
          bytes_per_row += image_width % 8 ? 1 : 0;
          short relx = j-px0[k];
          short rely = i-py0[k];
          short byte_index = (rely*bytes_per_row) + relx/8;
          bool inbounds = relx >= 0 ? (relx < image_width ? (rely >= 0 ? rely < image_height : false) : false) : false;

          if (inbounds) {
            if (pimage[k][byte_index] & (1 << (7-(relx%8)))) {
              HAL_LCD_writeData(pfColor[k] >> 8);
              HAL_LCD_writeData(pfColor[k]);
              break;
            }
          }
        }
      }
    }
  }
  xSemaphoreGive(Sem_LCD);
}
