#include "lcd.h"

static const uint8_t _1xx_bm_0x8000[] = {
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

static layer _layers_1xx[] = {
  {97,99,116,124,0x8000,_1xx_bm_0x8000}
};

void draw_1xx(image* image) {
  fill_image(image,_layers_1xx,1,false);
};
