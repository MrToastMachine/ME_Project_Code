import serial
import time
import json

def InitSerialPort(com, baud):
    # com = args.COM_PORT
    print("Connecting to serial port " + com)
    try:
        sp = serial.Serial(com)
    except:
        print(f"Could not connect to serial port {com}")
        return False
    
    # sp.baudrate = args.baudrate
    sp.baudrate = baud
    if sp.isOpen() == True :
        sp.close()
    sp.open()
    if sp.isOpen() == True:
        print("Serial port successfully opened with "  + com)

    return sp


def ParsePushData(ser):       
    rcvBytes = 0

    while (rcvBytes == 0):
        # wait till we receive the complete buffer
        rcvBytes = ser.in_waiting
        time.sleep(0.05)

    rcvData = ser.read(ser.in_waiting)

    try:
        # Remove leading 'b' and trailing '\r\n'
        rcvData = rcvData.strip()
        # Parse the JSON data
        data = json.loads(rcvData)\
        
        print(data)
        
        return data
        
    except json.JSONDecodeError as e:
        print(f"Error parsing JSON: {e}")
        print(rcvData)
        return None


def main(com, baud):
    # parser = argparse_setup()
    # args = parser.parse_args()    
    ser = InitSerialPort(com, baud)

    for i in range(5):
        ParsePushData(ser)

    """
    # Look at PushDataParser.py for Metadata class
    # metaData = MetaData()
    
    
    for i in range(5):
        metaData.ParsePushData(ser)

    """

    ser.close()      

if __name__ == "__main__":
    main('COM5', 115200)