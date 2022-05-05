#include "lcd.h"

static const uint8_t _xx8_bm_0x8000[] = {
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

static layer _layers_xx8[] = {
  {110,117,116,124,0x8000,_xx8_bm_0x8000}
};

void draw_xx8(image* image) {
  fill_image(image,_layers_xx8,1);
};
