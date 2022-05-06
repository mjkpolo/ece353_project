#include "lcd.h"

static const uint8_t _2xx_bm_0x8000[] = {
  0x70,
  0x88,
  0x88,
  0x18,
  0x70,
  0xc0,
  0x80,
  0x80,
  0xf8
};

static layer _layers_2xx[] = {
  {96,100,116,124,0x8000,_2xx_bm_0x8000}
};

void draw_2xx(image* image) {
  fill_image(image,_layers_2xx,1,false);
};
