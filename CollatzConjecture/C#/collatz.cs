// Collatz in C#
// Will Darragh

using System;
using System.Collections.Generic;

class collatz
{

	// MAX NUMBER
	public static int N = 10000;

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

	public static int collatz_length(int n)
	{                
		int x = n;
                int length = 0;
                while ( x != 1 ) {
                        if ( x%2 == 0 )
                                x = x/2;
                        else
                                x = 3*x + 1;
                        length++;
                }
                return length;
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
