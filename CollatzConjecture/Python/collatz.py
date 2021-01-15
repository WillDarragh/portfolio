#!/usr/bin/python3

# Collatz in Python
# Will Darragh

# MAX NUMBER
N = 10000

def collatz(n):
	x = n
	length = 0
	while ( x != 1 ):
		if ( x%2 == 0 ):
			x = x/2
		else:
			x = 3*x + 1
		length += 1
	return length

# BIGGEST LENGTHS
numbers = []

for n in range(1,N+1):
	length = collatz(n)
	if (len(numbers) < 10):
		numbers.append([n,length])
	else:
		if (length > numbers[0][1]):
			numbers[0] = [n,length]
		elif (length == numbers[0][1] and n < numbers[0][0]):
			numbers[0] = [n,length]
	numbers.sort(key=lambda x : x[1])

numbers.sort(key=lambda x : x[0])
print('Number\tLength')
for number in numbers:
	print(f'{number[0]}\t{number[1]}')
