#include "lcd.h"

static const uint8_t _0xx_bm_0x8000[] = {
  0x70,
  0xc8,
  0xc8,
  0xa8,
  0xa8,
  0xa8,
  0x98,
  0x98,
  0x70
};

static layer _layers_0xx[] = {
  {96,103,116,124,0x8000,_0xx_bm_0x8000}
};

void draw_0xx(image* image) {
  fill_image(image,_layers_0xx,1);
};
