#include "lcd.h"

static const uint8_t _6xx_bm_0x8000[] = {
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

static layer _layers_6xx[] = {
  {96,100,116,124,0x8000,_6xx_bm_0x8000}
};

void draw_6xx(image* image) {
  fill_image(image,_layers_6xx,1,false);
};
