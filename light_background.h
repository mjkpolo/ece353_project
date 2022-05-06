#include "lcd.h"

static const uint8_t _light_background_bm_0x871c[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0x4, 0x7f, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0x0, 0x1f, 0xff, 0xfc, 0x0, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xf0,
  0x0, 0x1f, 0x81, 0xf0, 0x0, 0x3f, 0xff, 0xff, 0xff, 0xfc, 0x1, 0xff, 0xf0, 0x5f, 0xc7, 0xff, 0x90,
  0x0, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x3, 0x81, 0xf0, 0x0, 0xd, 0xf0, 0xc, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x200[] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xf0,
  0x80, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x0, 0x1e, 0x0, 0x6, 0x7, 0xff, 0xf0,
  0xf0, 0x4, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xfc, 0x0, 0xf, 0xff, 0xff, 0xf0,
  0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1, 0xff, 0xff, 0xff, 0xf0,
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0
};

static const uint8_t _light_background_bm_0x4600[] = {
  0x0, 0x1, 0x80, 0x7c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x3, 0xf7, 0xe1, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x1, 0x80, 0x0, 0x0,
  0xf, 0xff, 0xff, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xc0, 0x3, 0xe0, 0x0, 0x0,
  0x3f, 0xff, 0xff, 0xff, 0xfc, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x7, 0xff, 0xe0, 0x29, 0xe0, 0x0, 0x0,
  0x7f, 0xff, 0xff, 0xf1, 0xf8, 0x0, 0x0, 0x1, 0x80, 0x0, 0x7, 0xff, 0xf0, 0x18, 0xe0, 0x0, 0x0,
  0x7f, 0xff, 0xff, 0xf8, 0x7c, 0x0, 0x0, 0x1, 0x80, 0x0, 0x3, 0xff, 0xf8, 0x10, 0x7c, 0x4, 0x0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0xff, 0xbc, 0x0, 0xff, 0x3, 0x80,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xa4, 0x0, 0xff, 0xf1, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x3f, 0x0, 0x0, 0x1f, 0xc6, 0x1, 0xff, 0xff, 0xf0,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x7, 0xe7, 0x3, 0xff, 0xff, 0xf0,
  0xff, 0x1, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0xf, 0xc0, 0x0, 0x1, 0xf7, 0x83, 0xff, 0xff, 0xf0,
  0x40, 0x0, 0x7, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x6, 0xc0, 0x0, 0x0, 0x7b, 0xc3, 0xff, 0xf8, 0x0,
  0x0, 0x0, 0x0, 0x7f, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x23, 0x0, 0x0, 0x3f, 0xc1, 0xff, 0xfc, 0x0,
  0x0, 0x0, 0x0, 0x1f, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0xf, 0xe0, 0xff, 0xc0, 0x0,
  0x0, 0x0, 0x0, 0x3, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x7, 0xf0, 0x7c, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xf0, 0x18, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xf0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xf0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x4500[] = {
  0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x6, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x7e, 0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x1, 0x80, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x7f, 0x2c, 0x0, 0x38, 0x0, 0x18, 0x0, 0x18, 0x60, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x70, 0x7e, 0x0, 0x18, 0x0, 0xc, 0x0, 0x1f, 0x10, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x3, 0x80, 0x0, 0x70, 0x7f, 0x80, 0x1c, 0x0, 0x6, 0x0, 0x3, 0xf8, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x70, 0xff, 0x80, 0xf, 0x0, 0x2, 0x0, 0x0, 0xfc, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x3c, 0xff, 0xfe, 0x7, 0x80, 0x3, 0x0, 0x0, 0xe, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xc0, 0xfc, 0x43, 0xe0, 0x1, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xc0, 0x7e, 0x1, 0xf8, 0x0, 0x80, 0x0, 0x0, 0x0,
  0x0, 0xfe, 0x0, 0x0, 0x0, 0x38, 0x0, 0x1f, 0xf0, 0x3f, 0x80, 0x3e, 0x0, 0x40, 0x0, 0x0, 0x0,
  0xbf, 0xff, 0xf8, 0x0, 0x0, 0x38, 0x0, 0xf, 0xf9, 0xf, 0xe0, 0x7, 0x80, 0x0, 0x0, 0x7, 0xf0,
  0xff, 0xff, 0xff, 0x80, 0x0, 0x30, 0x0, 0x3, 0xfc, 0x0, 0xff, 0x3, 0xc0, 0x2, 0x0, 0x3, 0xf0,
  0x7f, 0xff, 0xff, 0xe0, 0x0, 0x60, 0x0, 0x0, 0x7f, 0x0, 0x1f, 0xfb, 0xf0, 0x1, 0x0, 0x3f, 0xf0,
  0x7f, 0xff, 0xff, 0xfc, 0x3, 0x80, 0x0, 0x0, 0xf, 0x80, 0x3, 0xff, 0xf8, 0x1, 0x83, 0xff, 0xf0,
  0x3f, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0xfc, 0x8, 0x67, 0xff, 0xf0,
  0x7, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x3c, 0x8, 0x3f, 0xf0, 0x40,
  0x0, 0x0, 0x3f, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x78, 0x1a, 0x8, 0x1, 0xc1, 0x80,
  0x0, 0x0, 0x3, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xf0, 0x19, 0x58, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x3, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xf0, 0x7, 0xd8, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x80, 0x7, 0xf0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xc0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x2500[] = {
  0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0xfc, 0x0, 0x8, 0x0, 0x0, 0x0, 0x3f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x1e, 0x0,
  0xf8, 0x0, 0x0, 0x0, 0x6, 0x6, 0x1f, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0xff, 0x80,
  0xf0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x7f, 0x80, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x77, 0xc0,
  0xc0, 0x0, 0x0, 0x0, 0x1, 0x87, 0x6f, 0x80, 0x0, 0x0, 0x40, 0x0, 0x5, 0xc0, 0x0, 0x1c, 0xf0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0xc3, 0x7f, 0x80, 0x1, 0x0, 0x60, 0x0, 0x1, 0xc0, 0x0, 0xf, 0x90,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x61, 0x3d, 0x80, 0x0, 0x0, 0x60, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x21, 0x1c, 0x80, 0x0, 0x40, 0x70, 0x0, 0x1, 0xf0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x8e, 0xc0, 0x0, 0x1, 0xf8, 0x0, 0x0, 0xe0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x4f, 0xc0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x4f, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x27, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x17, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x1b, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0,
  0x80, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x8, 0xee, 0x0, 0x0, 0x0, 0x0, 0x0, 0x14, 0x0, 0x0, 0x0,
  0x80, 0x0, 0x0, 0x0, 0x0, 0x78, 0x1, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa, 0x0, 0x0, 0x0,
  0x40, 0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0x7c, 0x6, 0x0, 0x0, 0x0, 0x0, 0x1, 0x80, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x4, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x20, 0x4, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x2400[] = {
  0x0, 0x0, 0x0, 0x0, 0x2, 0x78, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x1, 0xf8, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x3, 0x1c, 0x0, 0x0, 0x4, 0x0, 0x0, 0x8, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x3, 0x8f, 0x80, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0xff, 0x80, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x2, 0x0, 0x0, 0x7f, 0x80, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x3, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0,
  0x80, 0x0, 0x0, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x1, 0xc0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0,
  0xf0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xa0, 0x3, 0xf7, 0xf8, 0x0, 0x0, 0x0, 0x3, 0xc0, 0x0, 0x10,
  0xf8, 0x0, 0x0, 0x0, 0x0, 0x3f, 0x80, 0x3, 0xc3, 0xfe, 0x0, 0x0, 0xc0, 0x2, 0x60, 0x18, 0x0,
  0x3e, 0x0, 0x0, 0x0, 0x18, 0x7f, 0xa8, 0x2, 0x0, 0x73, 0x80, 0x0, 0xe0, 0x6, 0x30, 0x8, 0x0,
  0x7, 0xf0, 0x0, 0x0, 0x60, 0x0, 0x4, 0x70, 0x0, 0x0, 0xc0, 0x0, 0xe0, 0x4, 0x12, 0x6, 0x0,
  0x0, 0x1f, 0x80, 0xf, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x10, 0x10, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x7, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x80, 0x10, 0x10, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x40, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x4504[] = {
  0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x80, 0x10, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x42, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x60, 0xa, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xf9, 0x7, 0x80,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x7, 0x88, 0x0, 0x0, 0x8, 0xc, 0x83, 0xf8, 0x0, 0x40,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc7, 0xf8, 0x1, 0xf8, 0x0, 0xa0, 0xc0, 0x10, 0x0, 0x20,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xf8, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x14, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xc0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x3f, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x88, 0x1, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0xf8, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x3f, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x1, 0xfb, 0xc, 0x8, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1c, 0xc, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x30, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x2300[] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x0, 0x1, 0x80, 0x0, 0x30,
  0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x1, 0xff, 0x8c, 0x0, 0x0, 0x0, 0x1, 0xc0, 0x30, 0x60,
  0xf8, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xf8, 0xf, 0xe0, 0xff, 0x0, 0x0, 0x0, 0x3, 0xe1, 0xf9, 0x80,
  0xff, 0xe0, 0x0, 0x0, 0x77, 0xff, 0xff, 0xf8, 0x0, 0x1f, 0x80, 0xf, 0xe0, 0x4, 0xfe, 0x1e, 0x0,
  0x7f, 0xff, 0xf8, 0x3f, 0x80, 0x0, 0x1, 0x0, 0x0, 0x1, 0xc0, 0x70, 0x60, 0x8, 0x30, 0x0, 0x0,
  0x0, 0x0, 0x1f, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x0, 0xe0, 0x30, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x63, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x2200[] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60,
  0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x7, 0x0, 0x60, 0x0, 0x0, 0x0, 0x3, 0x1, 0xe1, 0xc0,
  0x80, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xfe, 0xf0, 0x0, 0x6, 0x0, 0xf, 0x80, 0x7, 0xcf, 0xfe, 0x0,
  0x7f, 0xff, 0xe0, 0x1f, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x80, 0xe1, 0x0, 0x9, 0xf8, 0x0, 0x0,
  0xf, 0xfb, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7e, 0x3, 0x80, 0xf0, 0x0, 0x0, 0x0,
  0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xfe, 0x0, 0x0, 0x0, 0x0,
  0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x4604[] = {
  0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x1f, 0xf8, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x4, 0x0,
  0xff, 0x0, 0x1, 0x98, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x3d, 0x0, 0xf, 0x0,
  0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xdf, 0xc0, 0xf, 0x38,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xe0, 0x0, 0x1e, 0xa,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xb, 0x0,
  0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x80,
  0x0, 0x0, 0x3, 0xc0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xc0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x3, 0x80,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2c, 0x3, 0x80,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x3, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x2, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x2, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xc0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x8718[] = {
  0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0xbb, 0x80, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x20, 0x0, 0x2, 0x45, 0x0, 0x0, 0x0, 0x0, 0x3, 0xfc, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0,
  0x0, 0x20, 0x7e, 0xc, 0x0, 0x40, 0x0, 0x0, 0x0, 0x2, 0x6, 0x0, 0xf, 0xa0, 0x38, 0x0, 0x60,
  0x0, 0x0, 0x1, 0x10, 0x0, 0x1f, 0xff, 0xfc, 0x7e, 0xc, 0x0, 0x72, 0x0, 0x33, 0xe7, 0x10, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xf0, 0x0, 0xf, 0xf0, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x4400[] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfa,
  0x7f, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xe2, 0x64,
  0x1f, 0xff, 0xc0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0xfc, 0x78,
  0x0, 0xff, 0xc1, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0,
  0x0, 0x7, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x6, 0x0, 0x80, 0x80, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xf0, 0x0, 0xc2, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x2504[] = {
  0x2c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0xc7, 0x0, 0xc, 0x0, 0x8, 0x0, 0x37, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x7c, 0x0,
  0x2, 0x0, 0x0, 0x0, 0xc, 0x2, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x61, 0xc0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x60,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0xf, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x80, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x4508[] = {
  0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0xee, 0x80, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x84, 0x80, 0x0, 0x1, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0,
  0x81, 0xc4, 0x0, 0x2, 0x42, 0xd3, 0x34, 0x0, 0x0, 0x0, 0x6, 0x40, 0x0, 0x80, 0xcc, 0xd2, 0x90,
  0x0, 0xc0, 0x0, 0x0, 0x0, 0x2, 0xc0, 0x0, 0x80, 0x0, 0x46, 0x18, 0x2, 0x60, 0x0, 0x0, 0x30,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x7, 0xfc, 0x0, 0x18, 0xa0, 0x0, 0x0, 0x10
};

static const uint8_t _light_background_bm_0x6614[] = {
  0xae, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0xa4, 0x0, 0x0, 0x0, 0x0, 0x1, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x80, 0x80, 0x18, 0x1, 0x0, 0x0, 0x0, 0x0, 0x6, 0x3c, 0x0, 0x18, 0x0, 0x23, 0x1c, 0xc0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xf8, 0x0, 0x18, 0x0, 0x80, 0x11, 0xc9, 0x88, 0x61, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x10, 0x60, 0x8, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x2404[] = {
  0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x36, 0x80, 0x7, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0xc, 0x20, 0x1, 0x0, 0x1f, 0x80, 0x0, 0x0, 0x0, 0x0, 0x4,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x70, 0x0, 0x0, 0x40, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x1f, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x6, 0x2, 0xc0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0xe, 0x3, 0xe0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x3c, 0x0, 0xbc, 0xe0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x450c[] = {
  0x9f, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x2, 0x0, 0x0, 0x2, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x6, 0x0, 0x0, 0x4, 0x7, 0x80, 0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x11, 0x86, 0x20,
  0x0, 0x0, 0x0, 0x0, 0x2, 0x58, 0x7, 0xfb, 0x0, 0x3, 0x90, 0x40, 0x6, 0x0, 0x66, 0x10, 0xc0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x40, 0x0, 0x1b, 0x2, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x6610[] = {
  0x90, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x20, 0x40, 0x0, 0x0, 0x42, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x40, 0x0, 0x8, 0x6, 0x80, 0x0, 0x0, 0x0, 0x0, 0x50, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x18, 0xe, 0x10, 0x0, 0x20, 0x0, 0x0, 0x0, 0x1, 0x7, 0xc0, 0x2, 0x81, 0x95, 0x24, 0xa0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x2, 0x20, 0x18, 0x4, 0x25, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x3, 0x30, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x6718[] = {
  0x80, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x8, 0x80, 0x0, 0x3, 0x54, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x4, 0x9, 0x0, 0x0, 0x0, 0x0, 0x3, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x1e, 0x10, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x4, 0x1, 0x0, 0x11, 0x80, 0x20, 0x51, 0x80,
  0x0, 0x0, 0x1, 0x80, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x10, 0x0, 0x20, 0x10, 0x8, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xc0, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x2600[] = {
  0x0, 0x0, 0x5, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x4, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x60,
  0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xf0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x70,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x460c[] = {
  0xf, 0x80, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x80, 0x3c, 0x86, 0x0, 0x2, 0x0, 0x8, 0x0, 0x0, 0x6, 0x0, 0x1, 0x0, 0x0, 0x10,
  0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x10, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x4608[] = {
  0x9d, 0x80, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40,
  0x0, 0x0, 0x1a, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0xa0,
  0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x8, 0x0, 0x0
};

static const uint8_t _light_background_bm_0x6714[] = {
  0x86, 0xb0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x9, 0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40
};

static const uint8_t _light_background_bm_0x4404[] = {
  0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0,
  0x20, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x0,
  0xc0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80
};

static const uint8_t _light_background_bm_0x2604[] = {
  0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x80, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x10,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1
};

static const uint8_t _light_background_bm_0x4610[] = {
  0xc0, 0x20, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x1, 0x80, 0x0, 0x0, 0x80
};

static const uint8_t _light_background_bm_0x6510[] = {
  0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x2, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80
};

static const uint8_t _light_background_bm_0x650c[] = {
  0x80, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x40,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x8
};

static const uint8_t _light_background_bm_0x660c[] = {
  0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40
};

static const uint8_t _light_background_bm_0x2508[] = {
  0x80, 0x0, 0x0, 0x0, 0x0, 0x2
};

static const uint8_t _light_background_bm_0x4408[] = {
  0x80, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x4
};

static layer _layers_light_background[] = {
  {0,131,0,95,0x871c,_light_background_bm_0x871c},
  {0,131,118,131,0x200,_light_background_bm_0x200},
  {0,131,99,118,0x4600,_light_background_bm_0x4600},
  {0,131,99,120,0x4500,_light_background_bm_0x4500},
  {0,131,98,116,0x2500,_light_background_bm_0x2500},
  {0,131,99,122,0x2400,_light_background_bm_0x2400},
  {1,131,95,118,0x4504,_light_background_bm_0x4504},
  {0,131,116,122,0x2300,_light_background_bm_0x2300},
  {0,131,117,124,0x2200,_light_background_bm_0x2200},
  {7,117,97,113,0x4604,_light_background_bm_0x4604},
  {0,130,91,96,0x8718,_light_background_bm_0x8718},
  {4,130,114,121,0x4400,_light_background_bm_0x4400},
  {0,131,97,117,0x2504,_light_background_bm_0x2504},
  {0,131,94,99,0x4508,_light_background_bm_0x4508},
  {2,131,93,98,0x6614,_light_background_bm_0x6614},
  {3,120,97,118,0x2404,_light_background_bm_0x2404},
  {1,131,94,99,0x450c,_light_background_bm_0x450c},
  {0,130,93,98,0x6610,_light_background_bm_0x6610},
  {1,129,92,97,0x6718,_light_background_bm_0x6718},
  {0,131,99,112,0x2600,_light_background_bm_0x2600},
  {10,125,96,99,0x460c,_light_background_bm_0x460c},
  {11,109,97,99,0x4608,_light_background_bm_0x4608},
  {11,108,95,96,0x6714,_light_background_bm_0x6714},
  {37,93,98,118,0x4404,_light_background_bm_0x4404},
  {22,109,98,109,0x2604,_light_background_bm_0x2604},
  {9,49,96,97,0x4610,_light_background_bm_0x4610},
  {1,81,93,96,0x6510,_light_background_bm_0x6510},
  {39,83,95,97,0x650c,_light_background_bm_0x650c},
  {13,110,96,98,0x660c,_light_background_bm_0x660c},
  {6,52,97,97,0x2508,_light_background_bm_0x2508},
  {39,76,98,99,0x4408,_light_background_bm_0x4408}
};

void draw_light_background(image* image) {
  fill_image(image,_layers_light_background,31);
};
