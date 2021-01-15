#include "btree.h"
using namespace std;

// !!!NOTE!!! ORDER-1 must be EVEN for splitting to work

BTree::BTree()
{
}

void BTree::reset(char* filename)
{
	root.currSize = 0;
	for (int i = 0; i < ORDER; i++ ) root.child[i] = -1;
	rootAddr = 0;
	strcpy(treeFileName, filename);
	treeFile.open(treeFileName, ios::in | ios::out | ios::binary);
	treeFile.write((char*)&root, sizeof(BTNode));
	height = 0;
	read = 0; 
	write = 1;
}

// Public insert from root
void BTree::insert(keyType key)
{
	insert(key, rootAddr, -1);
}

// Private insert recursively
pair<bool, keyType> BTree::insert(keyType key, int recAddr, int parentAddr)
{
	BTNode currNode;
	treeFile.seekg(recAddr, treeFile.beg);
	treeFile.read((char*)&currNode, sizeof(BTNode));
	read++;

	set<Album> newContents;
	for (int i = 0; i < currNode.currSize; i++)
	{
		newContents.insert(currNode.contents[i]);
	}	
	newContents.insert(key);

	if (isLeaf(currNode)) // If node is a leaf
	{
		if (currNode.currSize < ORDER-1) // If node is not full
		{
			currNode.currSize++;

			set<Album>::iterator it = newContents.begin();
			for (int i = 0; i < currNode.currSize; i++, ++it)
			{
				currNode.contents[i] = *it;
			}

			treeFile.seekp(recAddr, treeFile.beg);
			treeFile.write((char*)&currNode, sizeof(BTNode));
			write++;
		}
		else // Node is full, need to split
		{
			if (parentAddr < 0) // Special case for first split on root
			{
				splitRoot(key, recAddr, currNode);
			}
			else
			{
				BTNode parentNode;
				treeFile.seekg(parentAddr, treeFile.beg);
				treeFile.read((char*)&parentNode, sizeof(BTNode));
				read++;

				if (parentNode.currSize < ORDER - 1) // Parent Node is not full
				{
					set<Album>::iterator it = newContents.begin();
					int childSize =	(ORDER - 1) / 2;

					// Left Child
					BTNode left;
					left.currSize = childSize;
					for (int i = 0; i < childSize; i++, ++it)
					{
						left.contents[i] = *it;
					}
					for (int i = 0; i < ORDER; i++ ) left.child[i] = -1;
				
					treeFile.seekp(recAddr, treeFile.beg);
					treeFile.write((char*)&left, sizeof(BTNode));
					write++;
						
					// Parent Node
					set<Album> parentContents;
					for (int i = 0; i < parentNode.currSize; i++)
					{
						parentContents.insert(parentNode.contents[i]);
					}
					parentContents.insert(*it);
					parentNode.currSize++;
					int pos;
					set<Album>::iterator pIt = parentContents.begin();
					for (int i = 0; i < parentNode.currSize; i++, ++pIt)
					{
						parentNode.contents[i] = *pIt;
						if ((*pIt) == (*it)) 
							pos = i;
					}

					for (int i = parentNode.currSize; i > pos; i--)
					{
						parentNode.child[i] = parentNode.child[i-1];
					}
					parentNode.child[pos] = recAddr;
					treeFile.seekp(0, treeFile.end);
					parentNode.child[pos+1] = treeFile.tellp();

					++it;
					treeFile.seekp(parentAddr, treeFile.beg);
					treeFile.write((char*)&parentNode, sizeof(BTNode));
					write++;

					// Right Child
					BTNode right;
					right.currSize = childSize;
					for (int i = 0; i < childSize; i++, ++it)
					{
						right.contents[i] = *it;
					}
					for (int i = 0; i < ORDER; i++ ) right.child[i] = -1;

					treeFile.seekp(0, treeFile.end);
					treeFile.write((char*)&right, sizeof(BTNode));
					write++;
				}
				else // Parent Node is full
				{
					set<Album>::iterator it = newContents.begin();
					int childSize =	(ORDER - 1) / 2;

					// Left Child
					BTNode left;
					left.currSize = childSize;
					for (int i = 0; i < childSize; i++, ++it)
					{
						left.contents[i] = *it;
					}
					for (int i = 0; i < ORDER; i++ ) left.child[i] = -1;
				
					treeFile.seekp(recAddr, treeFile.beg);
					treeFile.write((char*)&left, sizeof(BTNode));
					write++;
						
					// Parent Node
					keyType newKey = (*it);
					++it;

					// Right Child
					BTNode right;
					right.currSize = childSize;
					for (int i = 0; i < childSize; i++, ++it)
					{
						right.contents[i] = *it;
					}
					for (int i = 0; i < ORDER; i++ ) right.child[i] = -1;

					treeFile.seekp(0, treeFile.end);
					treeFile.write((char*)&right, sizeof(BTNode));
					write++;

					pair<bool, keyType> recursiveSplit;
					recursiveSplit.first = true;
					recursiveSplit.second = newKey;
					return recursiveSplit; 
				}
			}
		}
	}
	else // Node is not leaf
	{
		int pos = 0;
		for (int i = 0; i < currNode.currSize; i++)
		{
			if (!(key < currNode.contents[i])) 
			{
				pos++;
			}
			else break;
		}
		pair<bool, keyType> recursiveSplit = insert(key, currNode.child[pos], recAddr); // Info for recursive split
		if (recursiveSplit.first)
		{
			keyType newKey = recursiveSplit.second;
			int oldRecAddr = currNode.child[pos];
			if (parentAddr < 0)
			{
				splitRoot(newKey, oldRecAddr, currNode);
			}
			else
			{
				int childSize = (ORDER - 1) / 2;

				set<Album> newContents;
				for (int i = 0; i < currNode.currSize; i++)
				{
					newContents.insert(currNode.contents[i]);
				}
				newContents.insert(key);

				set<Album>::iterator it = newContents.begin();
				int pos = 0;
				int childPos = 0;

				for (int i = 0; i < currNode.currSize; i++, ++it)
				{
					pos = i;
					if ((*it) == key)
					{
						break;
					}
					pos++;
				}	
				it = newContents.begin();
				
				// Left Child
				BTNode left;
				left.currSize = childSize;
				for (int i = 0; i < childSize; i++, ++it)
				{
					left.contents[i] = *it;
				}
				for (int i = 0; i < ORDER; i++) left.child[i] = -1;
					
				if (!isLeaf(currNode));
				{
					for (int i = 0; i < childSize+1; i++) 
					{
						if (childPos != pos)
						{
							left.child[i] = currNode.child[childPos];
							childPos++;
						}
						else
						{
							left.child[i] = oldRecAddr;
							i++;
							if (i != childSize+1)
							{
								treeFile.seekp(-1*sizeof(BTNode), treeFile.end);
								left.child[i] = treeFile.tellp();
							}
						}
					}
				}

				// Parent Node
				keyType newKey = *it;
				++it;

				// Right Child
				BTNode right;
				right.currSize = childSize;
				for (int i = 0; i < childSize; i++, ++it)
				{
					right.contents[i] = *it;
				}
				for (int i = 0; i < ORDER; i++) right.child[i] = -1;

				if (!isLeaf(currNode))
				{	
					for (int i = 0; i < childSize+1; i++) 
					{
						if (i==0 && (childPos == pos))
						{
							treeFile.seekp(-1*sizeof(BTNode), treeFile.end);
							right.child[i] = treeFile.tellp();
						}
						else if (childPos != pos)
						{
							right.child[i] = currNode.child[childPos];
							childPos++;
						}
						else
						{
							right.child[i] = oldRecAddr;
							i++;
							treeFile.seekp(-1*sizeof(BTNode), treeFile.end);
							right.child[i] = treeFile.tellp();
						}
					}
				}

				treeFile.seekp(recAddr, treeFile.beg);
				treeFile.write((char*)&left, sizeof(BTNode));
				treeFile.seekp(0, treeFile.end);
				treeFile.write((char*)&right, sizeof(BTNode));
				write += 2;
				
				BTNode parentNode;
				treeFile.seekg(parentAddr, treeFile.beg);
				treeFile.read((char*)&parentNode, sizeof(BTNode));
				read++;
			
				if (parentNode.currSize < ORDER - 1) // Parent Node is not full
				{
					// Parent Node
					set<Album> parentContents;
					for (int i = 0; i < parentNode.currSize; i++)
					{
						parentContents.insert(parentNode.contents[i]);
					}
					parentContents.insert(newKey);
					parentNode.currSize++;
					int pos;
					set<Album>::iterator pIt = parentContents.begin();
					for (int i = 0; i < parentNode.currSize; i++, ++pIt)
					{
						parentNode.contents[i] = *pIt;
						if ((*pIt) == (newKey)) 
							pos = i;
					}

					for (int i = parentNode.currSize; i > pos; i--)
					{
						parentNode.child[i] = parentNode.child[i-1];
					}
					parentNode.child[pos] = recAddr;
					treeFile.seekp(-1*sizeof(BTNode), treeFile.end);
					parentNode.child[pos+1] = treeFile.tellp();

					treeFile.seekp(parentAddr, treeFile.beg);
					treeFile.write((char*)&parentNode, sizeof(BTNode));
					write++;
				}
				else // Parent Node is full
				{
					pair<bool, keyType> recursiveSplit;
					recursiveSplit.first = true;
					recursiveSplit.second = newKey;
					return recursiveSplit; 
				}
			}
		}
	}
	pair<bool, keyType> finished;
	finished.first = false;
	return finished;
}

