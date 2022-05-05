#include "lcd.h"

static const uint8_t _xx2_bm_0x8000[] = {
  0x70,
  0x88,
  0x88,
  0x18,
  0x70,
  0xc0,
  0x80,
  0x80,
  0xf8
};

static layer _layers_xx2[] = {
  {110,117,116,124,0x8000,_xx2_bm_0x8000}
};

void draw_xx2(image* image) {
  fill_image(image,_layers_xx2,1);
};
