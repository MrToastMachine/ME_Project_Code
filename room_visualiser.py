import pygame
import math
pygame.init()

RES = (1000, 1000)
FPS = 5

win = pygame.display.set_mode(RES)
clock = pygame.time.Clock()

# COLOURS
WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)

cone = pygame.image.load("vision_cone.png")
image_size = cone.get_size()

des_w = 400
scale = des_w / image_size[0]

cone2 = pygame.transform.scale_by(cone, scale)

new_scale = cone2.get_size()
xPos = RES[0]/2 - new_scale[0]/2
yPos = RES[1]/2 - new_scale[1]/2

rot = 0

cone2 = pygame.transform.rotate(cone2, rot)

def update():
    global rot
    global cone2

    win.fill(BLACK)
    win.blit(cone2,(0,0))
    print(cone2.get_size())
    
    cone2 = pygame.transform.rotate(cone2, rot)
    rot = rot + 1



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
