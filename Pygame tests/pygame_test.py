# Simple test to make sure that pygame has installed correctly.
import pygame, sys
from pygame.locals import *

pygame.init()
DisplaySurface = pygame.display.set_mode((400, 300))
pygame.display.set_caption("Pygame Test")

while True:

	for e in pygame.event.get():
		if e.type == QUIT:
			pygame.quit()
			sys.exit()

	pygame.display.update()