#include "lcd.h"

static const uint8_t _x5x_bm_0x8000[] = {
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

static layer _layers_x5x[] = {
  {103,107,116,124,0x8000,_x5x_bm_0x8000}
};

void draw_x5x(image* image) {
  fill_image(image,_layers_x5x,1,false);
};
