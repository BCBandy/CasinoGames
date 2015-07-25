#include"Card.h"
#include <string>
#include <vector>

Card::Card()
{
	suit[0] = "Hearts";
	suit[1] = "Spades";
	suit[2] = "Diamonds";
	suit[3] = "Clubs";

	face[0] = "Ace";
	face[1] = "2";
	face[2] = "3";
	face[3] = "4";
	face[4] = "5";
	face[5] = "6";
	face[6] = "7";
	face[7] = "8";
	face[8] = "9";
	face[9] = "10";
	face[10] = "Jack";
	face[11] = "Queen";
	face[12] = "King";
}

string Card::getFace(int f)
{
	return face[f];
}
string Card::getSuit(int s)
{
	return suit[s];
}
void Card::setMySuit(string s)
{
	mySuit = s;
}
void Card::setMyFace(string f)
{
	myFace = f;
}
string Card::getMySuit()
{
	return mySuit;
}
string Card::getMyFace()
{
	return myFace;
}