// Split on root
void BTree::splitRoot(keyType key, int recAddr, BTNode currNode)
{
	height++;

	int childSize = (ORDER - 1) / 2;

	set<Album> newContents;
	for (int i = 0; i < currNode.currSize; i++)
	{
		newContents.insert(currNode.contents[i]);
	}
	newContents.insert(key);

	set<Album>::iterator it = newContents.begin();
	int pos = 0;
	int childPos = 0;

	for (int i = 0; i < currNode.currSize; i++, ++it)
	{
		pos = i;
		if ((*it) == key)
		{
			break;
		}
		pos++;
	}	
	it = newContents.begin();

	// Left Child
	BTNode left;
	left.currSize = childSize;
	for (int i = 0; i < childSize; i++, ++it)
	{
		left.contents[i] = *it;
	}
	for (int i = 0; i < ORDER; i++) left.child[i] = -1;
		
	if (!isLeaf(currNode));
	{
		for (int i = 0; i < childSize+1; i++) 
		{
			if (childPos != pos)
			{
				left.child[i] = currNode.child[childPos];
				childPos++;
			}
			else
			{
				left.child[i] = recAddr;
				i++;
				if (i != childSize+1)
				{
					treeFile.seekp(-1*sizeof(BTNode), treeFile.end);
					left.child[i] = treeFile.tellp();
				}
			}
		}
	}

	// New Root
	root.currSize = 1;
	root.contents[0] = *it;
	++it;
	treeFile.seekp(0, treeFile.end);
	root.child[0] = treeFile.tellp();
	root.child[1] = int(treeFile.tellp()) + sizeof(BTNode);

	// Right Child
	BTNode right;
	right.currSize = childSize;
	for (int i = 0; i < childSize; i++, ++it)
	{
		right.contents[i] = *it;
	}
	for (int i = 0; i < ORDER; i++) right.child[i] = -1;

	if (!isLeaf(currNode))
	{	
		for (int i = 0; i < childSize+1; i++) 
		{
			if (i==0 && (childPos == pos))
			{
				treeFile.seekp(-1*sizeof(BTNode), treeFile.end);
				right.child[i] = treeFile.tellp();
			}
			else if (childPos != pos)
			{
				right.child[i] = currNode.child[childPos];
				childPos++;
			}
			else
			{
				right.child[i] = recAddr;
				i++;
				treeFile.seekp(-1*sizeof(BTNode), treeFile.end);
				right.child[i] = treeFile.tellp();
			}
		}
	}

	treeFile.seekp(rootAddr, treeFile.beg);
	treeFile.write((char*)&root, sizeof(BTNode));
	treeFile.seekp(0, treeFile.end);
	treeFile.write((char*)&left, sizeof(BTNode));
	treeFile.write((char*)&right, sizeof(BTNode));
	write += 3;
}

