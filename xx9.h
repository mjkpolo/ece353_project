#include "lcd.h"

static const uint8_t _xx9_bm_0x8000[] = {
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

static layer _layers_xx9[] = {
  {110,117,116,124,0x8000,_xx9_bm_0x8000}
};

void draw_xx9(image* image) {
  fill_image(image,_layers_xx9,1);
};
