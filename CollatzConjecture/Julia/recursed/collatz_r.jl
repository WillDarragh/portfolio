#!/usr/bin/julia

# Collatz in Julia with Recursion
# Will Darragh

# MAX NUMBER
N = 10000

function collatz(x)
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

function small_index(lengths)
        small_index = 1
        smallest = lengths[1]

        for i in 1:(length(lengths))
                if (lengths[i] < smallest)
                        smallest = lengths[i]
                        small_index = i
                end
        end
        return (small_index)
end

numbers = UInt128[]
lengths = UInt128[]

for n = 1:N
        collatz_length = collatz(n)
        if ( length(numbers) < 10 )
                push!(numbers, n)
                push!(lengths, collatz_length)
        else
                index = small_index(lengths)
                smallest = lengths[index]
                if ((collatz_length > smallest) || (collatz_length == smallest && n < numbers[index]))
                        numbers[index] = n
                        lengths[index] = collatz_length
                end
        end
end

for i = 1:length(numbers)
        println("\t", numbers[i], "\t", lengths[i])
end
