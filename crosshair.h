#include "lcd.h"

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

layer layers_crosshair[] = {
  {58,72,52,66,0x0,crosshair_bm_0x0},
  {58,72,52,66,0xc718,crosshair_bm_0xc718}
};
void draw_crosshair(image* image, short x, short y) {
  int i;
  erase_image(image);
  for (i=0; i<2; i++) {
    short image_width = layers_crosshair[i].x1-layers_crosshair[i].x0;
    short image_height = layers_crosshair[i].y1-layers_crosshair[i].y0;
    layers_crosshair[i].x0 = x-(image_width/2+image_width%2);
    layers_crosshair[i].x1 = x+(image_width/2);
    layers_crosshair[i].y0 = y-(image_height/2+image_height%2);
    layers_crosshair[i].y1 = y+(image_height/2);
  }
  fill_image(image,layers_crosshair,2);
};
