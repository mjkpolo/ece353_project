#!/usr/bin/env python

import cv2
import sys
import numpy as np
from functools import reduce
import os
import argparse

def getBitmaps(img, name, move):
        sections = sorted(((key,np.where(img == key,True,False)) for key in set(img[~img.mask])),key=lambda n : np.count_nonzero(n[1]), reverse=True) # search high pixel count bitmaps first
        bool2byte = lambda c : hex((c[7] << 0) |
                                   (c[6] << 1) |
                                   (c[5] << 2) |
                                   (c[4] << 3) |
                                   (c[3] << 4) |
                                   (c[2] << 5) |
                                   (c[1] << 6) |
                                   (c[0] << 7))
        images = []
        keys = []
        x0 = []
        y0 = []
        x1 = []
        y1 = []

        last_col = 0
        last_row = 0
        first_col = 132
        first_row = 132
        yield '#include "lcd.h"\n\n'


        for key,pixels in sections:
            bitmap = []
            yield f'const uint8_t {name}_bm_{hex(key)}[] =\n' + '{\n'

            p = np.where(pixels) if not move else np.where(~img.mask)
            last_col = max(p[1])
            last_row = max(p[0])
            first_col = min(p[1])
            first_row = min(p[0])

            image_height = last_row-first_row+1
            image_width = last_col-first_col+1

            pixels = pixels[first_row:last_row+1,first_col:last_col+1]
            bytes_per_row = (image_width + 8-image_width%8)//8
            
            for line in pixels:
                chunks = np.concatenate((line,np.zeros(8-len(line)%8)),axis=0).reshape((bytes_per_row,8)).astype(bool) # seperate into bytes
                bitmap.append(', '.join(map(bool2byte,(row for row in chunks))))

            yield ',\n'.join(bitmap)
            yield '\n};\n\n'

            images.append(f'{name}_bm_{hex(key)}')
            keys.append(hex(key))

            x0.append(str(first_col))

            x1.append(str(last_col))

            y0.append(str(first_row))

            y1.append(str(last_row))

        yield f'const short x0_{name}[] = '+'{\n  '
        yield ',\n  '.join(x0)
        yield '\n};\n'
        yield f'const short y0_{name}[] = '+'{\n  '
        yield ',\n  '.join(y0)
        yield '\n};\n'
        yield f'const short x1_{name}[] = '+'{\n  '
        yield ',\n  '.join(x1)
        yield '\n};\n'
        yield f'const short y1_{name}[] = '+'{\n  '
        yield ',\n  '.join(y1)
        yield '\n};\n'
        yield f'const uint8_t* images_{name}[] = '+'{\n  '
        yield ',\n  '.join(images)
        yield '\n};\n'
        yield f'const uint16_t rgb_{name}[] = '+'{\n  '
        yield ',\n  '.join(keys)
        yield '\n};\n'
        yield(
            f'void draw_{name}(void) ' + '{\n'
            if not move else
            f'void draw_{name}(short x, short y) ' + '{\n'
        )
        yield(
            f'  draw(x0_{name},y0_{name},x1_{name},y1_{name},images_{name},rgb_{name},{len(images)},{0},{0},{131},{131},false);'
            if not move else
            f'  draw(x0_{name},y0_{name},x1_{name},y1_{name},images_{name},rgb_{name},{len(images)},x-{image_width//2+image_width%2},y-{image_height//2+image_height%2},x+{image_width//2},y+{image_height//2},true);'
        )
        yield '\n};\n'
        assert((len(x0) == len(y0)) and (len(x1) == len(y1)) and (len(images) == len(keys)) and (len(keys) == len(x0)) and (len(y0) == len(y1)))

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
