#include "lcd.h"

static const uint8_t _xx7_bm_0x8000[] = {
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

static layer _layers_xx7[] = {
  {110,117,116,124,0x8000,_xx7_bm_0x8000}
};

void draw_xx7(image* image) {
  fill_image(image,_layers_xx7,1);
};
