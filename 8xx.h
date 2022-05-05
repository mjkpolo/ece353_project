#include "lcd.h"

static const uint8_t _8xx_bm_0x8000[] = {
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

static layer _layers_8xx[] = {
  {96,103,116,124,0x8000,_8xx_bm_0x8000}
};

void draw_8xx(image* image) {
  fill_image(image,_layers_8xx,1);
};
