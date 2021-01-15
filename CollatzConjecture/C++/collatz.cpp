// Collatz Conjectture
// Will Darragh

#include <iostream> // cout
#include <vector> // dynamic array

using namespace std;

// Calculate Collatz Length
int collatz(int n);

// Find index of smallest int
int small_index(vector<int> lengths);

// MAX NUMBER
const int N = 10000;

int main()
{
	vector<int> numbers;
	vector<int> lengths;

	int length, index, smallest;
	for ( int n = 1; n <= N; n++ ) {
		length = collatz(n);
		if (numbers.size() < 10) {
			numbers.push_back(n);
			lengths.push_back(length);
		} else {
			index = small_index(lengths);
			smallest = lengths[index];
			if ((length > smallest) || (length == smallest && n < numbers[index])) {
				numbers[index] = n;
				lengths[index] = length;
			}
		}
			
	}

	cout << "Number\tLength" << endl;
	for (int i = 0; i < numbers.size(); i++)
		cout << numbers[i] << "\t" << lengths[i] << endl;		

	return 0;
}

int collatz(int n)
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

int small_index(vector<int> lengths)
{
	int smallest = lengths[0];
	int small_index = 0;

	for (int i = 0; i < lengths.size(); i++) {
		if (lengths[i] < smallest) {
			smallest = lengths[i];
			small_index = i;
		}
	}

	return small_index;
}
