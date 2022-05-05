#include "lcd.h"

static const uint8_t _xx3_bm_0x8000[] = {
  0x70,
  0x88,
  0x8,
  0x8,
  0x70,
  0x8,
  0x8,
  0x88,
  0x70
};

static layer _layers_xx3[] = {
  {110,117,116,124,0x8000,_xx3_bm_0x8000}
};

void draw_xx3(image* image) {
  fill_image(image,_layers_xx3,1);
};
