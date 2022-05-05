#include "lcd.h"

static const uint8_t _4xx_bm_0x8000[] = {
  0x90,
  0x90,
  0x90,
  0x90,
  0xf8,
  0x10,
  0x10,
  0x10
};

static layer _layers_4xx[] = {
  {96,103,117,124,0x8000,_4xx_bm_0x8000}
};

void draw_4xx(image* image) {
  fill_image(image,_layers_4xx,1);
};
