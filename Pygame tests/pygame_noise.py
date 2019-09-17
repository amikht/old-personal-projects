# It do some noise, but it's really slow. Can't figure out how to blit faster
# Turned off clock because the program wasn't even getting close to 10 fps anyways

import pygame
import sys
import random
# from random import randint
from pygame.locals import *

WIDTH = 400
HEIGHT = 300
DELTA = 2

pygame.init()
displaySurface = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Noise Gen")

# FPS = 30
# clock = pygame.time.Clock()

def genNoise():
	return [[random.random() for x in range(0, WIDTH//DELTA)] for y in range(0, HEIGHT//DELTA)]

## Test genNoise() func
# print(*(genNoise()), sep="\n")

displayPix = pygame.PixelArray(displaySurface)

while True:

	for e in pygame.event.get():
		if e.type == QUIT:
			del displayPix
			pygame.quit()
			sys.exit()

	noise = genNoise()
	
	for y in range(0, HEIGHT, DELTA):
		for x in range(0, WIDTH, DELTA):
			if DELTA>1:
				pygame.draw.rect(displaySurface,
					(noise[y//DELTA][x//DELTA] * 255, 
					 noise[y//DELTA][x//DELTA] * 255, 
					 noise[y//DELTA][x//DELTA] * 255),
					(x, y, x+DELTA, y+DELTA))
			else:
				displayPix[x][y] = (int(noise[y][x] * 255))

	pygame.display.update()
	#clock.tick()