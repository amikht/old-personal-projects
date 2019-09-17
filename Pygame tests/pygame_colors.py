import pygame, sys
from pygame.locals import *

WIDTH = 1260
HEIGHT = 720

pygame.init()
DisplaySurface = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Colors")

red = 0
green = 0
blue = 200  # Could be 255, this looks slightly better

# Limit fps so colors change at a reasonable and predictable rate
FPS = 60
fpsClock = pygame.time.Clock()

while True:
	## Event Handling
	for e in pygame.event.get():
		if e.type == QUIT:
			pygame.quit()
			sys.exit()

	## Updating
	# Change color
	if (red > 0) and (blue == 0):
		red -= 1
		green += 1
	elif green > 0:
		green -= 1
		blue += 1
	else:
		blue -= 1
		red += 1
	# Update color variable
	color = (red, green, blue)

	## Drawing
	pygame.draw.rect(DisplaySurface, color, (0, 0, WIDTH, HEIGHT))
	pygame.display.update()

	## End loop
	fpsClock.tick(FPS)