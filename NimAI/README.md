**Will Darragh**
**CSC 380**
**Dr. Digh**
**Nim Game**

# Nim Game README

--------------------------------------------

*Last Updated:* 	01-28-2020 

--------------------------------------------
## Algorithms

###  Game Setup and Finish

1. Prompt user for for number of chips in each pile
	- check if valid (positive integer)
2. Prompt user for going first or second
3. **Play Game**
4. Prompt user to play again
	- if yes, go back to 1 of Game Setup
	- if no, exit program

### Play Game
1. Print piles
2. Get player 1 move
	- if human, read from standard input and check for validity (integer between 1 and three inclusive)
	- if computer, use **Nim AI**
3. Update piles, and check to see if player 1 loses
	- if player 1 loses, exit playgame, else continue
4. Print piles
5. Get player 2 move
	- if human, read from standard input and check for validity (integer between 1 and three inclusive)
	- if computer, use **Nim AI**
6. Update piles, and check to see if player 2 loses
	- if player 1 loses, exit playgame, else go back to 1 of Play Game

### Nim AI
TODO: this section
