#!/usr/bin/ruby

# Collatz in Ruby with Recursion
# Will Darragh

# MAX NUMBER
N = 10000

def collatz(x)
	if ( x == 1 )
		return 0
	else
		if ( x%2 == 0 )
			x = x/2
		else
			x = 3*x + 1
		end
	return ( 1 + collatz(x) )
	end
end

def small_index(lengths)
        small_index = 0
        smallest = lengths[0]

        for i in 0..(lengths.size-1)
                if (lengths[i] < smallest)
                        smallest = lengths[i];
                        small_index = i;
                end
        end
        return (small_index)
end

numbers = Array.new
lengths = Array.new

for n in 1..N
        length = collatz(n)
        if ( numbers.size < 10 )
                numbers << n
                lengths << length
        else
                index = small_index(lengths)
                smallest = lengths[index]
                if ((length > smallest) || (length == smallest && n < numbers[index]))
                        numbers[index] = n
                        lengths[index] = length
                end
        end
end

print("\tNumber\tLength\n")
for i in 0..(numbers.size-1)
        print("\t#{numbers[i]}\t#{lengths[i]}\n")
end

