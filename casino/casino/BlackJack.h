#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "Person.h"
#include "Deck.h"
#include <vector>
using namespace std;

class BlackJack : public Person, public Deck
{
	
public:
	BlackJack();
	~BlackJack(){}
	void getPlayers();
	void createPlayers();
	void printHand(int) const;
//	friend ostream& operator<<(ostream&, BlackJack&);
	int getNumPlayers() const;
	void placeBets();
	void deal();
	void split(int);
	void doubleDown(int);
	void surrender(int);
	void playHand();
	int checkSplit(int);
	void hit(int, int);
	int setHandTotal(int, int);
	int determineCardValue(string);
	void stand(int);
	void playDealerHand();
	void printDealerHand() const;
	void payOut();
	void loopGame();
protected:
	Card dealerHand[2];
	Person *players;
	int numPlayers;
};

#endif