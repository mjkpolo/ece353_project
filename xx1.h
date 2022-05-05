#include "lcd.h"

static const uint8_t _xx1_bm_0x8000[] = {
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

static layer _layers_xx1[] = {
  {111,118,116,124,0x8000,_xx1_bm_0x8000}
};

void draw_xx1(image* image) {
  fill_image(image,_layers_xx1,1);
};
