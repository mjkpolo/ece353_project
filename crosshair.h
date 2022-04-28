#include <string.h>

const uint8_t crosshair_bm_0x0[] =
{
0x1, 0x0,
0x3e, 0xfc,
0x40, 0x4,
0x5e, 0xf4,
0x51, 0x14,
0x51, 0x14,
0x52, 0x94,
0x8c, 0x62,
0x52, 0x94,
0x51, 0x14,
0x51, 0x14,
0x5e, 0xf4,
0x40, 0x4,
0x3e, 0xf8,
0x1, 0x0
};

const uint8_t crosshair_bm_0xc718[] =
{
0x0, 0x0,
0x1, 0x0,
0x3f, 0xf8,
0x21, 0x8,
0x20, 0x8,
0x20, 0x8,
0x21, 0x8,
0x73, 0x9c,
0x21, 0x8,
0x20, 0x8,
0x20, 0x8,
0x21, 0x8,
0x3f, 0xf8,
0x1, 0x0,
0x0, 0x0
};

short first_row_fg = 132;
short first_col_fg = 132;
short last_row_fg = 0;
short last_col_fg = 0;

short pfirst_row_fg = 132;
short pfirst_col_fg = 132;
short plast_row_fg = 0;
short plast_col_fg = 0;

layer* moving_layers = NULL;
size_t num_moving_layers = 0;


layer layers_crosshair[] = {
  {58,72,52,66,0x0,crosshair_bm_0x0},
  {58,72,52,66,0xc718,crosshair_bm_0xc718}
};
void draw_crosshair(short x, short y) {
  int i;
  for (i = 0; i<2; i++) {
    short image_width = layers_crosshair[0].x1 - layers_crosshair[0].x0;
    short image_height = layers_crosshair[0].y1 - layers_crosshair[0].y0;

    layers_crosshair[i].x0 = x-(image_width/2+image_width%2);
    layers_crosshair[i].x1 = x+(image_width/2);
  
    layers_crosshair[i].y0 = y-(image_height/2+image_height%2);
    layers_crosshair[i].y1 = y+(image_height/2);
    first_row_fg = first_row_fg < layers_crosshair[i].y0 ? first_row_fg : layers_crosshair[i].y0;
    last_row_fg = last_row_fg > layers_crosshair[i].y1 ? last_row_fg : layers_crosshair[i].y1;
    first_col_fg = first_col_fg < layers_crosshair[i].x0 ? first_col_fg : layers_crosshair[i].x0;
    last_col_fg = last_col_fg > layers_crosshair[i].x1 ? last_col_fg : layers_crosshair[i].x1;
  }
  // add textures to the rest
  moving_layers = (layer*) realloc(moving_layers, (num_moving_layers+2)*sizeof(layer));
  memcpy(&moving_layers[num_moving_layers],layers_crosshair,sizeof(layer)*2);
  num_moving_layers+=2;
};
