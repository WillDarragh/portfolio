#include <iostream>
#include <sstream>
#include "btree.h"

using namespace std;

int height;

int main(int argv, char* args[])
{
	BTree tree;

	string filename = args[1];

	tree.reset((char*)filename.c_str());

//	height = tree.getHeight();

//	cout << "Height: " << height << endl;

	Album album;

	ifstream data(args[2], ios::in);

	while(data >> album)
	{
		tree.insert(album);
//		tree.printTree();
//		cout << endl;
	}

	tree.printTree();

	tree.close();	

	return 0;
}
