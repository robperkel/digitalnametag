from PIL import Image
import serial
import serial.tools
import serial.tools.list_ports

def main():    
    print('Available COM Ports: ')
    for port in serial.tools.list_ports.comports():
        print(port.name)

    print('Select a COM Port: ')
    port = input()

    try:
        print('Opening COM port...')
        ser = serial.Serial(port)

        #Display size
        dispX = 212
        dispY = 104

        print('Enter image path: ')
        imgName = input()

        im = Image.open(imgName)
        pixels = im.load()

        #Verify image and display are matched
        if (im.height != dispY) or (im.width != dispX):
            print('Picture does not match display size')
            raise Exception

        print('Transferring image data...')

        #Reset Memory Pointers
        ser.write(b' ')    

        for y in range(im.height):
            for x in range(im.width):
                if (pixels[x, y] == (255, 0, 0)):
                    #print('R', end='')
                    ser.write(b'R')
                elif (pixels[x, y] == (255, 255, 255)):
                    #print('W', end='')
                    ser.write(b'W')
                elif (pixels[x, y] == (0, 0, 0)):
                    #print('B', end='')
                    ser.write(b'B')
                else:
                    print('Warning: Invalid pixel data found at ', x, ', ', y)
                    ser.write(b'B')
            #print('\r\n', end='')

        #Commit to display (device will close the COM port)
        print('Requesting display update...')
        ser.write(b'#')

        #Release COM Port
        ser.close()
        print('Transfer done')
    except serial.SerialException as errCOM:
        print('Unable to open COM port\r\n> ', errCOM)
    except FileNotFoundError:
        print('Unable to find the specified image')
    except:
        print('An unhandled exception occurred')

main()