Will Darragh
CSC 310
Dr. Digh
Project #3

BBBBBBBBBBBBBBBBBBBBBBBBBBB
BBB			BBB
BBB	The B-Tree	BBB
BBB			BBB
BBBBBBBBBBBBBBBBBBBBBBBBBBB

---------------------------
---	Classes		---
---------------------------

Album
-----

The Album class contains all the information for
our album objects, which we will be storing in a BTree.
Holds a universal product code (UPC), artist name (Artist),
and title (Title).

public:
  Constructors
    -Default
    -Copy
    -Regular - passed char arrays upc, artist, and title
  Assignment operator =
  Comparison operator < (compares based on UPC)
  Instream operator >> (reads in three lines)
  Outstream operator << (writes out three lines)
  Getters
    -getUPC
    -recordSize (size of record)

private:
  (String defined as char array size 50)
  String UPC, Artist, and Title

BTree //TODO: Add as necesarry
-----

The BTree class is used to build and edit the BTree index
file that stores all the information of the Albums stored.
BTree should be of order 5.

Structs:
  BTNode - Node for tree containing size, contents, and child nodes
  Pair - ????? I don't know what this does so I may not use it

Public:
  insert - Insert an album into the tree
         - 1. Find the insertion spot
	     a. Start at top, find first element greater
             b. If it has child, go into child
	   Repeat 1 until at lowest level
           2. If not full, insert
           3. If is full, split	
	     a. Move middle element up
	     b. Create new nodes and adjust as necesary

Private:

---------------------------
---	Client Programs	---
---------------------------

Create BTree
------------

Input - input comes from a file passed from command line
      - albums are the format CPU, Artist, Title each on one line

Output - output will be a binary file created with the BTree (tree.ind)

Algorithm Design-

  1. Initial Setup
    a. Open input file
    b. Create BTree


  2. While Getting input
    a. Read the input into an Album object buffer
    b. Insert into tree
      i. Several things may happen to the tree, including a split or root adjustment
      ii. Tree should print to screen what happens
   
  3. Print the B-Tree
  4. Output B-Tree to binary file


Update BTree //TODO: add info as I think about how to do update
------------
