#include "lcd.h"

static const uint8_t _9xx_bm_0x8000[] = {
  0x70,
  0x88,
  0x88,
  0x98,
  0x68,
  0x8,
  0x8,
  0x10,
  0x60
};

static layer _layers_9xx[] = {
  {96,100,116,124,0x8000,_9xx_bm_0x8000}
};

void draw_9xx(image* image) {
  fill_image(image,_layers_9xx,1);
};
