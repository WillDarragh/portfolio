#!/usr/bin/python3

# Collatz in Python with Recursion
# Will Darragh

# MAX NUMBER
N = 10000

def collatz(x):
	if ( x == 1 ):
		return 0
	else:
		if ( x%2 == 0 ):
			x = x/2
		else:
			x = 3*x + 1
	return ( 1 + collatz(x) )


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

