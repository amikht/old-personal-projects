import random
import time

# Version 1.0
#
# Runs in O(n^2) time at best, O(n^3) at worst
#
# Absolutely terrible considering that, on data sets of this size,
# python's default sort runs in O(c), and even worse, its literally instantaneous

def sort(arr):
	changes = 1
	while changes != 0:
		changes = 0
		for i in range(len(arr)-1):
			if arr[i] > arr[i+1]:
				tmp = arr[i]
				arr[i] = arr[i+1]
				arr[i+1] = tmp
				changes += 1
	return arr

with open("2018.11.23_50000.txt", 'r') as f_in:
	dataset = list(map(int, f_in.readlines()))
	print("My method:\n")
	startTime = time.time()
	arr = sort(dataset)
	delta = str(time.time() - startTime)
	print("Final time for " + str(len(dataset)) + " items: " + delta + "s")

print("\n")

with open("2018.11.23_50000.txt") as f_in:
	print("\nPython default:\n")
	startTime = time.time()
	arr = sorted(test)
	delta = str(time.time() - startTime)
	print("Final time for " + str(len(dataset)) + " items: " + delta + "s")
