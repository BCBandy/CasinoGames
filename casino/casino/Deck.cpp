#include "Deck.h"
#include <iostream>
#include <ctime>

using namespace std;

int Deck::deckCount = 0;

Deck::Deck(){
	int count = 0;
	for (int i = 0; i < 4; i++){						//initializes a deck of cards
		for (int j = 0; j < 13; j++){
			deck[count].setMySuit(getSuit(i));
			deck[count].setMyFace(getFace(j));
				count++;
		}
	}
	shuffle();
}
void Deck::printDeck()
{
	for (int i = 0; i < 52; i++){
		cout << deck[i].getMyFace() << " of " << deck[i].getMySuit() << endl;
	}
}
void Deck::shuffle()
{
	Card temp;
	srand(time(NULL));
//	cout << "Deck shuffeled" << endl;
	for (int i = 0; i < 52; i++){
		
		int seed = rand() % 52;
		temp = deck[i];
		deck[i] = deck[seed];
		deck[seed] = temp;
	}
}
const Deck &Deck::operator=(Deck &replacement)
{
	if (&replacement != this){
		temp = replacement;
		return *this;
	}
}