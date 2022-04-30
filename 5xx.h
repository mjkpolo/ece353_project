#include "lcd.h"

static const uint8_t _5xx_bm_0x8000[] = {
  0xf8,
  0x80,
  0x80,
  0xf0,
  0x8,
  0x8,
  0x88,
  0x88,
  0x70
};

static layer _layers_5xx[] = {
  {96,100,116,124,0x8000,_5xx_bm_0x8000}
};

void draw_5xx(image* image) {
  fill_image(image,_layers_5xx,1);
};
