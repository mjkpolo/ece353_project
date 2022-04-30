#include "lcd.h"

static const uint8_t _x3x_bm_0x8000[] = {
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

static layer _layers_x3x[] = {
  {103,107,116,124,0x8000,_x3x_bm_0x8000}
};

void draw_x3x(image* image) {
  fill_image(image,_layers_x3x,1);
};
