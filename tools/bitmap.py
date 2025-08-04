from PIL import Image
from random import randint
import os 

size = 256
img = Image.new( 'RGB', (size,size), "black") # create a new black image
pixels = img.load() # create the pixel map

def get_int(integers):
    f = open("php_randint.txt", "r")
    lines = f.readlines()
    length = len(lines)
    print(length)
    for i in range(length):
        # print(lines[i])
        integers.append(int(lines[i]))

def get_bits(bits):
    file = open("trand", "rb")
    byte = file.read(1)
    bys = []
    while byte != b"":
        byte = file.read(1)
        num = int.from_bytes(byte, "little")  
        print(num)
        for _ in range(8):
            bit = num % 2
            num = num // 2
            bits.append(bit)
            print(bit)
        bys.append(byte)

    print(os.stat("trand"))
    print(len(bits))
    print(len(bys))


def make_bitmap(name):
    integers = []
    get_int(integers)
    print(len(integers))
    for i in range(img.size[0]):    # for every col:
        for j in range(img.size[1]):    # For every row
            p = (int(integers[i * img.size[0] + j]))
            p_ = 0
            if p == 1:
                p_ = 255
            pixels[i,j] = (p_, p_, p_)
    img.show()
    img.save(name)

def make_bitmap_t(name):
    bits = []
    get_bits(bits)
    for i in range(img.size[0]):    # for every col:
        for j in range(img.size[1]):    # For every row
            p = (int(bits[i * img.size[0] + j]))
            p_ = 0
            if p == 1:
                p_ = 255
            pixels[i,j] = (p_, p_, p_)
    img.show()
    img.save(name)

# name = "php_im.pdf"
# make_bitmap(name)

name = "trand.pdf"
make_bitmap_t(name)
