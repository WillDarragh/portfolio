#!/usr/bin/julia

# Collatz in Julia
# Will Darragh

# MAX NUMBER
N = 10000

function collatz(x)
	collatz_length = 0
	while ( x != 1 )
		if ( x%2 == 0 )
			x = x/2
		else
			x = 3*x + 1
		end
		collatz_length += 1
	end
	return (collatz_length)
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
