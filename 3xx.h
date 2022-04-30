#include "lcd.h"

static const uint8_t _3xx_bm_0x8000[] = {
  0x70,
  0x88,
  0x8,
  0x8,
  0x70,
  0x8,
  0x8,
  0x88,
  0x70
};

static layer _layers_3xx[] = {
  {96,100,116,124,0x8000,_3xx_bm_0x8000}
};

void draw_3xx(image* image) {
  fill_image(image,_layers_3xx,1);
};
