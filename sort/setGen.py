from random import randint
arr = []
def checker(arr, number):
	return True if (number not in arr) else False
start = int(input("Enter start number: "))
end = int(input("Enter end number: "))
filename = input("Enter output file name: ")
if start < end:
	for i in range(start, end+1):
		while True:
			num = randint(start, end)
			if checker(arr, num):
				arr.append(num)
				break
	with open(filename, "w") as file:
		for el in arr:
			file.write(str(el) + "\n")