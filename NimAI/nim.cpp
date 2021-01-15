// Will Darragh
// CSC 380
// Dr. Digh
// Nim Game

/*
	Nim Game
	--------

	Human vs. Computer game of nim
*/

#include <iostream> // cin, cout, etc
#include <fstream> // fstream
#include <utility> // pair
#include <limits> // numeric limits
#include <vector> // dynamic array
#include <sstream> // string stream
#include <string> // string compare

// Move type definition
typedef std::pair<char, int> move;

// Class for piles
class Piles {
     public:
	// Constructor
	Piles() {
		A = 0;
		B = 0;
		C = 0;
	}
	// Getter for pile size
	int getSize(char pile) {
		int size;

		switch ( pile )
		{
			case 'A': size = A; break;
			case 'B': size = B; break;
			case 'C': size = C; break;
			default: size = -1; break;
		}

		return size;
	}
	// Update board base on move
	void update(move mv) {
		switch ( mv.first )
		{
			case 'A': A -= mv.second; break;
			case 'B': B -= mv.second; break;
			case 'C': C -= mv.second; break;
		}
	}
	bool validStart() {
		return ( A > 0 && B > 0 && C > 0);
	}
	// Check if a player has won
	bool gameOver() {
		return ( A == 0 && B == 0 && C == 0 );
	}
	// Assignment operator overload
	void operator = (const Piles &P) {
		A = P.A;
		B = P.B;
		C = P.C;
	}
	// Equality operator overload
	friend bool operator == (const Piles &P1, const Piles &P2) {
		return 	( P1.A == P2.A &&
			  P1.B == P2.B &&
			  P1.C == P2.C );
	}
	// Less than operator overload
	friend bool operator < (const Piles &P1, const Piles &P2) {
		if ( P1.A < P2.A ) {
			return true;
		} else if ( P1.A == P2.A) {
			if ( P1.B < P2.B ) {
				return true;
			} else if ( P1.B == P2.B ) {
				if ( P1.C < P2.C ) {
					return true;
				} else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
	// Input operator overload
	friend std::istream &operator >> (std::istream &input, Piles &P) {
		input >> P.A >> P.B >> P.C;
		return input;
	}
	// Output operator overload
	friend std::ostream &operator << (std::ostream &output, const Piles &P) {
		output << P.A << " " << P.B << " " << P.C << '\n';
		return output;
	}
	// Print piles nicely
	void print() {
		int i;		

		std::cout << std::endl;
		std::cout << "A: ";
		for ( i = 0; i < A; i++ ) { std::cout << "0 "; }
		std::cout << std::endl;
		std::cout << "B: ";
		for ( i = 0; i < B; i++ ) { std::cout << "0 "; }
		std::cout << std::endl;
		std::cout << "C: ";
		for ( i = 0; i < C; i++ ) { std::cout << "0 "; }
		std::cout << std::endl;
		std::cout << '\n' << "A: " << A << " B: " << B << " C: " << C << '\n' << std::endl;
	}
    private:
	// Pile sizes
	int A, B, C;
};

// Piles Pointer
typedef Piles *pilesPtr;

class NimAI {
    public:
	// Constructors
	NimAI() {}
	NimAI(const char fn[]) {
		filename = fn;
	}
	bool isSafe(move mv, pilesPtr piles) {
		current = *piles;
		current.update(mv);

		return ( findPos() < -1 );
	}
	// Reset the AI at the beginning of every match
	void reset() {
		file.close();
		plays.clear();
	}
	// Add a move to vector of this game's moves
	void addPlay(move mv, pilesPtr piles) {
		current = *piles;
		current.update(mv);
		plays.push_back(current);
	}
	// Update the AI at the end of every match if it loses
	void update() {
		for ( auto it = plays.begin(); it != plays.end(); ++it ) {
			current = *it;
			if ( findPos() < -1 ) {
				file.open(filename, std::ios::in | std::ios::out);
				ss.clear();	

				// Find position to insert new move
				do {
					file >> buffer;
					prev = pos;
					pos = file.tellg();
				} while ( buffer < current && (! file.eof()) );

				// Save position
				if ( file.eof() ) {
					file.clear();
					file.seekg(0, std::ios::end);
					pos = file.tellg();
				} else {
					pos = prev;
					pos++;
					ss << buffer;
				}

				// Fill the a stringstream with rest of file
				while ( file >> buffer ) {
					ss << buffer;
				}

				// Write new move in position
				file.clear();
				file.seekp(pos);

				file << current;

				// Write rest of file
				while ( ss >> buffer ) {
					file << buffer;
				}

				file.close();
			}
		}
	}
	// Find the position in the file of the current piles
	// Return -1 if not found
	int findPos() {
		file.open(filename, std::ios::in);
		while ( file >> buffer ) {
			if ( current == buffer ) {
				file.close();
				return file.tellg();
			}
		}
		file.close();
		return -2;
	}
    private:
	const char *filename; // Filename
	std::fstream file; // File stream
	Piles current; // current Piles state to check
	Piles buffer; // Piles buffer to read from file
	std::vector<Piles> plays; // Vector of this games moves
	std::stringstream ss; // String stream for reading files
	int pos; // position for file processing
	int prev; // previous positon for file processing
};

// NimAI pointer
typedef NimAI *aiPtr;

// Get Move function pointer
typedef move (*getMove)(pilesPtr);

void playGame(pilesPtr piles, getMove p1Move, getMove p2Move); // main section where game takes place
			   				       // passed an int which says who goes first	

void botGame(pilesPtr piles, getMove p1Move, getMove p2Move); // Game for bots!

move getHumanMove(pilesPtr piles); // Prompt Human for move
		     		   // return Human move

move getComputerMove(pilesPtr piles); // Nim AI section
				      // return Computer move

// Global Pointer to NimAI in use 		 
aiPtr AI;

// begin MAIN
int main(int argc, char *argv[]) 
{
	if ( argc > 1 ) {
	if ( std::string(argv[1]) == "bots" ) {
	
	Piles thePiles;
	pilesPtr piles = &thePiles;

	std::stringstream ss;

	ss << argv[2] << " ";
	ss << argv[3] << " ";
	ss << argv[4] << " ";
	
	ss >> *piles;

	botGame(piles, &getComputerMove, &getComputerMove);
	
	}
	} else {

	std::cout << "\n\tNim Game" << std::endl;

	// Nim AI file here
	NimAI nimAI("unsafe.shortest");
	AI = &nimAI;
	
	int choice; // first or second
	getMove p1Move;
	getMove p2Move;
	
	Piles thePiles;
	pilesPtr piles = &thePiles;

	char playAgain = 'Y';

	while ( playAgain == 'Y' ) {

		std::cout << "\nHow many coins in each pile (input 3 integers)? " << std::flush;
		while ( ! ( (std::cin >> *piles) && ( piles -> validStart() ) ) ) {
			std::cout << "Input 3 positive integers seperated by spaces. ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(),'\n');
		}

		std::cout << std::endl;

		std::cout << "Do you want to go first or second (1 or 2)? " << std::flush;
		while ( ! (std::cin >> choice) ) {
			std::cout << "Input 1 to go first, or any integer to go second. ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(),'\n');
		}

		if ( choice == 1 ) {
			p1Move = &getHumanMove;
			p2Move = &getComputerMove;
		} else {
			p1Move = &getComputerMove;
			p2Move = &getHumanMove;
		}

		AI -> reset();
	
		playGame(piles, p1Move, p2Move);

		std::cout << "\nDo you want to play agame (Y/N)? ";

		std::cin >> playAgain;
	
	}

	std::cout << std::endl;
	
	}

	return 0;
}
// end MAIN

void botGame(pilesPtr piles, getMove p1Move, getMove p2Move)
{
	// Bot AIs files here
	NimAI nim1("unsafe.shortest");
	NimAI nim2("unsafe.shortest");

	while ( true ) {
		AI = &nim1;
		piles -> update(p1Move(piles));
		piles -> print();
			if ( piles -> gameOver() ) {
				break;
			}
		AI = &nim2;
		piles -> update(p2Move(piles));
		piles -> print();
			if ( piles -> gameOver() ) {
				break;
			}
	}

	AI -> update();
}

void playGame(pilesPtr piles, getMove p1Move, getMove p2Move)
{
	std::cout << "\n     Nim      \n" 
		  << "----------------\n"; 

	piles -> print();


	NimAI nim1("unsafe");
	NimAI nim2("unsafe");

	while ( true ) {
		AI = &nim1;
		piles -> update(p1Move(piles));
		piles -> print();
			if ( piles -> gameOver() ) {
				if ( p1Move == &getHumanMove ) {
					std::cout << "You lose!" << std::endl;
				} else {
					std::cout << "You win!" << std::endl;
					AI -> update();
				}
				break;
			}
		AI = &nim2;
		piles -> update(p2Move(piles));
		piles -> print();
			if ( piles -> gameOver() ) {
				if ( p2Move == &getHumanMove ) {
					std::cout << "You lose!" << std::endl;
				} else {
					std::cout << "You win!" << std::endl;
					AI -> update();
				}
				break;
			}
	}
}

move getHumanMove(pilesPtr piles)
{
	char pile;
	int n;

	while ( true ) {
		std::cout << "What is your move (letter & integer)? " << std::flush;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		std::cin >> pile >> n;

		if ( std::cin.fail() ) {
			std::cout << "Bad input." << std::endl;
		} else if ( ! ( pile == 'A' || pile == 'B' || pile == 'C' ) ) {
			std::cout << "Pile letter must be A, B, or C." << std::endl;
		} else if ( ! ( 1 <= n && n <= 3 ) ) {
			std::cout << "Number of coins must be between 1 and 3 inclusive." << std::endl;
		} else if ( ! ( n <= piles -> getSize(pile) ) ) {
			std::cout << "Number of coins cannot be greater than size of pile." << std::endl;
		} else {
			break;
		}
	}

	return std::make_pair(pile, n);
}

move getComputerMove(pilesPtr piles)
{
	char pile = 'A';
	int n = 1;

	while ( pile <= 'C' && n <= 3 )
	{
		if ( n <= piles -> getSize(pile) ) {
			if ( AI -> isSafe(std::make_pair(pile, n), piles) ) {
				break;
			}
		}

		if ( n < 3 ) {
			n++;
		} else {
			pile++;
			n = 1;
		}
	}

	if ( pile == 'D' ) {
		for ( pile = 'A'; pile <= 'C'; pile++ ) {
			for ( n = 3; n >= 1; n-- ) {
				if ( n <= piles -> getSize(pile) ) {
					std::cout << "Computer chose " << pile << n << std::endl;
					return std::make_pair(pile, n);
				}
			}
		}
	}

	AI -> addPlay(std::make_pair(pile, n), piles);
	
	std::cout << "Computer chose " << pile << n << std::endl;
	return std::make_pair(pile, n);
}
