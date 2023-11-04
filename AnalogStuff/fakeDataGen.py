import json
import random
import time

class People:
    def __init__(self, ID, ImgX, ImgY, ActLvl):
        self.ID = ID
        self.ImageX = ImgX
        self.ImageY = ImgY
        self.ActivityLevel = ActLvl

class MetaData:
    heartbeat = 0
    def __init__(self):
        self.PacketID = 0
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
        self.number = 4
    
    def Create(self):
        if self.number > 3:
            self.PeopleCount = random.randint(0, 5)
            pplList = []
            for i in range(self.PeopleCount):
                randX = random.randint(0, 639)
                randY = random.randint(0, 479)
                # print(i, randX, randY)
                ppl = People(i, randX, randY, 10)
                pplList.append(ppl)
            self.People = pplList
            self.number = 0
            self.PacketID += 1
        else:
            self.number += 1


    def ParsePushData(self, ser):
        time.sleep(MetaData.heartbeat)
        self.Create()

def InitSerialPort(heartbeat):
    MetaData.heartbeat = heartbeat
    print("Running Fake Data")
    print(f"Fake heartbeat: {MetaData.heartbeat}")
