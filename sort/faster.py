import random
import time

# Version 1.1.0
# 
# Adjusted algorithm to prevent weird behaviour with lists
# Somewhat faster than previous iteration, but still seems to run in exponential time

times = []
for i in range(5000, 1000001, 5000):

	initial = [j for j in range(1, i+1)]
	fin = [0 for j in range(i)]

	start = time.time()
	for j in range(i):
		rand = random.randint(0, len(initial) - 1)
		fin[j] = initial[rand]
		# Possibly might be source?
		del initial[rand]
	delta = time.time() - start

	print("Generation of {} took {}s".format(i, delta))
	curtime = time.localtime()
	with open("{}.{}.{}_{}.txt".format(curtime.tm_year, curtime.tm_mon, curtime.tm_mday, i), 'w') as file:
		for element in fin:
			file.write("{}\n".format(element))
	print("Writing to file finished.")
	times.append(delta)

with open("{}.{}.{}_times.txt".format(curtime.tm_year, curtime.tm_mon, curtime.tm_mday), 'w') as file:
	for i in range(len(times)):
		file.write("{}\t{}\n".expandtabs(10).format(i * 5000, times[i]))