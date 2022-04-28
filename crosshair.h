#include "lcd.h"

// Crosshair values
#define CROSSHAIR_WIDTH    18
#define CROSSHAIR_HEIGHT   20
#define SKY_BOTTOM_Y       95
#define STEP_VAL           3

const uint8_t crosshair_bm_0x0[] =
{
0x1, 0x0,
0x3e, 0xfc,
0x40, 0x4,
0x5e, 0xf4,
0x51, 0x14,
0x51, 0x14,
0x52, 0x94,
0x8c, 0x62,
0x52, 0x94,
0x51, 0x14,
0x51, 0x14,
0x5e, 0xf4,
0x40, 0x4,
0x3e, 0xf8,
0x1, 0x0
};

const uint8_t crosshair_bm_0xc718[] =
{
0x0, 0x0,
0x1, 0x0,
0x3f, 0xf8,
0x21, 0x8,
0x20, 0x8,
0x20, 0x8,
0x21, 0x8,
0x73, 0x9c,
0x21, 0x8,
0x20, 0x8,
0x20, 0x8,
0x21, 0x8,
0x3f, 0xf8,
0x1, 0x0,
0x0, 0x0
};

const short x0_crosshair[] = {
  58,
  58
};
const short y0_crosshair[] = {
  52,
  52
};
const short x1_crosshair[] = {
  72,
  72
};
const short y1_crosshair[] = {
  66,
  66
};
const uint8_t* images_crosshair[] = {
  crosshair_bm_0x0,
  crosshair_bm_0xc718
};
const uint16_t rgb_crosshair[] = {
  0x0,
  0xc718
};
void draw_crosshair(short x, short y) {
  draw(x0_crosshair,y0_crosshair,x1_crosshair,y1_crosshair,images_crosshair,rgb_crosshair,2,x-8,y-8,x+7,y+7,true);
};
