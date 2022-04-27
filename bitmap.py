#!/usr/bin/env python
import sys


def main(hexes):
    hex2bin = lambda h : (' '*8+bin(int(h,base=16))[2:].replace('0',' ').replace('1','#'))[-8:]
    rows = len(hexes.strip().split('\n'))
    hexes = hexes.replace('\n',' ').strip().split(', ')
    bytes_per_row = len(hexes)//rows
    for r in range(rows):
        for i in range(bytes_per_row):
            print(hex2bin(hexes[bytes_per_row*r+i]),end='')
        print()
    return 0

if __name__=='__main__':
    exit(main(sys.stdin.read()))
