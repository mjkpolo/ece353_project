#include "lcd.h"

static const uint8_t _xx0_bm_0x8000[] = {
  0x70,
  0xc8,
  0xc8,
  0xa8,
  0xa8,
  0xa8,
  0x98,
  0x98,
  0x70
};

static layer _layers_xx0[] = {
  {110,114,116,124,0x8000,_xx0_bm_0x8000}
};

void draw_xx0(image* image) {
  fill_image(image,_layers_xx0,1,false);
};
