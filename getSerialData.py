import serial

def InitSerialPort(com, baud):
    # com = args.COM_PORT
    print("Connecting to serial port " + com)
    sp = serial.Serial(com)

    # sp.baudrate = args.baudrate
    sp.baudrate = baud
    if sp.isOpen() == True :
        sp.close()
    sp.open()
    if sp.isOpen() == True:
        print("Serial port successfully opened with "  + com)

    return sp

def main(com, baud):
    # parser = argparse_setup()
    # args = parser.parse_args()    
    ser = InitSerialPort(com, baud)

    """
    # Look at PushDataParser.py for Metadata class
    # metaData = MetaData()
    
    
    for i in range(5):
        metaData.ParsePushData(ser)

    """

    ser.close()      

if __name__ == "__main__":
    main('COM10', 115200)