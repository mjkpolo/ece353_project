#include "lcd.h"

static const uint8_t _x7x_bm_0x8000[] = {
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

static layer _layers_x7x[] = {
  {103,107,116,124,0x8000,_x7x_bm_0x8000}
};

void draw_x7x(image* image) {
  fill_image(image,_layers_x7x,1);
};