// Check if a node is a leaf (has no children)
bool BTree::isLeaf(BTNode node)
{
	for (int i = 0; i < ORDER; i++)
	{
		if (!(node.child[i] < 0))
		{
			return false;
		}
	}
	return true;
}

// Check if the node at an address if full
bool BTree::isFull(int recAddr)
{
	BTNode node;
	treeFile.seekg(recAddr, treeFile.beg);
	treeFile.read((char*)&node, sizeof(BTNode));
	read++;

	return (node.currSize = ORDER - 1);
}

// Print the file sequentially
void BTree::printFile()
{
	try
	{
	treeFile.seekg(0, treeFile.beg);
	BTNode currNode;
	while (treeFile.read((char*)&currNode, sizeof(BTNode)))
	{
		read++;
		for (int i = 0; i < currNode.currSize; i++)
			cout << currNode.contents[i] << endl;
		cout << endl;
		cout << treeFile.tellg() << endl;
	}
	} catch (...) {}
	treeFile.clear();
}

// Public print tree from root
void BTree::printTree()
{
	treeFile.clear();
	cout << "\tTree is height" << height << endl;
	printTree(rootAddr);
	cout << "\tread: " << read << "\twrite: " << write << endl;
}

// Private print tree recursively
void BTree::printTree(int recAddr)
{
	BTNode currNode;
	treeFile.seekg(recAddr, treeFile.beg);
	treeFile.read((char*)&currNode, sizeof(BTNode));
	read++;

	cout << "---------------------------------------" << endl;
	for (int i = 0; i < currNode.currSize; i++)
	{
		cout << currNode.contents[i] << endl;
	}

	for (int i = 0; i < ORDER; i++)
	{
		if (currNode.child[i] < 0) break;
		printTree(currNode.child[i]);
	}
	cout << "---------------------------------------" << endl;
}

// Public search
bool BTree::search(keyType key)
{
	return search(key, rootAddr);
}

// Priavte search
bool BTree::search(keyType key, int recAddr)
{
	BTNode currNode;
	treeFile.seekg(recAddr, treeFile.beg);
	treeFile.read((char*)&currNode, sizeof(BTNode));
	read++;

	for (int i = 0; i < currNode.currSize; i++)
	{
		if (currNode.contents[i] == key) return true;
		cout << "Found " << key << endl;
	}

	for (int i = 0; i < ORDER; i++)
	{
		if (currNode.child[i] < 0) break;
		printTree(currNode.child[i]);
	}
}

void BTree::close()
{
	treeFile.close();
}

int BTree::getHeight()
{
	return height;
}
