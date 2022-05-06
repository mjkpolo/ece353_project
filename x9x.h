#include "lcd.h"

static const uint8_t _x9x_bm_0x8000[] = {
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

static layer _layers_x9x[] = {
  {103,107,116,124,0x8000,_x9x_bm_0x8000}
};

void draw_x9x(image* image) {
  fill_image(image,_layers_x9x,1,false);
};
