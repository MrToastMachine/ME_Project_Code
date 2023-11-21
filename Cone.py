import pygame
import math

scale = 800
view_range = scale/2

# COLOURS
WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)

def dist_two_points(pointA, pointB):
    return math.sqrt((pointB[0] - pointA[0])**2 + (pointB[1] - pointA[1])**2)

class Cone():
    sensors = []

    def __init__(self, win, img, pos, start_ang, end_ang, letter_id, track_mouse=True):
        self.win = win
        self.img = img
        self.pos = pos
        self.start_angle = start_ang
        self.end_angle = end_ang
        self.id = letter_id
        self.track_mouse = track_mouse
        self.detection = False
        Cone.sensors.append(self)

    def showCone(self):
        self.win.blit(self.img, [x - scale/2 for x in self.pos])

        if self.track_mouse:
            dist_to_mouse = self.getDistToMouse()
            self.drawArc(dist_to_mouse)

    def getDistToMouse(self):
        mousePos = pygame.mouse.get_pos()
        dist_to_mouse = dist_two_points(mousePos, self.pos)
        return dist_to_mouse

    def drawArc(self, dist):
        
        arc_rect = (self.pos[0] - dist, self.pos[1] - dist, 2*dist, 2*dist)
        pygame.draw.arc(self.win, WHITE, arc_rect, -math.radians(self.end_angle), -math.radians(self.start_angle), 1)

    def angle_to_point(self, mousePos):
        angle = math.atan2(mousePos[1] - self.pos[1], mousePos[0] - self.pos[0])
        return (math.degrees(angle) + 360) % 360
        
    def checkSensorTriggered(self):
        mousePos = pygame.mouse.get_pos()
        angle_to_object = self.angle_to_point(mousePos)

        if (self.start_angle < angle_to_object < self.end_angle):
            if (dist_two_points(mousePos, self.pos) <= view_range):
                # print(f"In view of sensor {self.id}")
                self.showCone()
    
    @classmethod
    def checkAllSensors(cls):
        for sensor in cls.sensors:
            if sensor.track_mouse:
                sensor.checkSensorTriggered()
            else:
                if sensor.detection and sensor.detection < 450:
                    sensor.showCone()
                    sensor.drawArc(sensor.detection)
