#include <iostream>
#include <sstream>
#include "btree.h"

using namespace std;

int height;

int main(int argv, char* args[])
{
	BTree tree;

	string filename = args[2];

	tree.reset((char*)filename.c_str());

	Album album;

	ifstream data(args[2], ios::in);

	string buffer;

	while (data.getline(buffer))
	{
		if (buffer.compare("S") == 0)
		{
		}
		else if (buffer.compare("I") == 0)
		{
			data >> album;
			tree.insert(album);
		}
	}

	tree.printTree();

	tree.close();	

	return 0;
}
