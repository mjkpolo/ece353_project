#include "lcd.h"

static const uint8_t _x2x_bm_0x8000[] = {
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

static layer _layers_x2x[] = {
  {103,110,116,124,0x8000,_x2x_bm_0x8000}
};

void draw_x2x(image* image) {
  fill_image(image,_layers_x2x,1);
};
