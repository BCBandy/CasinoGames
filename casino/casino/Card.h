#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>
using namespace std;

class Card
{
public:
	Card();
	~Card(){};
	string getSuit(int);
	string getFace(int);
	void setMySuit(string);
	void setMyFace(string);
	string getMySuit();
	string getMyFace();
protected:
	string suit[4];
	string face[13];
	string mySuit;
	string myFace;
};
#endif