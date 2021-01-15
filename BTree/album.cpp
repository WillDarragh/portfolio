#include "album.h"
#include <cstring>
#include <string>
#include <fstream>
#include <stdlib.h> //atoi
using namespace std;

Album::Album()
{
}

Album & Album::operator = (const Album & otherAlbum)
{
	strcpy(UPC, otherAlbum.UPC);
	strcpy(Artist, otherAlbum.Artist);
	strcpy(Title, otherAlbum.Title);
	return *this;
}
bool operator < (const Album& a, const Album& b)
{
	int A = atoi(a.UPC);
	int B = atoi(b.UPC);
	return A < B;	
}

istream & operator >> (istream & stream, Album & C)
{
	stream.getline(C.UPC, UpTo);
	stream.getline(C.Artist, UpTo);
	stream.getline(C.Title, UpTo);
	return stream;
}

ostream & operator << (ostream & stream, Album & C)
{
	stream << C.UPC << "|" << C.Artist << "|" << C.Title;
	return stream;
}

bool operator == (const Album& a, const Album& b)
{
	int A = atoi(a.UPC);
	int B = atoi(b.UPC);
	return A == B;
}
