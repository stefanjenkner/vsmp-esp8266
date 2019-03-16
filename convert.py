#!/usr/bin/env python

import argparse

from bitarray import bitarray
from PIL import Image


def convert(src, dst):
    treshhold=128
    with Image.open(src) as img:
        width, height = img.size
        rgb_img = img.convert('RGB')
        a = bitarray()
        for y in range(0, height):
            for x in range(0, width):
                r, g, b = rgb_img.getpixel((x, y))
                is_black = ((r + g + b) / 3) > treshhold
                a.append(is_black)
        #print(a.tobytes().hex())
        with open(dst, 'wb') as out:
            out.write(a.tobytes())
            out.flush()

def main():
    parser = argparse.ArgumentParser(description='Abc')
    parser.add_argument('src')
    parser.add_argument('dst')
    args = parser.parse_args()
    convert(args.src, args.dst)


if __name__ == '__main__':
    main()