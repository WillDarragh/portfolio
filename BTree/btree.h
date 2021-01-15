#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "album.h"
using namespace std;

class Album;
const int ORDER = 5;
typedef Album keyType;
typedef int IndexArray[ORDER];
typedef keyType ValueArray[ORDER-1];

struct BTNode
{
        int currSize;
        ValueArray contents;
        IndexArray child;
}; 

/*
struct Pair
{
        Album element;
        int loffset;
        int roffset;
        friend bool operator < (const Pair& p1, const Pair& p2)
           { return (p1.element < p2.element);  }
};
*/

class BTree
{
 public:
	BTree();
//	void writeHeader (char * fileName);
	void insert (keyType key);
	void reset (char * filename);
	void close ();
	void printTree();
	void printFile(); // Prints contents of file in order on file
//	void inorder();
//	void reverse();
	bool search(keyType key);
	int getHeight();
//	bool search (string key);
//	keyType retrieve (string key);
//	void totalio() const;
//	int countLeaves();

 private:
	BTNode root;
	int rootAddr;
	char treeFileName[80];
	fstream treeFile;
	int height;
	void printTree(int recAddr);
//	void inorder (int rootAddr);
//	void reverse (int rootAddr);
	int read;
	int write;

//	int findAddr (keyType key, BTNode t, int tAddr);
//	int findpAddr(keyType key, BTNode t, int tAddr);
	pair<bool, keyType> insert (keyType key, int recAddr, int parentAddr); // Returns info for recursively splitting
	void splitRoot(keyType key, int recAddr, BTNode currNode);
	bool search(keyType key, int recAddr);
//	BTNode getNode (int recAddr);
//	void printNode(int recAddr);
//	void placeNode (keyType k,int recAddr,int oneAddr,int twoAddr);
//	bool isLeaf (int recAddr);
	bool isLeaf(BTNode node);
	bool isFull(int recAddr);
//	int countLeaves(int recAddr);
//	void adjRoot (keyType rootElem, int oneAddr, int twoAddr);
//	void splitNode (keyType& key,int recAddr,int& oneAddr,int& twoAddr);
//	bool search (string key, BTNode t, int tAddr);
	
};

#endif
