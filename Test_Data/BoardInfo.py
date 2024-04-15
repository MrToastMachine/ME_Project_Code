import numpy as np

# distance to sensor from board origin [CONSTANT]
SENSOR_DIST_TO_ORIGIN = 0.11 * np.cos(np.pi/12)

class Board:
    def __init__(self, id_num, pos, angle):
        self.id = id_num
        self.posX, self.posY = pos
        self.angle = angle

        self.initSensors()

        self.all_sensors = [self.sensorA, self.sensorB, self.sensorC]

    def initSensors(self):
        self.sensorA = Sensor(self, 'A')
        self.sensorB = Sensor(self, 'B')
        self.sensorC = Sensor(self, 'C')

    

class Sensor:
    def __init__(self, parent_board, sensor_id):
        self.sensor_id = sensor_id
        self.parent_board = parent_board

        if sensor_id == 'A':
            self.angle = parent_board.angle - (np.pi / 12) # 15 degrees 
        elif sensor_id == 'B':
            self.angle = parent_board.angle - (np.pi / 4) # 45 degrees
        elif sensor_id == 'C':
            self.angle = parent_board.angle - (np.pi / 3) # 60 degrees

        self.posX = parent_board.posX + (np.cos(self.angle) * SENSOR_DIST_TO_ORIGIN)
        self.posY = parent_board.posY + (np.sin(self.angle) * SENSOR_DIST_TO_ORIGIN)

        self.detections = []

    def loadTestData(self, test_data):
        if len(test_data) > 0:
            self.detections.extend([x[0] for x in test_data])

    def printInfo(self):
        print(f"b{self.parent_board.id}s{self.sensor_id} : {self.detections}")
        print(f"Pos: {self.posX}, {self.posY}")
        print(f"Angle: {self.angle}")


# b1 = Board(1, (1.6,0), np.pi)
# b2 = Board(2, (0, 0), np.pi/2)
# b3 = Board(3, (0,1.6), 0)

if __name__=="__main__":
    x = [(3.2,4), (6.8,8)]
    data = [5.6]

    if len(x) > 0:
        data.extend([i[0] for i in x])

    print(data)