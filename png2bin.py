#!/usr/bin/env python

import cv2
import sys
import numpy as np
from functools import reduce
import os
import argparse

def getBitmaps(img, name, move):
        sections = sorted(((key,img == key) for key in set(img[~img.mask])),key=lambda n : np.count_nonzero(n[1]), reverse=True) # search high pixel count bitmaps first
        bool2byte = lambda c : hex((c[7] << 0) |
                                   (c[6] << 1) |
                                   (c[5] << 2) |
                                   (c[4] << 3) |
                                   (c[3] << 4) |
                                   (c[2] << 5) |
                                   (c[1] << 6) |
                                   (c[0] << 7))
        structs = []

        yield '#include "lcd.h"\n\n'


        tmp = np.zeros((132,132,4)).astype(np.uint8)
        tmp [:,:,0:4] = 255
        for key,pixels in sections:

            ''' reconstruct image '''

            hex2b = lambda h : (h&0x001F)<<3
            hex2g = lambda h : (h&0x07E0)>>3
            hex2r = lambda h : (h&0xF800)>>8


            bitmap = []
            yield f'static const uint8_t _{name}_bm_{hex(key)}[] = ' + '{\n  '

            p = np.where(pixels) if not move else np.where(~img.mask)
            last_col = max(p[1])
            last_row = max(p[0])
            first_col = min(p[1])
            first_row = min(p[0])

            pixels = pixels[first_row:last_row+1,first_col:last_col+1]

            tmp[first_row:last_row+1,first_col:last_col+1,0][pixels] = hex2b(key)
            tmp[first_row:last_row+1,first_col:last_col+1,1][pixels] = hex2g(key)
            tmp[first_row:last_row+1,first_col:last_col+1,2][pixels] = hex2r(key)

            
            for line in pixels:
                chunks = np.concatenate((line,np.zeros(8-len(line)%8)),axis=0).reshape(((len(line)+8-(len(line)%8))//8,8)).astype(bool) # seperate into bytes
                bitmap.append(', '.join(map(bool2byte,(row for row in chunks))))

            yield ',\n  '.join(bitmap)
            yield '\n};\n\n'

            structs.append('{'+f'{first_col},{last_col+8-(last_col-first_col+1)%8},{first_row},{last_row},{hex(key)},_{name}_bm_{hex(key)}'+'}')


        yield f'static layer _layers_{name}[] = '+'{\n  '
        yield ',\n  '.join(structs)
        yield '\n};\n\n'
        #print('Put window focus on image and press any key to continue')
        #cv2.imshow('Reconstructed Image for a check',tmp)
        #cv2.waitKey(0)

        yield(
            f'void draw_{name}(image* image) ' + '{\n'
            if not move else
            f'void draw_{name}(image* image, short x, short y) ' + '{\n'
        )
        yield(
            f'  fill_image(image,_layers_{name},{len(structs)});\n'
            if not move else
            '  int i;\n' \
            '  erase_image(image);\n' \
            f'  for (i=0; i<{len(structs)}; i++) '+'{\n' \
            f'    short image_width = _layers_{name}[i].x1-_layers_{name}[i].x0;\n' \
            f'    short image_height = _layers_{name}[i].y1-_layers_{name}[i].y0;\n' \
            f'    _layers_{name}[i].x0 = x-(image_width/2+image_width%2);\n' \
            f'    _layers_{name}[i].x1 = x+(image_width/2);\n' \
            f'    _layers_{name}[i].y0 = y-(image_height/2+image_height%2);\n' \
            f'    _layers_{name}[i].y1 = y+(image_height/2);\n' \
            '  }\n' \
            f'  fill_image(image,_layers_{name},{len(structs)});\n'
        )
        yield '};\n'

def main(names, move):
    layer = np.ma.zeros((132,132)).astype(np.uint16)
    layer.mask = True
    for name in names:
        if os.path.splitext(name)[1] != '.png':
            print("Pass png file",file=sys.stderr)
            return 420
    
        img = cv2.cvtColor(cv2.imread(name, cv2.IMREAD_UNCHANGED), cv2.COLOR_BGRA2RGBA).astype(np.uint16)
        
        '''
        CONVERT TO 16 BIT
        '''
        R = (img[:,:,0] >> 3 & 0x18)
        G = (img[:,:,1] >> 2 & 0x38)
        B = (img[:,:,2] >> 3 & 0x18)
        A = (img[:,:,3] > (1 << 7)).astype(bool) # consider alpha < 128 (max val 255) clear

        np.place(layer, A ,((R << 11) | (G << 5) | B)[A])
        layer.mask &= ~A
    
    with open(f'{os.path.splitext(name)[0]}.h', mode='w') as file:
        file.write(reduce(lambda a,b:a+b, getBitmaps(layer, os.path.splitext(name)[0], move)))

    return 0


if __name__=='__main__':
    parser = argparse.ArgumentParser(description='Convert text file to bitmap')
    parser.add_argument('input', nargs='+', help='.png filename')
    parser.add_argument('-m', action='store_true', help='allow midpoint selection')
    args = parser.parse_args()
    exit(main(args.input,args.m))
