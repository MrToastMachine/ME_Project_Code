import pygame
import math
pygame.init()

RES = (400, 400)
FPS = 10

win = pygame.display.set_mode(RES)
clock = pygame.time.Clock()

#COLOURS
WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)

point_of_interest = (200,200)

def angle_to_point(mousePos):
    angle = math.atan2(mousePos[1] - point_of_interest[1], mousePos[0] - point_of_interest[0])
    print((math.degrees(angle) + 360) % 360)

def update():
    mousePos = pygame.mouse.get_pos()

    # angle_to_point(mousePos)

    #drawing
    win.fill(BLACK)
    # pygame.draw.line(win, RED, point_of_interest, mousePos, 2)
    pygame.draw.arc(win, WHITE, (RES[0]/2 - 150,RES[1]/2 - 150,300,300), 0, math.pi, 200)


run = True
while run:
	clock.tick(FPS)
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run = False
	update()
	pygame.display.update()

pygame.quit()