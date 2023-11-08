"""
Copyright (c) 2021 - Analog Devices Inc. All Rights Reserved.

This software is proprietary to Analog Devices, Inc. and its licensors.
"""
"""
@file     : PushDataParser.py
@brief    : Capture, parse and display analytics metadata pushed over UART
@version  : 0.1
@date     : April 2021
@arguments: c - Serial (COM) port number, b - Baudrate of serial port
"""

import serial
import argparse
import json
import time

keyValString = "{key}: {value}"
peopleString = "\t[ID: {val0}, ImageX: {val1}, ImageY: {val2}, ActivityLevel: {val3}]"

class People:
    def __init__(self, ID, ImgX, ImgY, ActLvl):
        self.ID = ID
        self.ImageX = ImgX
        self.ImageY = ImgY
        self.ActivityLevel = ActLvl

class MetaData:
    def __init__(self):
        self.PacketID = None
        self.PacketNum = None
        self.TimeStamp = None
        self.OccupancyStatus = None
        self.LightStatus = None
        self.PeopleCount = None
        self.ZoneOccupancyStatus = None
        self.ZoneLightStatus = None
        self.ZoneLuxLevel = None
        self.ZonePeopleCount = None
        self.People = None
        self.DeviceNotCommissioned = None

    def Create(self, rcvData):
        try:
            data = json.loads(rcvData)
        except:
            return False

        dictList = data.items()

        for (key, value) in dictList:
            if(key == "PID"):
                self.PacketID = value
            elif(key == "PNO"):
                self.PacketNum = value
            elif(key == "TimeStamp"):
                self.TimeStamp = value
            elif(key == "OccStat"):
                self.OccupancyStatus = value
            elif(key == "LgtStat"):
                self.LightStatus = value
            elif(key == "PplCnt"):
                self.PeopleCount = value
            elif(key == "ZnOccStat"):
                self.ZoneOccupancyStatus = value
            elif(key == "ZnLgtStat"):
                self.ZoneLightStatus = value
            elif(key == "ZnLuxLvl"):
                self.ZoneLuxLevel = value
            elif(key == "ZnPplCnt"):
                self.ZonePeopleCount = value
            elif(key == "Ppl"):
                pplList = []
                for val in value:
                    pplJson = str(eval(json.dumps(val))).replace("'", '"')
                    pplDict = json.loads(pplJson)
                    ppl = People(pplDict['ID'], pplDict['ImgX'], pplDict['ImgY'], pplDict['ActLvl'])
                    pplList.append(ppl)
                self.People = pplList
            elif(key == "DeviceNotCommissioned"):
                self.DeviceNotCommissioned = value

        return True

    def Print(self):
        obj = vars(self)

        for item in obj:
            if(obj[item] is not None):
                if(item == 'People'):
                    print("People: ")
                    for ppl in self.People:
                        print(peopleString.format(val0=ppl.ID, val1=ppl.ImageX, val2=ppl.ImageY, val3=ppl.ActivityLevel))
                else:
                    print(keyValString.format(key=item, value=obj[item]))

        print("------------------------------------------------------------")
    
    def ParsePushData(self, ser):       
        rcvBytes = 0

        while (rcvBytes == 0):
            # wait till we receive the complete buffer
            rcvBytes = ser.in_waiting
            time.sleep(1)

        rcvData = ser.read(ser.in_waiting)
            
        self.Create(rcvData)
        # self.Print()

def argparse_setup():

    parser = argparse.ArgumentParser(
        prog="PushDataParser",
        description="Read push data in JSON format and display metadata.",
        epilog="",
    )

    parser.add_argument(
        "-c", "--COM-PORT",
        help="serial port.",
        action='store',
        required=True
    )

    parser.add_argument(
        "-b", "--baudrate",
        help="serial port baudrate",
        action='store',
        required=True
    )

    return parser

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
    metaData = MetaData()
    for i in range(5):
        metaData.ParsePushData(ser)

    ser.close()      

if __name__ == "__main__":
    main('COM10', 115200)