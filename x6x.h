#include "lcd.h"

static const uint8_t _x6x_bm_0x8000[] = {
  0x30,
  0x40,
  0x80,
  0xb0,
  0xc8,
  0x88,
  0x88,
  0x88,
  0x70
};

static layer _layers_x6x[] = {
  {103,107,116,124,0x8000,_x6x_bm_0x8000}
};

void draw_x6x(image* image) {
  fill_image(image,_layers_x6x,1);
};
