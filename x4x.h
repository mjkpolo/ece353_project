#include "lcd.h"

static const uint8_t _x4x_bm_0x8000[] = {
  0x90,
  0x90,
  0x90,
  0x90,
  0xf8,
  0x10,
  0x10,
  0x10
};

static layer _layers_x4x[] = {
  {103,107,117,124,0x8000,_x4x_bm_0x8000}
};

void draw_x4x(image* image) {
  fill_image(image,_layers_x4x,1,false);
};
