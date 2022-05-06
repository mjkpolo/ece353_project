#include "lcd.h"

static const uint8_t _7xx_bm_0x8000[] = {
  0xf8,
  0x8,
  0x8,
  0x10,
  0x10,
  0x20,
  0x20,
  0x40,
  0x40
};

static layer _layers_7xx[] = {
  {96,100,116,124,0x8000,_7xx_bm_0x8000}
};

void draw_7xx(image* image) {
  fill_image(image,_layers_7xx,1,false);
};
