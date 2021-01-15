// Collatz in C# with Recursion
// Will Darragh

using System;
using System.Collections.Generic;

class collatz_r
{
	// MAX NUMBER
	public static int N = 10000;

	public static int collatz_length(int x)
	{
		if ( x == 1 )
			return (0);
		else {
			if ( x%2 == 0 ) 
				x = x/2;
			else
				x = 3*x + 1;
		}
		return ( 1 + collatz_length(x));
	}

        public static void Main(String[] args)
        {
                List<int> numbers = new List<int>();
                List<int> lengths = new List<int>();

                int length, index, smallest;
                for ( int n = 1; n <= N; n++ ) {
                        length = collatz_length(n);
                        if (numbers.Count < 10) {
                                numbers.Add(n);
                                lengths.Add(length);
                        } else {
                                index = small_index(lengths);
                                smallest = lengths[index];
                                if ((length > smallest) || (length == smallest && n < numbers[index])) {         
                                        numbers[index] = n;
                                        lengths[index] = length;
                                }
                        }
                }

                Console.WriteLine("\tNumber\tLength");
                for (int i = 0; i < numbers.Count; i++)
                        Console.WriteLine("\t{0}\t{1}", numbers[i], lengths[i]);

        }

	public static int small_index(List<int> lengths)
        {
                int smallest = lengths[0];
                int small_index = 0;

                for (int i = 0; i < lengths.Count; i++) {
                        if (lengths[i] < smallest) {
                                smallest = lengths[i];
                                small_index = i;
                        }
                }

                return small_index;
        }

}
