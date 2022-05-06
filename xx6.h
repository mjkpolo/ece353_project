#include "lcd.h"

static const uint8_t _xx6_bm_0x8000[] = {
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

static layer _layers_xx6[] = {
  {110,114,116,124,0x8000,_xx6_bm_0x8000}
};

void draw_xx6(image* image) {
  fill_image(image,_layers_xx6,1,false);
};
