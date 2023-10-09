import pygame
import math
import time
pygame.init()

from Cone import *

RES = (500, 400)
FPS = 20

win = pygame.display.set_mode(RES)
clock = pygame.time.Clock()

# COLOURS
WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)

cone_15 = pygame.image.load("Images/vision_cone_15.png")
cone_45 = pygame.image.load("Images/vision_cone_45.png")
cone_75 = pygame.image.load("Images/vision_cone_75.png")

img_size = cone_15.get_size()

scale = 800

# LOAD ALL IMAGES

# 0 to 90 degress clockwise     - POINTING SE
s_cone_A = pygame.transform.scale_by(cone_15, scale/img_size[0])
s_cone_B = pygame.transform.scale_by(cone_45, scale/img_size[0])
s_cone_C = pygame.transform.scale_by(cone_75, scale/img_size[0])

# 90 to 180 degrees clockwise   - POINTING SW
s_cone_D = pygame.transform.flip(s_cone_C, 1, 0)
s_cone_E = pygame.transform.flip(s_cone_B, 1, 0)
s_cone_F = pygame.transform.flip(s_cone_A, 1, 0)

# 180 to 270 degrees clockwise  - POINTING NW
s_cone_G = pygame.transform.flip(s_cone_A, 1, 1)
s_cone_H = pygame.transform.flip(s_cone_B, 1, 1)
s_cone_I = pygame.transform.flip(s_cone_C, 1, 1)

# 270 to 360 degrees clockwise  - POINTING NE
s_cone_J = pygame.transform.flip(s_cone_C, 0, 1)
s_cone_K = pygame.transform.flip(s_cone_B, 0, 1)
s_cone_L = pygame.transform.flip(s_cone_A, 0, 1)


# CREATE ALL CONE OBJECTS
Cone_A = Cone(win, s_cone_A, (0,0), 0, 30, "A")
Cone_B = Cone(win, s_cone_B, (0,0), 30, 60, "B")
Cone_C = Cone(win, s_cone_C, (0,0), 60, 90, "C")

Cone_D = Cone(win, s_cone_D, (RES[0],0), 90, 120, "D")
Cone_E = Cone(win, s_cone_E, (RES[0],0), 120, 150, "E")
Cone_F = Cone(win, s_cone_F, (RES[0],0), 150, 180, "F")

Cone_G = Cone(win, s_cone_G, (RES[0],RES[1]), 180, 210, "G")
Cone_H = Cone(win, s_cone_H, (RES[0],RES[1]), 210, 240, "H")
Cone_I = Cone(win, s_cone_I, (RES[0],RES[1]), 240, 270, "I")

Cone_J = Cone(win, s_cone_J, (0,RES[1]), 270, 300, "J")
Cone_K = Cone(win, s_cone_K, (0,RES[1]), 300, 330, "K")
Cone_L = Cone(win, s_cone_L, (0,RES[1]), 330, 360, "L")



def adjust(x,y):
    return (x - scale/2, y - scale/2)

def update():
    mouse = pygame.mouse.get_pos()

    win.fill(BLACK)
    Cone.checkAllSensors()
    # print(f"Mouse Pos: {mouse}")


run = True
while run:
    clock.tick(FPS)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
	#Do Stuff Here
    update()
    pygame.display.update()

pygame.quit()


# Load Image
#   img1 = pygame.image.load("vision_cone.png")

# Scaling
#   img2_warp = pygame.transform.scale(img1, (NewWidth, NewHeight))
#   w = img1.get_width()
#   h = img1.get_height()
#   img3_aspect_keep = pygame.transform.scale_by(img1, factor)

# Rotation
#   img2_rotate = pygame.transform.rotate(img1, angle_in_degrees)

# Flip
#   img_flip = pygame.transform.flip(img1, (flipX_bool, flipY_bool))
