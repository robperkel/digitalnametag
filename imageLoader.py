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

    for y in range(104):
        for x in range(212):
            if (pixels[x, y] == (255, 0, 0)):
                ser.write(b'R')
            elif (pixels[x, y] == (255, 255, 255)):
                ser.write(b'W')
            else:
                ser.write(b'B')

    ser.write(b'#')
    ser.close()
    print("Transfer done")

main()