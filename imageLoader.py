from PIL import Image
import serial

def main():
    print("Opening Image file")
    
    im = Image.open("./Pictures/nametag_3color.png")
    pixels = im.load()

    # TODO: Verify Image Size

    ser = serial.Serial('COM11')

    # TODO: User selects COM port

    ser.write(b' ')    

    for y in range(im.height):
        for x in range(im.width):
            if (pixels[x, y] == (255, 0, 0)):
                #print('R', end='')
                ser.write(b'R')
            elif (pixels[x, y] == (255, 255, 255)):
                #print('W', end='')
                ser.write(b'W')
            else:
                #print('B', end='')
                ser.write(b'B')
        #print(' ')

    ser.write(b'#')
    ser.close()
    print("Transfer done")

main()