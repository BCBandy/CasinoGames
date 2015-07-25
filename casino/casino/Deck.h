#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <vector>
using namespace std;

class Deck : public Card
{
public:
	Deck();
	~Deck(){};
	void printDeck();
	void shuffle();
	const Deck &operator=(Deck&);
	void deal();
	static int deckCount;
protected:
	Card deck[52];
	vector<Card> discard;
	vector<Card> inPlay;
	Card temp;
};
#endif