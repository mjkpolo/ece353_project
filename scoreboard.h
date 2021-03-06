#include "lcd.h"

static const uint8_t _scoreboard_bm_0xc718[] = {
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
  0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0xb1, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xf8,
  0xb7, 0x11, 0x6b, 0xff, 0xff, 0xff, 0xf8,
  0xb1, 0x75, 0x22, 0xff, 0xff, 0xff, 0xf8,
  0xbd, 0x75, 0x6f, 0xff, 0xff, 0xff, 0xf8,
  0xb1, 0x11, 0x62, 0xff, 0xff, 0xff, 0xf8,
  0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8
};

static const uint8_t _scoreboard_bm_0x8000[] = {
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4,
  0x5f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
  0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
  0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
  0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
  0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
  0xa3, 0x0, 0x4, 0x0, 0x0, 0x0, 0x2,
  0xa4, 0x32, 0x4a, 0x0, 0x0, 0x0, 0x2,
  0xa7, 0x45, 0x6e, 0x80, 0x0, 0x0, 0x2,
  0xa1, 0x45, 0x48, 0x0, 0x0, 0x0, 0x2,
  0xa6, 0x32, 0x46, 0x80, 0x0, 0x0, 0x2,
  0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
  0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
  0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
  0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe
};

static const uint8_t _scoreboard_bm_0x8410[] = {
  0x80, 0x1, 0x40,
  0x8, 0xa0, 0x0,
  0x0, 0x0, 0x0,
  0x0, 0x0, 0x0,
  0x28, 0xa1, 0x0
};

static layer _layers_scoreboard[] = {
  {69,121,112,126,0xc718,_scoreboard_bm_0xc718},
  {68,122,111,127,0x8000,_scoreboard_bm_0x8000},
  {73,90,118,122,0x8410,_scoreboard_bm_0x8410}
};

void draw_scoreboard(image* image) {
  fill_image(image,_layers_scoreboard,3,false);
};
