from PIL import Image

im = Image.open(r"scrolltext.png")
width, height = im.size
px = im.load()
print("int scrolltext_1[][512]={")
for y in range(height):
    print("{",end='')
    for x in range(width):
        col = px[x,y]
        if col[1] == 255:
            print("0", end=',')
        elif col[0] == 0:
            print("1", end=',')
    print("},")
        #print(px[x,y])
print("};")