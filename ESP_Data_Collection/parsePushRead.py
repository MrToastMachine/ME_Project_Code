from getSerialData import *
import struct

ser = InitSerialPort('/dev/tty.usbserial-1110', 115200)

buffer = 1

incoming_data = []

def getSerialData(ser):
    byte_read = ser.read(buffer)

    while (byte_read.decode('ascii') != "["):
        # wait till we receive the complete buffer
        byte_read = ser.read(buffer)

        # print(byte_read)
        # actual = struct.unpack('>b', byte_read)
        actual = byte_read.decode('ascii')

        # print(actual)
        # time.sleep(0.05)
    data = ser.read_until(b']')[:-1]

    data = data.decode('ascii')

    # print(data)
    return data.split(",")



for i in range(5):

    data = getSerialData(ser)

    for i, val in enumerate(data):
        print(f"{i:3}", val)
