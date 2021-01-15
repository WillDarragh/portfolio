// Collatz in Java with Recursion
// Will Darragh

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

        public static int small_index(int[] lengths)
        {
                int smallest = lengths[0];
                int small_index = 0;

                for (int i = 0; i < lengths.length; i++) {
                        if (lengths[i] < smallest) {
                                smallest = lengths[i];
                                small_index = i;
                        }
                }

                return small_index;
        }

	public static void main(String[] args)
        {
                int[] numbers = new int[10];
                int[] lengths = new int[10];

                int curr_index = 0;

                int length, index, smallest;
                for ( int n = 1; n <= N; n++ ) {
                        length = collatz_length(n);
                        if (numbers.length < 10) {
                                numbers[curr_index] = n;
                                lengths[curr_index] = length;
                                curr_index++;
                        } else {
                                index = small_index(lengths);
                                smallest = lengths[index];
                                if ((length > smallest) || (length == smallest && n < numbers[index])) {
                                        numbers[index] = n;
                                        lengths[index] = length;
                                }
                        }
                }

                System.out.println("\tNumber\tLength");
                for (int i = 0; i < numbers.length; i++) {
                        System.out.print("\t");
                        System.out.print(numbers[i]);
                        System.out.print("\t");
                        System.out.print(lengths[i]);
                        System.out.println();
                }

        }
}
