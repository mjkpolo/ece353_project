#include "lcd.h"

static const uint8_t _x8x_bm_0x8000[] = {
  0x70,
  0x88,
  0x88,
  0x88,
  0x70,
  0x88,
  0x88,
  0x88,
  0x70
};

static layer _layers_x8x[] = {
  {103,107,116,124,0x8000,_x8x_bm_0x8000}
};

void draw_x8x(image* image) {
  fill_image(image,_layers_x8x,1,false);
};
