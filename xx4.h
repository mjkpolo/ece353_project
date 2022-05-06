#include "lcd.h"

static const uint8_t _xx4_bm_0x8000[] = {
  0x90,
  0x90,
  0x90,
  0x90,
  0xf8,
  0x10,
  0x10,
  0x10
};

static layer _layers_xx4[] = {
  {110,114,117,124,0x8000,_xx4_bm_0x8000}
};

void draw_xx4(image* image) {
  fill_image(image,_layers_xx4,1,false);
};
