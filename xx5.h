#include "lcd.h"

static const uint8_t _xx5_bm_0x8000[] = {
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

static layer _layers_xx5[] = {
  {110,114,116,124,0x8000,_xx5_bm_0x8000}
};

void draw_xx5(image* image) {
  fill_image(image,_layers_xx5,1,false);
};
