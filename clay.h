#include "lcd.h"

static const uint8_t _clay_bm_0xe400[] = {
  0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0,
  0x3, 0xff, 0xe0, 0x0,
  0x1f, 0xff, 0xfc, 0x0,
  0x3f, 0xff, 0xfe, 0x0,
  0x38, 0x0, 0xe, 0x0,
  0x0, 0x0, 0x0, 0x0
};

static const uint8_t _clay_bm_0x2100[] = {
  0x3, 0xff, 0xe0, 0x0,
  0x1c, 0x0, 0x1c, 0x0,
  0x20, 0x0, 0x2, 0x0,
  0x40, 0x0, 0x1, 0x0,
  0x80, 0x0, 0x0, 0x80,
  0x80, 0x0, 0x0, 0x80,
  0x7f, 0xff, 0xff, 0x0
};

static const uint8_t _clay_bm_0xe600[] = {
  0x0, 0x0, 0x0, 0x0,
  0x3, 0xff, 0xe0, 0x0,
  0x1c, 0x0, 0x1c, 0x0,
  0x20, 0x0, 0x2, 0x0,
  0x40, 0x0, 0x1, 0x0,
  0x40, 0x0, 0x1, 0x0,
  0x0, 0x0, 0x0, 0x0
};

static const uint8_t _clay_bm_0x8200[] = {
  0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0,
  0x7, 0xff, 0xf0, 0x0,
  0x0, 0x0, 0x0, 0x0
};

static layer _layers_clay[] = {
  {30,54,47,53,0xe400,_clay_bm_0xe400},
  {30,54,47,53,0x2100,_clay_bm_0x2100},
  {30,54,47,53,0xe600,_clay_bm_0xe600},
  {30,54,47,53,0x8200,_clay_bm_0x8200}
};

void draw_clay(image* image, short x, short y) {
  int i;
  if (image->layers) erase_image(image);
  for (i=0; i<4; i++) {
    short image_width = _layers_clay[i].x1-_layers_clay[i].x0;
    short image_height = _layers_clay[i].y1-_layers_clay[i].y0;
    _layers_clay[i].x0 = x-(image_width/2+image_width%2);
    _layers_clay[i].x1 = x+(image_width/2);
    _layers_clay[i].y0 = y-(image_height/2+image_height%2);
    _layers_clay[i].y1 = y+(image_height/2);
  }
  fill_image(image,_layers_clay,4);
};
