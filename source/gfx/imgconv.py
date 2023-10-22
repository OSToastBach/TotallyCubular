from PIL import Image

im = Image.open(r"rifttext.png")
w, h = im.size
px = im.load

for y in range(h):
    for x in range(w):
        pv=im.getpixel((x,y))
        if(pv==(255,255,255,255)):
            print(0, end=",")
        else:
            print(1, end=",")
    print("\a")