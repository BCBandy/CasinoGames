#include "Person.h"
#include <iostream>

using namespace std;

Person::Person()
{
	bankRoll = 1000;
}
int Person::setBet(int aBet)
{
	if (aBet > 0){
		if (bet > bankRoll && bankRoll != 0){
			cout << "You're low on cash, bet less" << endl;
			return 0;
		}
		else{
			bankRoll -= aBet;
			bet = aBet;
			cout << "Bet accepted" << endl;
			return 1;
		}
		if (bankRoll == 0){
			cout << "You're out of cash, game over!" << endl;
			return 2;
		}
	}
}
int Person::getBet() const
{
	return bet;
}
double Person::getBankRoll() const
{
	return bankRoll;
}

void Person::setBankRoll(double b)
{
	bankRoll = b;
}
void Person::setPlayHand(int dd)
{
	howToPlayHand = dd;
}
int Person::getPlayHand() const
{
	return howToPlayHand;
}
void Person::setSplitBets(int bet)
{
	splitBets.push_back(bet);
}
int Person::getSplitBets(int bet)
{
	return splitBets.at(bet);
}
void Person::setHandTotals(int handValue)
{
	handTotal.push_back(handValue);
}
int Person::getHandTotal(int player, int hand)
{
	return handTotal.at(hand);
}