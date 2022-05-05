#include "lcd.h"

static const uint8_t _x1x_bm_0x8000[] = {
  0x40,
  0xc0,
  0x40,
  0x40,
  0x40,
  0x40,
  0x40,
  0x40,
  0xe0
};

static layer _layers_x1x[] = {
  {104,111,116,124,0x8000,_x1x_bm_0x8000}
};

void draw_x1x(image* image) {
  fill_image(image,_layers_x1x,1);
};
