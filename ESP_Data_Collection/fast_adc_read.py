from getSerialData import *

if __name__=="__main__":
    ser = InitSerialPort("COM8", 115200)

    data = ParsePushData(ser)

    
